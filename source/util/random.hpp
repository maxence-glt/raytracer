#pragma once

#include <random>
#include <type_traits>

namespace Rand {

inline std::mt19937_64& engine() {
    //static thread_local std::mt19937_64 e{ std::random_device{}() };
    static thread_local std::mt19937_64 e{ 0xDEADBEEFCAFEBABEULL }; // <- unseeded
    return e;
}

template <typename T>
requires std::is_floating_point_v<T>
inline T random() {
    std::uniform_real_distribution<T> dis(T(0), T(1));
    static int i = 0;
    T out = dis(engine());

    return out;
}

template <typename T>
requires std::is_floating_point_v<T>
inline T random(T min, T max) {
    return min + (max - min)*random<T>();
}

} // namespace Rand
