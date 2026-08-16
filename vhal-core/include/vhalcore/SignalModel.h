#pragma once

#include <cstdint>
#include <string>

namespace vhalcore {

struct SignalDefinition {
    std::string name;
    uint32_t canId = 0;
    uint8_t startByte = 0;
    uint8_t lengthBytes = 0;
    float scale = 1.0F;
    float offset = 0.0F;
    bool littleEndian = true;
};

struct DecodedSignalValue {
    std::string signalName;
    float value = 0.0F;
};

}  // namespace vhalcore
