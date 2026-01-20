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
class Tuple2 {
public:
    static const int nDimensions = 2;

    Tuple2() = default;
    Tuple2(T x, T y) : x(x), y(y) { DCHECK(!hasNaN()); }

    bool hasNaN() const { return isnan(x) || isnan(y); }

    Tuple2(Child<T> c) {
        DCHECK(!c.hasNaN());
        x = c.x;
        y = c.y;
    }

    Child<T> &operator=(Child<T> c) {
        DCHECK(!c.hasNaN());
        x = c.x;
        y = c.y;
        return static_cast<Child<T> &>(*this);
    }

    template <typename U>
    auto operator+(Child<U> c) const -> Child<decltype(T{} + U{})> {
        DCHECK(!c.hasNaN());
        return {x + c.x, y + c.y};
    }
    template <typename U>
    Child<T> &operator+=(Child<U> c) {
        DCHECK(!c.hasNaN());
        x += c.x;
        y += c.y;
        return static_cast<Child<T> &>(*this);
    }

    template <typename U>
    auto operator-(Child<U> c) const -> Child<decltype(T{} - U{})> {
        DCHECK(!c.hasNaN());
        return {x - c.x, y - c.y};
    }
    template <typename U>
    Child<T> &operator-=(Child<U> c) {
        DCHECK(!c.hasNaN());
        x -= c.x;
        y -= c.y;
        return static_cast<Child<T> &>(*this);
    }

    bool operator==(Child<T> c) const { return x == c.x && y == c.y; }
    bool operator!=(Child<T> c) const { return x != c.x || y != c.y; }

    template <typename U>
    auto operator*(U s) const -> Child<decltype(T{} * U{})> {
        return {s * x, s * y};
    }
    template <typename U>
    Child<T> &operator*=(U s) {
        DCHECK(!isnan(s));
        x *= s;
        y *= s;
        return static_cast<Child<T> &>(*this);
    }

    template <typename U>
    auto operator/(U d) const -> Child<decltype(T{} / U{})> {
        DCHECK(d != 0 && !isnan(d));
        return {x / d, y / d};
    }
    template <typename U>
    Child<T> &operator/=(U d) {
        DCHECK_NE(d, 0);
        DCHECK(!isnan(d));
        x /= d;
        y /= d;
        return static_cast<Child<T> &>(*this);
    }

    Child<T> operator-() const { return {-x, -y}; }

    T operator[](int i) const {
        DCHECK(i >= 0 && i <= 1);
        return (i == 0) ? x : y;
    }

    T &operator[](int i) {
        DCHECK(i >= 0 && i <= 1);
        return (i == 0) ? x : y;
    }

    std::string toString() const { return std::format("[ {}, {} ]", x, y); }

    T x{}, y{};
};


template <template <class> class C, typename T, typename U>
inline auto operator*(U s, Tuple2<C, T> t) -> C<decltype(T{} * U{})> {
    DCHECK(!t.hasNaN());
    return t * s;
}

template <template <class> class C, typename T>
inline C<T> abs(Tuple2<C, T> t) {
    return {abs(t.x), abs(t.y)};
}

template <template <class> class C, typename T>
inline C<T> ceil(Tuple2<C, T> t) {
    using std::ceil;
    return {ceil(t.x), ceil(t.y)};
}

template <template <class> class C, typename T>
inline C<T> floor(Tuple2<C, T> t) {
    using std::floor;
    return {floor(t.x), floor(t.y)};
}

template <template <class> class C, typename T>
inline auto lerp(Float t, Tuple2<C, T> t0, Tuple2<C, T> t1) {
    return (1 - t) * t0 + t * t1;
}

template <template <class> class C, typename T>
inline C<T> FMA(Float a, Tuple2<C, T> b, Tuple2<C, T> c) {
    return {std::fma(a, b.x, c.x), std::fma(a, b.y, c.y)};
}

template <template <class> class C, typename T>
inline C<T> FMA(Tuple2<C, T> a, Float b, Tuple2<C, T> c) {
    return std::fma(b, a, c);
}

template <template <class> class C, typename T>
inline C<T> min(Tuple2<C, T> t0, Tuple2<C, T> t1) {
    using std::min;
    return {min(t0.x, t1.x), min(t0.y, t1.y)};
}

template <template <class> class C, typename T>
inline T minComponentValue(Tuple2<C, T> t) {
    using std::min;
    return min({t.x, t.y});
}

template <template <class> class C, typename T>
inline int minComponentIndex(Tuple2<C, T> t) {
    return (t.x < t.y) ? 0 : 1;
}

template <template <class> class C, typename T>
inline C<T> max(Tuple2<C, T> t0, Tuple2<C, T> t1) {
    using std::max;
    return {max(t0.x, t1.x), max(t0.y, t1.y)};
}

