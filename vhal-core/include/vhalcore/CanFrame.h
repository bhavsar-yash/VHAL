#pragma once

#include <array>
#include <cstdint>

namespace vhalcore {

struct CanFrame {
    uint32_t id = 0;
    uint8_t dlc = 0;
    std::array<uint8_t, 8> data{};
};

}  // namespace vhalcore
