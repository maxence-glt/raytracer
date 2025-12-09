#pragma once

#include "check.h"

using std::isnan;

/* TODO: Possible additions
*
* The basic arithmetic operators of per-component addition, subtraction, and negation, including the “in place” (e.g., operator+=) forms of them.
*
* Component-wise multiplication and division by a scalar value, including “in place” variants.
*
* Abs(a), which returns a value where the absolute value of each component of the tuple type has been taken.
*
* Ceil(a) and Floor(a), which return a value where the components have been rounded up or down to the nearest integer value, respectively.
*
* Lerp(t, a, b), which returns the result of the linear interpolation (1-t)*a + t*b.
*
* FMA(a, b, c), which takes three tuples and returns the result of a component-wise fused multiply-add a*b + c.
*
* Min(a, b) and Max(a, b), which respectively return the component-wise minimum and maximum of the two given tuples.
*
* MinComponentValue(a) and MaxComponentValue(a), which respectively return the minimum and maximum value of the tuple’s components.
*
* MinComponentIndex(a) and MaxComponentIndex(a), which respectively return the zero-based index of the tuple element with minimum or maximum value.
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
