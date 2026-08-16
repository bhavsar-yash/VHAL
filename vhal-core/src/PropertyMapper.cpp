#include "vhalcore/PropertyMapper.h"

namespace vhalcore {

std::optional<VehiclePropertyValue> PropertyMapper::mapToProperty(const DecodedSignalValue& signal,
                                                                  int64_t timestampNanos) const {
    if (signal.signalName == "vehicle_speed_mps") {
        return VehiclePropertyValue{.property = PropertyId::PERF_VEHICLE_SPEED,
                                    .areaId = 0,
                                    .timestampNanos = timestampNanos,
                                    .floatValues = {signal.value}};
    }

    return std::nullopt;
}

}  // namespace vhalcore
