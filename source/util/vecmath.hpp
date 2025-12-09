#pragma once

#include "check.h"

using std::isnan;

/* TODO: Possible additions
*
* FMA(a, b, c), which takes three tuples and returns the result of a component-wise fused multiply-add a*b + c.
*
* Permute(a, perm), which returns the permutation of the tuple according to an array of indices.
8
* HProd(a), which returns the horizontal product—the component values multiplied together. 
*/

template <template <typename> class Child, typename T>
class Tuple3 {
public:
    T x{}, y{}, z{};
    static constexpr int nDimensions = 3;

    Tuple3() = default;
    Tuple3(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!hasNaN()); }

    Tuple3(Child<T> c) {
        DCHECK(!c.HasNaN());
        x = c.x;
        y = c.y;
        z = c.z;
    }

    Child<T> &operator=(Child<T> c) {
        DCHECK(!c.HasNaN());
        x = c.x;
        y = c.y;
        z = c.z;
        return static_cast<Child<T> &>(*this);
    }

    bool hasNaN() const { return isnan(x) || isnan(y) || isnan(z); }

    T operator[](int i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    T &operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    template <typename U>
    auto operator+(Child<U> c) const -> Child<decltype(T{} + U{})> {
        return {x + c.x, y + c.y, z + c.z};
    }

    template <typename U>
    Child<T> &operator+=(Child<U> c) {
        DCHECK(!c.hasNaN());
        x += c.x;
        y += c.y;
        z += c.z;
        return static_cast<Child<T> &>(*this);
    }

    template <typename U>
    auto operator-(Child<U> c) const -> Child<decltype(T{} - U{})> {
        DCHECK(!c.hasNaN());
        return {x - c.x, y - c.y, z - c.z};
    }

    template <typename U>
    Child<T> &operator-=(Child<U> c) {
        DCHECK(!c.hasNaN());
        x -= c.x;
        y -= c.y;
        z -= c.z;
        return static_cast<Child<T> &>(*this);
    }

    bool operator==(Child<T> c) const { return x == c.x && y == c.y && z == c.z; }
    bool operator!=(Child<T> c) const { return x != c.x || y != c.y || z != c.z; }

    template <typename U>
    auto operator*(U s) const -> Child<decltype(T{} * U{})> {
        return {s * x, s * y, s * z};
    }

    template <typename U>
    Child<T> &operator*=(U s) {
        DCHECK(!isNaN(s));
        x *= s;
        y *= s;
        z *= s;
        return static_cast<Child<T> &>(*this);
    }

    template <typename U>
    auto operator/(U d) const -> Child<decltype(T{} / U{})> {
        DCHECK_NE(d, 0);
        return {x / d, y / d, z / d};
    }

    template <typename U>
    Child<T> &operator/=(U d) {
        DCHECK_NE(d, 0);
        x /= d;
        y /= d;
        z /= d;
        return static_cast<Child<T> &>(*this);
    }

    Child<T> operator-() const { return {-x, -y, -z}; }

    std::string toString() const { 
        return std::format("x = {}\ty = {}\tz = {}", x, y, z); 
    }

};

// Tuple3 Inline Functions
template <template <class> class C, typename T, typename U>
inline auto operator*(U s, Tuple3<C, T> t) -> C<decltype(T{} * U{})> {
    return t * s;
}

template <template <class> class C, typename T>
inline C<T> abs(Tuple3<C, T> t) {
    using std::abs;
    return {abs(t[0]), abs(t[1]), abs(t[2])};
}

template <template <class> class C, typename T>
inline C<T> ceil(Tuple3<C, T> t) {
    using std::ceil;
    return {ceil(t[0]), ceil(t[1]), ceil(t[2])};
}

template <template <class> class C, typename T>
inline C<T> floor(Tuple3<C, T> t) {
    using std::floor;
    return {floor(t[0]), floor(t[1]), floor(t[2])};
}

template <template <class> class C, typename T>
inline auto lerp(float t, Tuple3<C, T> t0, Tuple3<C, T> t1) {
    return (1 - t) * t0 + t * t1;
}

template <template <class> class C, typename T>
inline C<T> min(Tuple3<C, T> t1, Tuple3<C, T> t2) {
    using std::min;
    return {min(t1.x, t2.x), min(t1.y, t2.y), min(t1.z, t2.z)};
}

template <template <class> class C, typename T>
inline T minComponentValue(Tuple3<C, T> t) {
    using std::min;
    return min({t.x, t.y, t.z});
}

template <template <class> class C, typename T>
inline int minComponentIndex(Tuple3<C, T> t) {
    return (t.x < t.y) ? ((t.x < t.z) ? 0 : 2) : ((t.y < t.z) ? 1 : 2);
}

template <template <class> class C, typename T>
inline C<T> max(Tuple3<C, T> t1, Tuple3<C, T> t2) {
    using std::max;
    return {max(t1.x, t2.x), max(t1.y, t2.y), max(t1.z, t2.z)};
}

template <template <class> class C, typename T>
inline T maxComponentValue(Tuple3<C, T> t) {
    using std::max;
    return max({t.x, t.y, t.z});
}

template <template <class> class C, typename T>
inline int maxComponentIndex(Tuple3<C, T> t) {
    return (t.x > t.y) ? ((t.x > t.z) ? 0 : 2) : ((t.y > t.z) ? 1 : 2);
}

template <typename T>
class Vector3 : public Tuple3<Vector3, T> {
public:
    using Tuple3<Vector3, T>::x;
    using Tuple3<Vector3, T>::y;
    using Tuple3<Vector3, T>::z;

    Vector3() = default;
    Vector3(T x, T y, T z) : Tuple3<Vector3, T>(x, y, z) {}

    template <typename U>
    explicit Vector3(Vector3<U> v)
    : Tuple3<Vector3, T>(T(v.x), T(v.y), T(v.z)) {}

    /*
    template <typename U>
    explicit Vector3(Point3<U> p);

    template <typename U>
    explicit Vector3(Normal3<U> n);
    */
};

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
