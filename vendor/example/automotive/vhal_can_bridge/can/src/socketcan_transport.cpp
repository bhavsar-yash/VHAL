#include "vhal_can_bridge/socketcan_transport.h"

#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>

namespace vhal_can_bridge {

SocketCanTransport::SocketCanTransport(std::string ifname) : ifname_(std::move(ifname)) {}

SocketCanTransport::~SocketCanTransport() {
    Stop();
}

bool SocketCanTransport::Start(FrameHandler handler) {
    if (running_.exchange(true)) {
        return false;
    }

    fd_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (fd_ < 0) {
        running_ = false;
        return false;
    }

    ifreq ifr {};
    std::strncpy(ifr.ifr_name, ifname_.c_str(), IFNAMSIZ - 1);
    if (ioctl(fd_, SIOCGIFINDEX, &ifr) < 0) {
        Stop();
        return false;
    }

    sockaddr_can addr {};
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        Stop();
        return false;
    }

    while (running_) {
        can_frame raw {};
        const ssize_t bytes = read(fd_, &raw, sizeof(raw));
        if (bytes < 0) {
            if (errno == EINTR) {
                continue;
            }
            break;
        }
        if (bytes != static_cast<ssize_t>(sizeof(raw))) {
            continue;
        }

        CanFrame frame {};
        frame.can_id = raw.can_id & CAN_EFF_MASK;
        frame.dlc = raw.len;
        for (size_t i = 0; i < frame.data.size(); ++i) {
            frame.data[i] = raw.data[i];
        }

        handler(frame);
    }

    Stop();
    return true;
}

void SocketCanTransport::Stop() {
    running_ = false;
    if (fd_ >= 0) {
        close(fd_);
        fd_ = -1;
    }
}

}  // namespace vhal_can_bridge
