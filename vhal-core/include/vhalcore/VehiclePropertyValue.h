#pragma once

#include <cstdint>
#include <vector>

namespace vhalcore {

enum class PropertyId : int32_t {
    PERF_VEHICLE_SPEED = 0x11600207,
};

struct VehiclePropertyValue {
    PropertyId property;
    int32_t areaId = 0;
    int64_t timestampNanos = 0;
    std::vector<float> floatValues;
};

}  // namespace vhalcore
