#pragma once

#include <optional>

#include "vhal_can_bridge/can_frame.h"

namespace vhal_can_bridge {

struct DecodedVehicleSpeed {
    float kph = 0.0f;
};

class FrameDecoder {
  public:
    // First minimal mapping:
    // - CAN ID: 0x123
    // - Signal: vehicle_speed_kph in bytes[0..1], little-endian, scale 0.01
    std::optional<DecodedVehicleSpeed> DecodeVehicleSpeed(const CanFrame& frame) const;
};

}  // namespace vhal_can_bridge
