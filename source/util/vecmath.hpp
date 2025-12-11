#pragma once

#include "check.h"
#include "math.hpp"
#include <__ostream/print.h>

using std::isnan;

/* TODO: Possible additions
*
* FMA(a, b, c), which takes three tuples and returns the result of a component-wise fused multiply-add a*b + c.
*
* Permute(a, perm), which returns the permutation of the tuple according to an array of indices.
8
* HProd(a), which returns the horizontal product—the component values multiplied together. 
*/

template <typename T>
class Vector3;
template <typename T>
class Point3;
template <typename T>
class Normal3;

template <typename T>
struct TupleLength { using type = float; };

template <>
struct TupleLength<double> { using type = double; };

template <>
struct TupleLength<long double> { using type = long double; };

template <template <typename> class Child, typename T>
class Tuple3 {
public:
    T x{}, y{}, z{};
    static constexpr int nDimensions = 3;

    Tuple3() = default;
    Tuple3(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!hasNaN()); }

    Tuple3(Child<T> c) {
        DCHECK(!c.hasNaN());
        x = c.x;
        y = c.y;
        z = c.z;
    }

    Child<T> &operator=(Child<T> c) {
        DCHECK(!c.hasNaN());
        x = c.x;
        y = c.y;
        z = c.z;
        return static_cast<Child<T> &>(*this);
    }

    bool hasNaN() const { return isnan(x) || isnan(y) || isnan(z); }

    T operator[](int i) const {
        DCHECK(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    T &operator[](int i) {
        DCHECK(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    template <typename U>
    auto operator+(Child<U> c) const -> Child<decltype(T{} + U{})> {
        DCHECK(!c.hasNaN());
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

    template <typename U>
    explicit Vector3(Point3<U> p);

    template <typename U>
    explicit Vector3(Normal3<U> n);
};

template <typename T>
template <typename U>
Vector3<T>::Vector3(Point3<U> p) : Tuple3<Vector3, T>(T(p.x), T(p.y), T(p.z)) {}


using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;

template <typename T>
inline T lengthSquared(Vector3<T> v) { return v.x*v.x + v.y*v.y + v.z*v.z; }

template <typename T>
inline auto length(Vector3<T> v) -> typename TupleLength<T>::type {
    using std::sqrt;
    return sqrt(lengthSquared(v));
}

template <typename T>
inline auto normalize(Vector3<T> v) { return v / length(v); };

template <typename T>
inline T dot(Vector3<T> v, Vector3<T> w) {
    DCHECK(!v1.hasNaN() && !v2.hasNaN());
    return v.x*w.x + v.y*w.y + v.z*w.z;
}

template <typename T>
inline float angleBetween(Vector3<T> v1, Vector3<T> v2) {
    if (dot(v1, v2) < 0)
        return Pi - 2 * safeASin(length(v1 + v2) / 2);
    else
        return 2 * safeASin(length(v2 - v1) / 2);
}

template <typename T>
inline Vector3<T> gramSchmidt(Vector3<T> v, Vector3<T> w) {
    return v - dot(v, w) * w;
}

template <typename T>
inline Vector3<T> cross(Vector3<T> v, Vector3<T> w) {
    return {DifferenceOfProducts(v.y, w.z, v.z, w.y),
            DifferenceOfProducts(v.z, w.x, v.x, w.z),
            DifferenceOfProducts(v.x, w.y, v.y, w.x)};
}

template <typename T>
inline void CoordinateSystem(Vector3<T> v1, Vector3<T> *v2, Vector3<T> *v3) {
    float sign = std::copysign(1.0, v1.z);
    float a = -1 / (sign + v1.z);
    float b = v1.x * v1.y * a;
    *v2 = Vector3<T>(1 + sign * (v1.x*v1.x) * a, sign * b, -sign * v1.x);
    *v3 = Vector3<T>(b, sign + (v1.y*v1.y) * a, -v1.y);
}

template <typename T>
class Point3 : public Tuple3<Point3, T> {
public:
    using Tuple3<Point3, T>::x;
    using Tuple3<Point3, T>::y;
    using Tuple3<Point3, T>::z;
    using Tuple3<Point3, T>::operator+;
    using Tuple3<Point3, T>::operator+=;
    using Tuple3<Point3, T>::operator*;
    using Tuple3<Point3, T>::operator*=;

    Point3() = default;
    Point3(T x, T y, T z) : Tuple3<Point3, T>(x, y, z) {}

    Point3<T> operator-() const { return {-x, -y, -z}; }

    template <typename U>
    explicit Point3(Point3<U> p)
    : Tuple3<Point3, T>(T(p.x), T(p.y), T(p.z)) {}

    template <typename U>
    explicit Point3(Vector3<U> v)
    : Tuple3<Point3, T>(T(v.x), T(v.y), T(v.z)) {}

    template <typename U>
    auto operator+(Vector3<U> v) const -> Point3<decltype(T{} + U{})> {
        DCHECK(!v.hasNaN());
        return {x + v.x, y + v.y, z + v.z};
    }

    template <typename U>
    Point3<T> &operator+=(Vector3<U> v) {
        DCHECK(!v.hasNaN());
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    template <typename U>
    auto operator-(Vector3<U> v) const -> Point3<decltype(T{} - U{})> {
        DCHECK(!v.hasNaN());
        return {x - v.x, y - v.y, z - v.z};
    }

    template <typename U>
    Point3<T> &operator-=(Vector3<U> v) {
        DCHECK(!v.hasNaN());
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    template <typename U>
    auto operator-(Point3<U> p) const -> Vector3<decltype(T{} - U{})> {
        DCHECK(!p.hasNaN());
        return {x - p.x, y - p.y, z - p.z};
    }
};

using Point3f = Point3<float>;
using Point3i = Point3<int>;

template <typename T>
auto distance(Point3<T> p1, Point3<T> p2) { return length(p1 - p2); }

template <typename T>
auto distanceSquared(Point3<T> p1, Point3<T> p2) {
    return lengthSquared(p1 - p2);
}

template <typename T>
class Normal3 : public Tuple3<Normal3, T> {
public:
    using Tuple3<Normal3, T>::x;
    using Tuple3<Normal3, T>::y;
    using Tuple3<Normal3, T>::z;
    using Tuple3<Normal3, T>::hasNaN;
    using Tuple3<Normal3, T>::operator+;
    using Tuple3<Normal3, T>::operator*;
    using Tuple3<Normal3, T>::operator*=;

    Normal3() = default;
    Normal3(T x, T y, T z) : Tuple3<Normal3, T>(x, y, z) {}

    template <typename U>
    explicit Normal3<T>(Normal3<U> v)
    : Tuple3<Normal3, T>(T(v.x), T(v.y), T(v.z)) {}

    template <typename U>
    explicit Normal3<T>(Vector3<U> v)
    : Tuple3<Normal3, T>(T(v.x), T(v.y), T(v.z)) {}
};

using Normal3f = Normal3<float>;
using Normal3i = Normal3<int>;

template <typename T>
inline T dot(Normal3<T> v, Normal3<T> w) {
    DHECK(!v.hasNaN() && !w.hasNaN());
    return v.x*w.x + v.y*w.y + v.z*w.z;
}

template <typename T>
inline Vector3<T> cross(Vector3<T> v1, Normal3<T> v2) {
    DCHECK(!v1.hasNaN() && !v2.hasNaN());
    return {differenceOfProducts(v1.y, v2.z, v1.z, v2.y),
            differenceOfProducts(v1.z, v2.x, v1.x, v2.z),
            differenceOfProducts(v1.x, v2.y, v1.y, v2.x)};
}

template <typename T>
inline Vector3<T> cross(Normal3<T> v1, Vector3<T> v2) {
    DCHECK(!v1.hasNaN() && !v2.hasNaN());
    return {DifferenceOfProducts(v1.y, v2.z, v1.z, v2.y),
            DifferenceOfProducts(v1.z, v2.x, v1.x, v2.z),
            DifferenceOfProducts(v1.x, v2.y, v1.y, v2.x)};
}

template <typename T>
Normal3<T> faceForward(Normal3<T> n, Vector3<T> v) {
    return (dot(n, v) < 0.f) ? -n : n;
}
