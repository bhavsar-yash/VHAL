#pragma once

#include <memory>
#include <vector>

#include "vhalcore/CanVhalPipeline.h"
#include "vhalcore/SignalModel.h"

namespace vhalaidl {

struct PropertyConfigScaffold {
    vhalcore::PropertyId property;
    int32_t areaId;
    bool onChange;
};

class CanVhalService {
  public:
    explicit CanVhalService(vhalcore::ICanTransport& transport);

    void start();
    void stop();

  private:
    void publishToVehicleHal(const vhalcore::VehiclePropertyValue& value);
    static std::vector<PropertyConfigScaffold> buildPropertyConfigs();

    vhalcore::CanVhalPipeline mPipeline;
    std::vector<PropertyConfigScaffold> mPropertyConfigs;
};

}  // namespace vhalaidl
