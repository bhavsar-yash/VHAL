#pragma once

#include <cstdint>
#include <optional>

#include "vhal_can_bridge/can_frame.h"

namespace vhal_can_bridge {

enum class SignalType {
    kVehicleSpeedKph,
    kEngineRpm,
    kGearPosition,
    kHvacFanLevel,
};

struct DecodedSignal {
    SignalType type = SignalType::kVehicleSpeedKph;
    float float_value = 0.0f;
    int32_t int32_value = 0;
};

class FrameDecoder {
  public:
    // DBC-aligned demo mappings (docs/dbc/vhal_can_bridge_demo.dbc):
    // - 0x123: vehicle_speed_kph bytes[0..1] little-endian scale 0.01
    // - 0x200: engine_rpm bytes[0..1] little-endian scale 0.25
    // - 0x202: gear_position byte[0] unsigned
    // - 0x201: hvac_fan_level byte[0] unsigned
    std::optional<DecodedSignal> Decode(const CanFrame& frame) const;
};

}  // namespace vhal_can_bridge
