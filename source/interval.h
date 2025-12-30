#pragma once

#include "util/math.hpp"

struct interval {
    Float min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(Float min, Float max) : min(min), max(max) {}

    Float size() const {
        return max - min;
    }

    bool contains(Float x) const {
        return min <= x && x <= max;
    }

    bool surrounds(Float x) const {
        return min < x && x < max;
    }

    Float clamp(Float x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};

inline const interval interval::empty = interval(+infinity, -infinity);
inline const interval interval::universe = interval(-infinity, +infinity);
