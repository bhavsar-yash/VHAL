#pragma once

#include <functional>

#include "vhal_can_bridge/can_frame.h"

namespace vhal_can_bridge {

class CanTransport {
  public:
    using FrameHandler = std::function<void(const CanFrame&)>;

    virtual ~CanTransport() = default;
    virtual bool Start(FrameHandler handler) = 0;
    virtual void Stop() = 0;
};

}  // namespace vhal_can_bridge
