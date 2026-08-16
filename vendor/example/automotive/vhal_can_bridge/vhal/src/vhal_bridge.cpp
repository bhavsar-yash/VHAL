#include "vhal_can_bridge/vhal_bridge.h"

namespace vhal_can_bridge {
namespace {
// TODO(aaos15): replace with generated AIDL constant reference in platform integration.
constexpr int32_t kPerfVehicleSpeedPropertyId = 0x11600207;
}  // namespace

std::optional<PropertyUpdate> VhalBridge::HandleFrame(const CanFrame& frame,
                                                      int64_t timestamp_ns) const {
    const auto decoded = decoder_.DecodeVehicleSpeed(frame);
    if (!decoded.has_value()) {
        return std::nullopt;
    }

    return PropertyUpdate{
            .property_id = kPerfVehicleSpeedPropertyId,
            .float_value = decoded->kph,
            .timestamp_ns = timestamp_ns,
    };
}

}  // namespace vhal_can_bridge
