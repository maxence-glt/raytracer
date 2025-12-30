#pragma once

#include "interval.h"
#include "util/vecmath.hpp"
#include "util/profiler.hpp"
#include "raytracer.hpp"

using color = Vector3f;

inline Float linear_to_gamma(Float linear_component) {
    if (linear_component > 0) return std::sqrt(linear_component);
    return 0;
}

inline void write_color(std::ostream &out, const color &pixel_color) {
    PROFILE_SCOPE("write_color");
    auto r = pixel_color[0];
    auto g = pixel_color[1];
    auto b = pixel_color[2];

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
