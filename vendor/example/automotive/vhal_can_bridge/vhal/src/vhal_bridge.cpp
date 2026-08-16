#include "vhal_can_bridge/vhal_bridge.h"

namespace vhal_can_bridge {
namespace {
// TODO(aaos15): replace with generated AIDL constant references in platform integration.
constexpr int32_t kPerfVehicleSpeedPropertyId = 0x11600207;
constexpr int32_t kEngineRpmPropertyId = 0x11600305;      // placeholder
constexpr int32_t kCurrentGearPropertyId = 0x11400400;    // placeholder

// Demo vendor properties.
constexpr int32_t kVendorHvacFanLevelReadOnlyPropertyId = 0x21400100;
constexpr int32_t kVendorDriveModeRequestReadWritePropertyId = 0x21400101;
}  // namespace

std::optional<PropertyUpdate> VhalBridge::HandleFrame(const CanFrame& frame,
                                                      int64_t timestamp_ns) const {
    const auto decoded = decoder_.Decode(frame);
    if (!decoded.has_value()) {
        return std::nullopt;
    }

    switch (decoded->type) {
        case SignalType::kVehicleSpeedKph:
            return PropertyUpdate{
                    .property_id = kPerfVehicleSpeedPropertyId,
                    .value_type = PropertyValueType::kFloat,
                    .float_value = decoded->float_value,
                    .timestamp_ns = timestamp_ns,
            };
        case SignalType::kEngineRpm:
            return PropertyUpdate{
                    .property_id = kEngineRpmPropertyId,
                    .value_type = PropertyValueType::kFloat,
                    .float_value = decoded->float_value,
                    .timestamp_ns = timestamp_ns,
            };
        case SignalType::kGearPosition:
            return PropertyUpdate{
                    .property_id = kCurrentGearPropertyId,
                    .value_type = PropertyValueType::kInt32,
                    .int32_value = decoded->int32_value,
                    .timestamp_ns = timestamp_ns,
            };
        case SignalType::kHvacFanLevel:
            return PropertyUpdate{
                    .property_id = kVendorHvacFanLevelReadOnlyPropertyId,
                    .value_type = PropertyValueType::kInt32,
                    .int32_value = decoded->int32_value,
                    .timestamp_ns = timestamp_ns,
            };
    }

    return std::nullopt;
}

std::optional<PropertyUpdate> VhalBridge::HandleSetProperty(int32_t property_id,
                                                            int32_t int32_value,
                                                            int64_t timestamp_ns) {
    if (property_id != kVendorDriveModeRequestReadWritePropertyId) {
        return std::nullopt;
    }

    vendor_drive_mode_request_ = int32_value;

    // TODO(aaos15): send this command onto CAN TX path once write transport is connected.
    return PropertyUpdate{
            .property_id = kVendorDriveModeRequestReadWritePropertyId,
            .value_type = PropertyValueType::kInt32,
            .int32_value = vendor_drive_mode_request_,
            .timestamp_ns = timestamp_ns,
    };
}

}  // namespace vhal_can_bridge
