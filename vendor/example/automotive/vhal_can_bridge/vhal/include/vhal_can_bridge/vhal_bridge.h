#pragma once

#include <cstdint>
#include <optional>

#include "vhal_can_bridge/can_frame.h"
#include "vhal_can_bridge/frame_decoder.h"

namespace vhal_can_bridge {

enum class PropertyValueType {
    kFloat,
    kInt32,
};

struct PropertyUpdate {
    int32_t property_id = 0;
    PropertyValueType value_type = PropertyValueType::kFloat;
    float float_value = 0.0f;
    int32_t int32_value = 0;
    int64_t timestamp_ns = 0;
};

class VhalBridge {
  public:
    std::optional<PropertyUpdate> HandleFrame(const CanFrame& frame, int64_t timestamp_ns) const;
    std::optional<PropertyUpdate> HandleSetProperty(int32_t property_id,
                                                    int32_t int32_value,
                                                    int64_t timestamp_ns);

  private:
    FrameDecoder decoder_;
    int32_t vendor_drive_mode_request_ = 0;
};

}  // namespace vhal_can_bridge
