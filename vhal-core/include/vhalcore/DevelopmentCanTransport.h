#pragma once

#include <atomic>

#include "CanTransport.h"

namespace vhalcore {

class DevelopmentCanTransport : public ICanTransport {
  public:
    void start(CanFrameCallback callback) override;
    void stop() override;

  private:
    std::atomic<bool> mRunning{false};
};

}  // namespace vhalcore
