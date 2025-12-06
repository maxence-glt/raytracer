
constexpr float ShadowEpsilon = 0.0001f;
constexpr float Pi = 3.14159265358979323846;
constexpr float InvPi = 0.31830988618379067154;
constexpr float Inv2Pi = 0.15915494309189533577;
constexpr float Inv4Pi = 0.07957747154594766788;
constexpr float PiOver2 = 1.57079632679489661923;
constexpr float PiOver4 = 0.78539816339744830961;
constexpr float Sqrt2 = 1.41421356237309504880;

template <typename T, typename U, typename V>
inline constexpr T clamp(T val, U low, V high) {
    if (val < low)
        return T(low);
    else if (val > high)
        return T(high);
    else
        return val;
}

constexpr inline float radians(float deg) { return (Pi / 180) * deg; }
constexpr inline float degrees(float rad) { return (180 / Pi) * rad; }
