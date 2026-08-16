#include "vhalcore/CanSignalDecoder.h"

namespace vhalcore {

CanSignalDecoder::CanSignalDecoder(std::vector<SignalDefinition> definitions) {
    for (const auto& definition : definitions) {
        mDefinitionsByCanId[definition.canId].push_back(definition);
    }
}

std::vector<DecodedSignalValue> CanSignalDecoder::decode(const CanFrame& frame) const {
    std::vector<DecodedSignalValue> decoded;

    const auto it = mDefinitionsByCanId.find(frame.id);
    if (it == mDefinitionsByCanId.end()) {
        return decoded;
    }

    for (const auto& definition : it->second) {
        const auto value = decodeRawSignal(frame, definition);
        if (!value.has_value()) {
            continue;
        }

        decoded.push_back({.signalName = definition.name, .value = *value});
    }

    return decoded;
}

std::optional<float> CanSignalDecoder::decodeRawSignal(const CanFrame& frame,
                                                       const SignalDefinition& definition) {
    if (!definition.littleEndian || definition.lengthBytes == 0 || definition.lengthBytes > 4) {
        return std::nullopt;
    }
    if (definition.startByte + definition.lengthBytes > frame.dlc) {
        return std::nullopt;
    }

    uint32_t raw = 0;
    for (uint8_t i = 0; i < definition.lengthBytes; ++i) {
        raw |= static_cast<uint32_t>(frame.data[definition.startByte + i]) << (i * 8U);
    }

    return (static_cast<float>(raw) * definition.scale) + definition.offset;
}

}  // namespace vhalcore
