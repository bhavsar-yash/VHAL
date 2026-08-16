#pragma once

#include <array>
#include <cstdint>

namespace vhal_can_bridge {

struct CanFrame {
    uint32_t can_id = 0;
    uint8_t dlc = 0;
    std::array<uint8_t, 8> data{};
};

}  // namespace vhal_can_bridge
