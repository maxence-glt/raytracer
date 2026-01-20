#pragma once

#include "interval.h"
#include "util/vecmath.hpp"
#include "util/profiler.hpp"
#include "raytracer.hpp"

#include <OpenImageIO/imageio.h>

using color = Vector3f;

inline Float linear_to_gamma(Float linear_component) {
    if (linear_component > 0) return std::sqrt(linear_component);
    return 0;
}

inline void write_color(std::vector<float> &out, const color &pixel_color, int index) {
    PROFILE_SCOPE("write_color");
    auto r = pixel_color[0];
    auto g = pixel_color[1];
    auto b = pixel_color[2];

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.000, 0.999);
    float rbyte = intensity.clamp(r);
    float gbyte = intensity.clamp(g);
    float bbyte = intensity.clamp(b);

    out[index + 0] = rbyte;
    out[index + 1] = gbyte;
    out[index + 2] = bbyte;
}
