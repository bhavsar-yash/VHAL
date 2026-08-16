#include "vhal_can_bridge/frame_decoder.h"

namespace vhal_can_bridge {
namespace {
constexpr uint32_t kVehicleSpeedCanId = 0x123;
constexpr uint32_t kPowertrainCanId = 0x200;
constexpr uint32_t kHvacCanId = 0x201;
constexpr uint32_t kGearCanId = 0x202;

constexpr float kVehicleSpeedScale = 0.01f;
constexpr float kEngineRpmScale = 0.25f;
}  // namespace

std::optional<DecodedSignal> FrameDecoder::Decode(const CanFrame& frame) const {
    if (frame.can_id == kVehicleSpeedCanId && frame.dlc >= 2) {
        const uint16_t raw = static_cast<uint16_t>(frame.data[0]) |
                             (static_cast<uint16_t>(frame.data[1]) << 8);
        return DecodedSignal{
                .type = SignalType::kVehicleSpeedKph,
                .float_value = static_cast<float>(raw) * kVehicleSpeedScale,
        };
    }

    if (frame.can_id == kPowertrainCanId && frame.dlc >= 2) {
        const uint16_t raw_rpm = static_cast<uint16_t>(frame.data[0]) |
                                 (static_cast<uint16_t>(frame.data[1]) << 8);
        return DecodedSignal{
                .type = SignalType::kEngineRpm,
                .float_value = static_cast<float>(raw_rpm) * kEngineRpmScale,
        };
    }

    if (frame.can_id == kHvacCanId && frame.dlc >= 1) {
        return DecodedSignal{
                .type = SignalType::kHvacFanLevel,
                .int32_value = static_cast<int32_t>(frame.data[0]),
        };
    }

    if (frame.can_id == kGearCanId && frame.dlc >= 1) {
        return DecodedSignal{
                .type = SignalType::kGearPosition,
                .int32_value = static_cast<int32_t>(frame.data[0]),
        };
    }

    return std::nullopt;
}

}  // namespace vhal_can_bridge
