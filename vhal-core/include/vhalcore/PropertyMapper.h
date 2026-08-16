#pragma once

#include <optional>

#include "SignalModel.h"
#include "VehiclePropertyValue.h"

namespace vhalcore {

class PropertyMapper {
  public:
    std::optional<VehiclePropertyValue> mapToProperty(const DecodedSignalValue& signal,
                                                      int64_t timestampNanos) const;
};

}  // namespace vhalcore
