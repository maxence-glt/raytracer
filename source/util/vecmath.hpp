#pragma once

#include "math.hpp"
#include "check.h"
#include "random.hpp"
#include "../raytracer.hpp"

using std::isnan;

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

    // copy-construct from Child
    Tuple3(const Child<T> &c) {
        DCHECK(!c.hasNaN());
        x = c.x; y = c.y; z = c.z;
    }

    Child<T> &operator=(const Child<T> &c) {
        DCHECK(!c.hasNaN());
        x = c.x; y = c.y; z = c.z;
        return static_cast<Child<T>&>(*this);
    }

    bool hasNaN() const { return isnan(x) || isnan(y) || isnan(z); }

    T operator[](const int i) const {
        DCHECK(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    T &operator[](const int i) {
        DCHECK(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    template <typename U>
    auto operator+(const Child<U> &c) const -> Child<decltype(T{} + U{})> {
        DCHECK(!c.hasNaN());
        return {x + c.x, y + c.y, z + c.z};
    }

    template <typename U>
    Child<T>& operator+=(const Child<U> &c) {
        DCHECK(!c.hasNaN());
        x += c.x; y += c.y; z += c.z;
        return static_cast<Child<T>&>(*this);
    }

    template <typename U>
    auto operator-(const Child<U> &c) const -> Child<decltype(T{} - U{})> {
        DCHECK(!c.hasNaN());
        return {x - c.x, y - c.y, z - c.z};
    }

    template <typename U>
    Child<T>& operator-=(const Child<U> &c) {
        DCHECK(!c.hasNaN());
        x -= c.x; y -= c.y; z -= c.z;
        return static_cast<Child<T>&>(*this);
    }

    bool operator==(const Child<T> &c) const { return x == c.x && y == c.y && z == c.z; }
    bool operator!=(const Child<T> &c) const { return !(*this == c); }

    template <typename S>
    requires std::is_arithmetic_v<std::remove_reference_t<S>>
    auto operator*(S s) const -> Child<decltype(T{} * S{})> {
        return {x * s, y * s, z * s};
    }

    template <typename S>
    requires std::is_arithmetic_v<std::remove_reference_t<S>>
    Child<T>& operator*=(S s) {
        if constexpr (std::is_floating_point_v<std::remove_reference_t<S>>)
            DCHECK(!isnan(s));
        x *= s; y *= s; z *= s;
        return static_cast<Child<T>&>(*this);
    }

    // tuple (Hadamard) multiply
    template <typename U>
    auto operator*(const Child<U> &c) const -> Child<decltype(T{} * U{})> {
        DCHECK(!c.hasNaN());
        return {x * c.x, y * c.y, z * c.z};
    }

    template <typename U>
    Child<T>& operator*=(const Child<U> &c) {
        DCHECK(!c.hasNaN());
        x *= c.x; y *= c.y; z *= c.z;
        return static_cast<Child<T>&>(*this);
    }

    template <typename U>
    requires std::is_arithmetic_v<std::remove_reference_t<U>>
    auto operator/(U d) const -> Child<decltype(T{} / U{})> {
        DCHECK_NE(d, 0);
        return {x / d, y / d, z / d};
    }

    template <typename U>
    requires std::is_arithmetic_v<std::remove_reference_t<U>>
    Child<T>& operator/=(U d) {
        DCHECK_NE(d, 0);
        x /= d; y /= d; z /= d;
        return static_cast<Child<T>&>(*this);
    }

    Child<T> operator-() const { return {-x, -y, -z}; }

    std::string toString() const { 
        return std::format("x = {}\ty = {}\tz = {}", x, y, z); 
    }

    static Child<T> random() {
        return Child<T>(Rand::random<T>(), Rand::random<T>(), Rand::random<T>());
    }

    static Child<T> random(T min, T max) {
        return Child<T>(Rand::random<T>(min, max), 
                        Rand::random<T>(min, max), 
                        Rand::random<T>(min, max));
    }

    bool near_zero() const {
        auto s = 1e-8;
        return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
    }
};


template <template <class> class C, typename T, typename U>
requires std::is_arithmetic_v<std::remove_reference_t<U>>
inline auto operator*(U s, const Tuple3<C, T>& t) -> C<decltype(T{} * U{})> {
    return t * s;
}

template <template <class> class C, typename T>
inline C<T> abs(const Tuple3<C, T> &t) {
    using std::abs; 
    return {abs(t[0]), abs(t[1]), abs(t[2])}; 
}

template <template <class> class C, typename T>
inline C<T> ceil(const Tuple3<C, T> &t) { 
    using std::ceil; 
    return {ceil(t[0]), ceil(t[1]), ceil(t[2])}; 
}

template <template <class> class C, typename T>
inline C<T> floor(const Tuple3<C, T> &t) { 
    using std::floor; 
    return {floor(t[0]), floor(t[1]), floor(t[2])}; 
}

template <template <class> class C, typename T>
inline auto lerp(Float t, const Tuple3<C, T> &t0, const Tuple3<C, T> &t1) {
    return (1 - t) * t0 + t * t1;
}

template <template <class> class C, typename T>
inline C<T> min(const Tuple3<C, T> &t1, const Tuple3<C, T> &t2) {
    using std::min;
    return {min(t1.x, t2.x), min(t1.y, t2.y), min(t1.z, t2.z)};
}

template <template <class> class C, typename T>
inline C<T> max(const Tuple3<C, T> &t1, const Tuple3<C, T> &t2) {
    using std::max;
    return {max(t1.x, t2.x), max(t1.y, t2.y), max(t1.z, t2.z)};
}

template <template <class> class C, typename T>
inline T minComponentValue(const Tuple3<C, T> &t) { 
    using std::min; 
    return min({t.x, t.y, t.z}); 
}

template <template <class> class C, typename T>
inline T maxComponentValue(const Tuple3<C, T> &t) { 
    using std::max; 
    return max({t.x, t.y, t.z}); 
}

template <template <class> class C, typename T>
inline int minComponentIndex(const Tuple3<C, T> &t) { 
    return (t.x < t.y) ? ((t.x < t.z) ? 0 : 2) : ((t.y < t.z) ? 1 : 2); 
}

template <template <class> class C, typename T>
inline int maxComponentIndex(const Tuple3<C, T> &t) { 
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
    explicit Vector3(const Vector3<U> &v)
    : Tuple3<Vector3, T>(T(v.x), T(v.y), T(v.z)) {}

    template <typename U>
    explicit Vector3(const Point3<U> &p);

    template <typename U>
    explicit Vector3(const Normal3<U> &n);
};

template <typename T>
template <typename U>
Vector3<T>::Vector3(const Point3<U> &p)
    : Tuple3<Vector3, T>(T(p.x), T(p.y), T(p.z)) {}

template <typename T>
template <typename U>
Vector3<T>::Vector3(const Normal3<U> &n)
    : Tuple3<Vector3, T>(T(n.x), T(n.y), T(n.z)) {}

template <typename T>
inline T lengthSquared(const Vector3<T> &v) { return v.x*v.x + v.y*v.y + v.z*v.z; }

template <typename T>
inline auto length(const Vector3<T> &v) -> typename TupleLength<T>::type {
    using std::sqrt;
    return sqrt(lengthSquared(v));
}

template <typename T>
inline T dot(const Vector3<T> &v, const Vector3<T> &w) {
    DCHECK(!v.hasNaN() && !w.hasNaN());
    return v.x*w.x + v.y*w.y + v.z*w.z;
}

template <typename T>
inline Float angleBetween(const Vector3<T> &v1, const Vector3<T> &v2) {
    if (dot(v1, v2) < 0)
        return Pi - 2 * safeASin(length(v1 + v2) / 2);
    else
        return 2 * safeASin(length(v2 - v1) / 2);
}

template <typename T>
inline Vector3<T> gramSchmidt(const Vector3<T> &v, const Vector3<T> &w) {
    return v - dot(v, w) * w;
}

template <typename T>
inline Vector3<T> reflect(const Vector3<T> &v, const Vector3<T> &w) {
    return v - 2*dot(v, w) * w;
}

template <typename T>
inline Vector3<T> reflect(const Vector3<T> &v, const Normal3<T> &n) {
    return reflect(v, Vector3<T>(n));
}

template <typename T>
inline Vector3<T> refract(const Vector3<T> &uv, const Normal3<T> &n, T etai_over_etat) {
    Vector3<T> nn(n);

    T cos_theta = std::min(T(dot(-uv, nn)), T(1));
    Vector3<T> r_out_perp = etai_over_etat * (uv + cos_theta * nn);

    T k = T(1) - lengthSquared(r_out_perp);
    Vector3<T> r_out_parallel = -std::sqrt(std::fabs(k)) * nn;

    return r_out_perp + r_out_parallel;
}

template <typename T>
inline Vector3<T> cross(const Vector3<T> &v, const Vector3<T> &w) {
    DCHECK(!v.hasNaN() && !w.hasNaN());
    return {differenceOfProducts(v.y, w.z, v.z, w.y),
            differenceOfProducts(v.z, w.x, v.x, w.z),
            differenceOfProducts(v.x, w.y, v.y, w.x)};
}

template <typename T>
inline Vector3<T> unit_vector(const Vector3<T> &v) {
    return v / length(v);
}

template <typename T>
inline Vector3<T> random_unit_vector() {
    while (true) {
        auto p = Vector3<T>::random(-1, 1);

        auto lensq = lengthSquared(p);
        if (1e-160 < lensq && lensq <= 1) return p / std::sqrt(lensq);
    }
}

template <typename T>
inline Vector3<T> random_in_unit_disk() {
    while (true) {
        auto p = Vector3<T>(Rand::random<T>(T(-1), T(1)),
                            Rand::random<T>(T(-1), T(1)),
                            T(0));
        if (lengthSquared(p) < 1)
            return p;
    }
}

template <typename T>
inline Vector3<T> random_on_hemisphere(const Vector3<T> &normal) {
    Vector3<T> on_unit_sphere = random_unit_vector<T>();
    if (dot(on_unit_sphere, normal) > 0.0) 
        return on_unit_sphere;
    return -on_unit_sphere;
}

template <typename T>
inline void CoordinateSystem(const Vector3<T> &v1, Vector3<T> *v2, Vector3<T> *v3) {
    Float sign = std::copysign(1.0, v1.z);
    Float a = -1 / (sign + v1.z);
    Float b = v1.x * v1.y * a;
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
    explicit Point3(const Point3<U> &p)
    : Tuple3<Point3, T>(T(p.x), T(p.y), T(p.z)) {}

    template <typename U>
    explicit Point3(const Vector3<U> &v)
    : Tuple3<Point3, T>(T(v.x), T(v.y), T(v.z)) {}

    template <typename U>
    auto operator+(const Vector3<U> &v) const -> Point3<decltype(T{} + U{})> {
        DCHECK(!v.hasNaN());
        return {x + v.x, y + v.y, z + v.z};
    }

    template <typename U>
    Point3<T> &operator+=(const Vector3<U> &v) {
        DCHECK(!v.hasNaN());
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    template <typename U>
    auto operator-(const Vector3<U> &v) const -> Point3<decltype(T{} - U{})> {
        DCHECK(!v.hasNaN());
        return {x - v.x, y - v.y, z - v.z};
    }

    template <typename U>
    Point3<T> &operator-=(const Vector3<U> &v) {
        DCHECK(!v.hasNaN());
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    template <typename U>
    auto operator-(const Point3<U> &p) const -> Vector3<decltype(T{} - U{})> {
        DCHECK(!p.hasNaN());
        return {x - p.x, y - p.y, z - p.z};
    }
};

template <typename T>
auto distance(const Point3<T> &p1, const Point3<T> &p2) { return length(p1 - p2); }

template <typename T>
auto distanceSquared(const Point3<T> &p1, const Point3<T> &p2) {
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
    explicit Normal3(const Normal3<U> &v)
    : Tuple3<Normal3, T>(T(v.x), T(v.y), T(v.z)) {}

    template <typename U>
    explicit Normal3(const Vector3<U> &v)
    : Tuple3<Normal3, T>(T(v.x), T(v.y), T(v.z)) {}
};

template <typename T>
inline Vector3<T> cross(const Vector3<T> &v, const Normal3<T> &n) {
    return cross(v, Vector3<T>(n));
}

template <typename T>
inline Vector3<T> cross(const Normal3<T> n, const Vector3<T> v) {
    return cross(Vector3<T>(n), v);
}

template <typename T>
inline auto dot(const Normal3<T> &n, const Vector3<T> &v) {
    DCHECK(!n.hasNaN() && !v.hasNaN());
    return n.x*v.x + n.y*v.y + n.z*v.z;
}

template <typename T>
inline auto dot(const Vector3<T> &v, const Normal3<T> &n) {
    DCHECK(!v.hasNaN() && !n.hasNaN());
    return v.x*n.x + v.y*n.y + v.z*n.z;
}

template <typename T>
inline auto dot(const Normal3<T> &n1, const Normal3<T> &n2) {
    DCHECK(!n1.hasNaN() && !n2.hasNaN());
    return n1.x*n2.x + n1.y*n2.y + n1.z*n2.z;
}

template <typename T>
inline auto absDot(const Normal3<T> &n, const Vector3<T> &v) {
    DCHECK(!n.hasNaN() && !v.hasNaN());
    return std::abs(dot(n, v));
}

template <typename T>
inline auto absDot(const Vector3<T> &v, const Normal3<T> &n) {
    using std::abs;
    return abs(dot(v, n));
}

template <typename T>
inline auto absDot(const Normal3<T> &n1, const Normal3<T> &n2) {
    using std::abs;
    return abs(dot(n1, n2));
}
