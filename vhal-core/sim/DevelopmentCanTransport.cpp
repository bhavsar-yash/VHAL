#include "vhalcore/DevelopmentCanTransport.h"

namespace vhalcore {

void DevelopmentCanTransport::start(CanFrameCallback callback) {
    mRunning = true;

    // Demo frame:
    // CAN ID: 0x123
    // Bytes 0..1 little-endian raw speed value.
    // Raw 1000 with scale 0.01 => 10.00 m/s.
    CanFrame frame{};
    frame.id = 0x123;
    frame.dlc = 8;
    frame.data = {0xE8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    if (mRunning) {
        callback(frame);
    }
}

void DevelopmentCanTransport::stop() {
    mRunning = false;
}

}  // namespace vhalcore
