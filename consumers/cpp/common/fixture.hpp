// The documents both applications write, each through its own usage: the same keys, the same
// values, so that what the library reads back can be compared across the two.
#pragma once

#include "shop_store_data.hpp"

#include <utility>
#include <vector>

namespace fixture {

inline std::vector<std::pair<shop::store::ProductKey, shop::store::ProductProperties>> products() {
    return {
        {shop::store::ProductKey{Viper::UUId::parse("0b0f8a52-58a3-4bd1-9b8e-1f4a0f3f6a01")},
         shop::store::ProductProperties{"drill", 129.5f, {"tool", "electric"}}},
        {shop::store::ProductKey{Viper::UUId::parse("7c2d9e10-4b11-4c2a-8d33-2a5b6c7d8e02")},
         shop::store::ProductProperties{"hammer", 19.0f, {"tool"}}},
    };
}

inline std::vector<std::pair<shop::store::PartKey, shop::store::PartProperties>> parts() {
    return {
        {shop::store::PartKey{Viper::UUId::parse("3e4f5a6b-7c8d-4e9f-a0b1-c2d3e4f5a603")},
         shop::store::PartProperties{"bit-8mm", 12}},
    };
}

} // namespace fixture
