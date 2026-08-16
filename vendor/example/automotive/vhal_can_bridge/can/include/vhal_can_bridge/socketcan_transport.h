#pragma once

#include <atomic>
#include <string>

#include "vhal_can_bridge/can_transport.h"

namespace vhal_can_bridge {

class SocketCanTransport final : public CanTransport {
  public:
    explicit SocketCanTransport(std::string ifname);
    ~SocketCanTransport() override;

    bool Start(FrameHandler handler) override;
    void Stop() override;

  private:
    std::string ifname_;
    int fd_ = -1;
    std::atomic<bool> running_{false};
};

}  // namespace vhal_can_bridge
