#include "vhal_can_bridge/frame_decoder.h"

namespace vhal_can_bridge {
namespace {
constexpr uint32_t kVehicleSpeedCanId = 0x123;
constexpr float kScale = 0.01f;
}  // namespace

std::optional<DecodedVehicleSpeed> FrameDecoder::DecodeVehicleSpeed(const CanFrame& frame) const {
    if (frame.can_id != kVehicleSpeedCanId || frame.dlc < 2) {
        return std::nullopt;
    }

    const uint16_t raw = static_cast<uint16_t>(frame.data[0]) |
                         (static_cast<uint16_t>(frame.data[1]) << 8);
    return DecodedVehicleSpeed{.kph = static_cast<float>(raw) * kScale};
}

}  // namespace vhal_can_bridge
