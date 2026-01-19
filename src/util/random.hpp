#pragma once

#include <cstdint>
#include <type_traits>

namespace Rand {

inline uint64_t& state() {
    static thread_local uint64_t s = 0xDEADBEEF;
    return s;
}

inline uint64_t xorshift64() {
    uint64_t x = state();

    if (x == 0) x = 0xDEADBEEF;

    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;

    state() = x;
    return x;
}

template <typename T>
requires std::is_floating_point_v<T>
inline T random() {
    uint64_t u = xorshift64();

    if constexpr (std::is_same_v<T, float>) {
        constexpr float inv = 1.0f / 16777216.0f;
        return float(u >> 40) * inv;
    } else {
        constexpr double inv = 1.0 / 9007199254740992.0;
        return double(u >> 11) * inv;
    }
}

template <typename T>
requires std::is_floating_point_v<T>
inline T random(T min, T max) {
    return min + (max - min) * random<T>();
}

} // namespace Rand
