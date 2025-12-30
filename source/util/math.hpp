#pragma once

#include <cmath>
#include "../raytracer.hpp"

constexpr Float ShadowEpsilon = 0.0001f;
constexpr Float Pi            = 3.14159265358979323846;
constexpr Float InvPi         = 0.31830988618379067154;
constexpr Float Inv2Pi        = 0.15915494309189533577;
constexpr Float Inv4Pi        = 0.07957747154594766788;
constexpr Float PiOver2       = 1.57079632679489661923;
constexpr Float PiOver4       = 0.78539816339744830961;
constexpr Float Sqrt2         = 1.41421356237309504880;
constexpr Float infinity      = std::numeric_limits<Float>::infinity();

template <typename T>
inline constexpr T sqr(T x) { return x*x; }

template <typename T, typename U, typename V>
inline constexpr T clamp(T val, U low, V high) {
    if (val < low)
        return T(low);
    else if (val > high)
        return T(high);
    else
        return val;
}

constexpr inline Float radians(Float deg) { return (Pi / 180) * deg; }
constexpr inline Float degrees(Float rad) { return (180 / Pi) * rad; }

inline constexpr Float safeASin(Float x) { return std::asin(clamp(x, -1, 1)); }
inline constexpr Float safeACos(Float x) { return std::acos(clamp(x, -1, 1)); }

template <typename Ta, typename Tb, typename Tc, typename Td>
inline auto differenceOfProducts(Ta a, Tb b, Tc c, Td d) {
    auto cd = c * d;
    auto differenceOfProducts = std::fma(a, b, -cd);
    auto error = std::fma(-c, d, cd);
    return differenceOfProducts + error;
}

template <typename Ta, typename Tb, typename Tc, typename Td>
inline auto sumOfProducts(Ta a, Tb b, Tc c, Td d) {
    auto cd = c * d;
    auto sumOfProducts = std::fma(a, b, cd);
    auto error = std::fma(c, d, -cd);
    return sumOfProducts + error;
}
