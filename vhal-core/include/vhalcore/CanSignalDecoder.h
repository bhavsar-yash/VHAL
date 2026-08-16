#pragma once

#include <optional>
#include <unordered_map>
#include <vector>

#include "CanFrame.h"
#include "SignalModel.h"

namespace vhalcore {

class CanSignalDecoder {
  public:
    explicit CanSignalDecoder(std::vector<SignalDefinition> definitions);

    std::vector<DecodedSignalValue> decode(const CanFrame& frame) const;

  private:
    std::unordered_map<uint32_t, std::vector<SignalDefinition>> mDefinitionsByCanId;

    static std::optional<float> decodeRawSignal(const CanFrame& frame,
                                                const SignalDefinition& definition);
};

}  // namespace vhalcore