template <template <class> class C, typename T>
inline T maxComponentValue(Tuple2<C, T> t) {
    using std::max;
    return max({t.x, t.y});
}

template <template <class> class C, typename T>
inline int maxComponentIndex(Tuple2<C, T> t) {
    return (t.x > t.y) ? 0 : 1;
}

template <template <class> class C, typename T>
inline C<T> Permute(Tuple2<C, T> t, std::array<int, 2> p) {
    return {t[p[0]], t[p[1]]};
}

template <template <class> class C, typename T>
inline T HProd(Tuple2<C, T> t) {
    return t.x * t.y;
}

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
        return std::format("[ {}, {}, {} ]", x, y, z); 
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
class Vector2 : public Tuple2<Vector2, T> {
public:
    using Tuple2<Vector2, T>::x;
    using Tuple2<Vector2, T>::y;

    Vector2() = default;
    Vector2(T x, T y) : Tuple2<Vector2, T>(x, y) {}
    template <typename U>
    explicit Vector2(Point2<U> p);
    template <typename U>
    explicit Vector2(Vector2<U> v)
        : Tuple2<Vector2, T>(T(v.x), T(v.y)) {}
};

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
inline Vector3<T> normalize(const Vector3<T> &v) {
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
class Point2 : public Tuple2<Point2, T> {
public:
    using Tuple2<Point2, T>::x;
    using Tuple2<Point2, T>::y;
    using Tuple2<Point2, T>::hasNaN;
    using Tuple2<Point2, T>::operator+;
    using Tuple2<Point2, T>::operator+=;
    using Tuple2<Point2, T>::operator*;
    using Tuple2<Point2, T>::operator*=;

    Point2() { x = y = 0; }
    Point2(T x, T y) : Tuple2<Point2, T>(x, y) {}
    template <typename U>
    explicit Point2(Point2<U> v) : Tuple2<Point2, T>(T(v.x), T(v.y)) {}
    template <typename U>
    explicit Point2(Vector2<U> v)
        : Tuple2<Point2, T>(T(v.x), T(v.y)) {}

    template <typename U>
    auto operator+(Vector2<U> v) const -> Point2<decltype(T{} + U{})> {
        DCHECK(!v.hasNaN());
        return {x + v.x, y + v.y};
    }
    template <typename U>
    Point2<T> &operator+=(Vector2<U> v) {
        DCHECK(!v.hasNaN());
        x += v.x;
        y += v.y;
        return *this;
    }

    Point2<T> operator-() const { return {-x, -y}; }

    template <typename U>
    auto operator-(Point2<U> p) const -> Vector2<decltype(T{} - U{})> {
        DCHECK(!p.hasNaN());
        return {x - p.x, y - p.y};
    }
    template <typename U>
    auto operator-(Vector2<U> v) const -> Point2<decltype(T{} - U{})> {
        DCHECK(!v.hasNaN());
        return {x - v.x, y - v.y};
    }
    template <typename U>
    Point2<T> &operator-=(Vector2<U> v) {
        DCHECK(!v.hasNaN());
        x -= v.x;
        y -= v.y;
        return *this;
    }
};

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


template <typename T>
class Bounds2 {
public:
    Bounds2() {
        T minNum = std::numeric_limits<T>::lowest();
        T maxNum = std::numeric_limits<T>::max();
        pMin = Point2<T>(maxNum, maxNum);
        pMax = Point2<T>(minNum, minNum);
    }

    explicit Bounds2(Point3<T> p) : pMin(p), pMax(p) {}

    Bounds2(Point2<T> p1, Point2<T> p2) : pMin(min(p1, p2)), pMax(max(p1, p2)) {}

    Point2<T> operator[](int i) const {
        DCHECK(i == 0 || i == 1);
        return (i == 0) ? pMin : pMax;
    }
    Point2<T> &operator[](int i) {
        DCHECK(i == 0 || i == 1);
        return (i == 0) ? pMin : pMax;
    }

    std::string toString() const { 
        return std::format("[ {} - {} ]", pMin.toString(), pMax.toString());
    }

    Point2<T> pMin, pMax;
};

template <typename T>
class Bounds3 {
public:
    Bounds3() {
        T minNum = std::numeric_limits<T>::lowest();
        T maxNum = std::numeric_limits<T>::max();
        pMin = Point3<T>(maxNum, maxNum, maxNum);
        pMax = Point3<T>(minNum, minNum, minNum);
    }

    explicit Bounds3(Point3<T> p) : pMin(p), pMax(p) {}

    Bounds3(Point3<T> p1, Point3<T> p2) : pMin(min(p1, p2)), pMax(max(p1, p2)) {}

    Point3<T> operator[](int i) const {
        DCHECK(i == 0 || i == 1);
        return (i == 0) ? pMin : pMax;
    }
    Point3<T> &operator[](int i) {
        DCHECK(i == 0 || i == 1);
        return (i == 0) ? pMin : pMax;
    }

    Point3<T> corner(int corner) const {
        DCHECK(corner >= 0 && corner < 8);
        return Point3<T>((*this)[(corner & 1)].x, 
                         (*this)[(corner & 2) ? 1 : 0].y,
                         (*this)[(corner & 4) ? 1 : 0].z);
    }

    Vector3<T> diagonal() const { return pMax - pMin; }

    T surfaceArea() const {
        Vector3<T> d = diagonal();
        return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
    }

    T volume() const {
        Vector3<T> d = diagonal();
        return d.x * d.y * d.z;
    }

    int maxDimension() const {
        Vector3<T> d = diagonal();
        if (d.x > d.y && d.x > d.z)
            return 0;
        else if (d.y > d.z)
            return 1;
        else
            return 2;
    }

    Point3f lerp(Point3f t) const {
        return Point3f(::lerp(t.x, pMin.x, pMax.x), 
                       ::lerp(t.y, pMin.y, pMax.y),
                       ::lerp(t.z, pMin.z, pMax.z));
    }

    Vector3f offset(Point3f p) const {
        Vector3f o = p - pMin;
        if (pMax.x > pMin.x)
            o.x /= pMax.x - pMin.x;
        if (pMax.y > pMin.y)
            o.y /= pMax.y - pMin.y;
        if (pMax.z > pMin.z)
            o.z /= pMax.z - pMin.z;
        return o;
    }

    void boundingSphere(Point3<T> *center, Float *radius) const {
        *center = (pMin + pMax) / 2;
        *radius = inside(*center, *this) ? distance(*center, pMax) : 0;
    }

    bool isEmpty() const {
        return pMin.x >= pMax.x || pMin.y >= pMax.y || pMin.z >= pMax.z;
    }
    bool isDegenerate() const {
        return pMin.x > pMax.x || pMin.y > pMax.y || pMin.z > pMax.z;
    }

    template <typename U>
    explicit Bounds3(const Bounds3<U> &b) {
        if (b.isEmpty())
            *this = Bounds3<T>();
        else {
            pMin = Point3<T>(b.pMin);
            pMax = Point3<T>(b.pMax);
        }
    }
    bool operator==(const Bounds3<T> &b) const {
        return b.pMin == pMin && b.pMax == pMax;
    }
    bool operator!=(const Bounds3<T> &b) const {
        return b.pMin != pMin || b.pMax != pMax;
    }
    bool intersectP(Point3f o, Vector3f d, Float tMax = infinity, Float *hitt0 = nullptr,
                    Float *hitt1 = nullptr) const;
    bool intersectP(Point3f o, Vector3f d, Float tMax, Vector3f invDir,
                    const int dirIsNeg[3]) const;

    std::string toString() const { 
        return std::format("[ {} - {} ]", pMin.toString(), pMax.toString());
    }

    Point3<T> pMin, pMax;
};

template <typename T>
Bounds3<T> combine(const Bounds3<T> &b, const Point3<T> &p) {
    return {min(b.pMin, p), max(b.pMax, p)};
}

template <typename T>
Bounds3<T> combine(const Bounds3<T> &b1, const Bounds3<T> &b2) {
    return {min(b1.pMin, b2.pMin), max(b1.pMax, b2.pMax)};
}

template <typename T>
Bounds3<T> intersect(const Bounds3<T> &b1, const Bounds3<T> &b2) {
    return {max(b1.pMin, b2.pMin), min(b1.pMax, b2.pMax)};
}

template <typename T>
bool overlaps(const Bounds3<T> &b1, const Bounds3<T> &b2) {
    bool x = (b1.pMax.x >= b2.pMin.x) && (b1.pMin.x <= b2.pMax.x);
    bool y = (b1.pMax.y >= b2.pMin.y) && (b1.pMin.y <= b2.pMax.y);
    bool z = (b1.pMax.z >= b2.pMin.z) && (b1.pMin.z <= b2.pMax.z);
    return (x && y && z);
}

template <typename T>
bool inside(const Point3<T> &p, const Bounds3<T> &b) {
    return (p.x >= b.pMin.x && p.x <= b.pMax.x &&
            p.y >= b.pMin.y && p.y <= b.pMax.y &&
            p.z >= b.pMin.z && p.z <= b.pMax.z);
}

template <typename T>
bool insideExclusive(const Point3<T> &p, const Bounds3<T> &b) {
    return (p.x >= b.pMin.x && p.x < b.pMax.x &&
            p.y >= b.pMin.y && p.y < b.pMax.y &&
            p.z >= b.pMin.z && p.z < b.pMax.z);
}

template <typename T, typename U>
auto distanceSquared(const Point3<T> &p, const Bounds3<U> &b) {
    using TDist = decltype(T{} - U{});
    TDist dx = std::max<TDist>({0, b.pMin.x - p.x, p.x - b.pMax.x});
    TDist dy = std::max<TDist>({0, b.pMin.y - p.y, p.y - b.pMax.y});
    TDist dz = std::max<TDist>({0, b.pMin.z - p.z, p.z - b.pMax.z});
    return sqr(dx) + sqr(dy) + sqr(dz);
}

template <typename T, typename U>
auto distance(const Point3<T> &p, const Bounds3<U> &b) {
    auto dist2 = distanceSquared(p, b);
    using TDist = typename TupleLength<decltype(dist2)>::type;
    return std::sqrt(TDist(dist2));
}

template <typename T, typename U>
Bounds3<T> expand(const Bounds3<T> &b, U delta) {
    Bounds3<T> ret;
    ret.pMin = b.pMin - Vector3<T>(delta, delta, delta);
    ret.pMax = b.pMax + Vector3<T>(delta, delta, delta);
    return ret;
}

// spherical geometry functions
inline Float sphericalTriangleArea(const Vector3f &a,
                                   const Vector3f &b,
                                   const Vector3f &c) {
    return std::abs(2 * std::atan2(dot(a, cross(b, c)),
                                   1 + dot(a, b) + dot(a, c) + dot(b, c)));
}

inline Float SphericalQuadArea(const Vector3f &a, const Vector3f &b, 
                               const Vector3f &c, const Vector3f &d) {
    Vector3f axb = cross(a, b), bxc = cross(b, c);
    Vector3f cxd = cross(c, d), dxa = cross(d, a);
    if (lengthSquared(axb) == 0 || lengthSquared(bxc) == 0 
        || lengthSquared(cxd) == 0 || lengthSquared(dxa) == 0)
        return 0;
    axb = normalize(axb);
    bxc = normalize(bxc);
    cxd = normalize(cxd);
    dxa = normalize(dxa);

    Float alpha = angleBetween(dxa, -axb);
    Float beta = angleBetween(axb, -bxc);
    Float gamma = angleBetween(bxc, -cxd);
    Float delta = angleBetween(cxd, -dxa);

    return std::abs(alpha + beta + gamma + delta - 2 * Pi);
}

// spherical parameterizations
inline Vector3f SphericalDirection(Float sinTheta, Float cosTheta, Float phi) {
    DCHECK(sinTheta >= -1.0001 && sinTheta <= 1.0001);
    DCHECK(cosTheta >= -1.0001 && cosTheta <= 1.0001);
    return Vector3f(clamp(sinTheta, -1, 1) * std::cos(phi),
                    clamp(sinTheta, -1, 1) * std::sin(phi), clamp(cosTheta, -1, 1));
}

inline Float sphericalTheta(const Vector3f &v) {
    return safeACos(v.z);
}

inline Float sphericalPhi(const Vector3f &v) {
    Float p = std::atan2(v.y, v.x);
    return (p < 0) ? (p + 2 * Pi) : p;
}

inline Float cosTheta(const Vector3f &w) { return w.z; }
inline Float absCosTheta(const Vector3f &w) { return std::abs(w.z); }
inline Float cos2Theta(const Vector3f &w) { return sqr(w.z); }

inline Float sin2Theta(const Vector3f &w) {
    return std::max<Float>(0, 1 - cos2Theta(w));
}
inline Float sinTheta(const Vector3f &w) {
    return std::sqrt(sin2Theta(w));
}

inline Float tanTheta(const Vector3f &w) {
    return sinTheta(w) / cosTheta(w);
}
inline Float tan2Theta(const Vector3f &w) {
    return sin2Theta(w) / cos2Theta(w);
}

inline Float cosPhi(const Vector3f &w) {
    Float t = sinTheta(w);
    return (t == 0) ? 1 : clamp(w.x / t, -1, 1);
}
inline Float sinPhi(const Vector3f &w) {
    Float t = sinTheta(w);
    return (t == 0) ? 0 : clamp(w.y / t, -1, 1);
}

inline Float cosDPhi(const Vector3f &wa, const Vector3f &wb) {
    Float waxy = sqr(wa.x) + sqr(wa.y), wbxy = sqr(wb.x) + sqr(wb.y);
    if (waxy == 0 || wbxy == 0)
        return 1;
    return clamp((wa.x * wb.x + wa.y * wb.y) / std::sqrt(waxy * wbxy), -1, 1);
}

inline bool sameHemisphere(const Vector3f &w, const Vector3f &wp) {
    return w.z * wp.z > 0;
}
inline bool sameHemisphere(const Vector3f &w, const Normal3f &wp) {
    return w.z * wp.z > 0;
}

// add bounding directions class for point lights
