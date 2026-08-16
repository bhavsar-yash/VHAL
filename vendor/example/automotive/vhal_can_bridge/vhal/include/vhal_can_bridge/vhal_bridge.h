#pragma once

#include <cstdint>
#include <optional>

#include "vhal_can_bridge/can_frame.h"
#include "vhal_can_bridge/frame_decoder.h"

namespace vhal_can_bridge {

struct PropertyUpdate {
    int32_t property_id = 0;
    float float_value = 0.0f;
    int64_t timestamp_ns = 0;
};

class VhalBridge {
  public:
    std::optional<PropertyUpdate> HandleFrame(const CanFrame& frame, int64_t timestamp_ns) const;

  private:
    FrameDecoder decoder_;
};

}  // namespace vhal_can_bridge
