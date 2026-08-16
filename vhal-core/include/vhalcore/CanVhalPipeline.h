#pragma once

#include <functional>
#include <vector>

#include "CanSignalDecoder.h"
#include "CanTransport.h"
#include "PropertyMapper.h"

namespace vhalcore {

using PropertyPublishCallback = std::function<void(const VehiclePropertyValue&)>;

class CanVhalPipeline {
  public:
    CanVhalPipeline(ICanTransport& transport, CanSignalDecoder decoder, PropertyMapper mapper);

    void start(PropertyPublishCallback publish);
    void stop();

  private:
    ICanTransport& mTransport;
    CanSignalDecoder mDecoder;
    PropertyMapper mMapper;
};

}  // namespace vhalcore
