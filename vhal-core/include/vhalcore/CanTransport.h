#pragma once

#include <functional>

#include "CanFrame.h"

namespace vhalcore {

using CanFrameCallback = std::function<void(const CanFrame&)>;

class ICanTransport {
  public:
    virtual ~ICanTransport() = default;
    virtual void start(CanFrameCallback callback) = 0;
    virtual void stop() = 0;
};

}  // namespace vhalcore
