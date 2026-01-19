#pragma once

#include "util/vecmath.hpp"
#include <format>
#include "raytracer.hpp"

class Ray {
public:
    Point3f o{};
    Vector3f d{};
    Float t;

    // Remove t unless you truly need it
    Ray() = default;
    Ray(Point3f origin, Vector3f direction, Float time = 0.f)
    : o(origin), d(direction), t(time) {/* empty ctor */}

    std::string toString() const;
    Point3f operator()(Float t) const { return o + d*t; }
    bool hasNaN() const { return (o.hasNaN() || d.hasNaN()); }

};

inline std::string Ray::toString() const {
    return std::format("o={}\td={}", o.toString(), d.toString());
}
