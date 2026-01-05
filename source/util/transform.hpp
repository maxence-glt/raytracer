#pragma once

#include "math.hpp"
#include "../ray.hpp"
#include <optional>

class Transform {
public:
    Transform() = default;

    Transform(const SquareMatrix<4> &m, const SquareMatrix<4> &mInv) : m(m), mInv(mInv) {}

    Transform(const SquareMatrix<4> &m) : m(m) {
        std::optional<SquareMatrix<4>> inv = inverse(m);
        if (inv)
            mInv = *inv;
        else {
            Float NaN = std::numeric_limits<Float>::has_signaling_NaN
                            ? std::numeric_limits<Float>::signaling_NaN()
                            : std::numeric_limits<Float>::quiet_NaN();
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    mInv[i][j] = NaN;
        }
    }

    const SquareMatrix<4> &getMatrix() const { return m; }
    const SquareMatrix<4> &getInverseMatrix() const { return mInv; }

    Transform operator*(const Transform &t2) const {
        return Transform(m * t2.m, t2.mInv * mInv);
    }

    bool operator==(const Transform &t) const { return t.m == m; }
    bool operator!=(const Transform &t) const { return t.m != m; }
    bool isIdentity() const { return m.isIdentity(); }

    template <typename T>
    Point3<T> operator()(const Point3<T> &p) const;
    template <typename T>
    Point3<T> applyInverse(const Point3<T> &p) const;

    template <typename T>
    Vector3<T> operator()(const Vector3<T> &v) const;
    template <typename T>
    Vector3<T> applyInverse(const Vector3<T> &v) const;

    template <typename T>
    Normal3<T> operator()(const Normal3<T> &n) const;
    template <typename T>
    Normal3<T> applyInverse(const Normal3<T> &n) const;

    Ray operator()(const Ray &r, Float *tMax) const;
    Ray applyInverse(const Ray &r, Float *tMax) const;

    Bounds3f operator()(const Bounds3f &b) const;

private:
    SquareMatrix<4> m, mInv;
};

Transform translate(const Vector3f &delta);
Transform scale(Float x, Float y, Float z);
Transform rotateX(Float theta);
Transform rotateY(Float theta);
Transform rotateZ(Float theta);
Transform rotate(Float sinTheta, Float cosTheta, const Vector3f &axis);
Transform rotate(Float theta, const Vector3f &axis);
Transform lookAt(const Point3f &pos, const Point3f &look, const Vector3f &up);

inline Transform inverse(const Transform &t) {
    return Transform(t.getInverseMatrix(), t.getMatrix());
}

inline Transform transpose(const Transform &t) {
    return Transform(transpose(t.getMatrix()), transpose(t.getInverseMatrix()));
}

template <typename T>
Point3<T> Transform::operator()(const Point3<T> &p) const {
    T x = p.x, y = p.y, z = p.z;
    T xp = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    T yp = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    T zp = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
    T wp = m[3][0] * x + m[3][1] * y + m[3][2] * z + m[3][3];
    if (wp == 1)
        return Point3<T>(xp, yp, zp);
    else
        return Point3<T>(xp, yp, zp) / wp;
}

template <typename T>
inline Point3<T> Transform::applyInverse(const Point3<T> &p) const {
    T x = p.x, y = p.y, z = p.z;
    T xp = (mInv[0][0] * x + mInv[0][1] * y) + (mInv[0][2] * z + mInv[0][3]);
    T yp = (mInv[1][0] * x + mInv[1][1] * y) + (mInv[1][2] * z + mInv[1][3]);
    T zp = (mInv[2][0] * x + mInv[2][1] * y) + (mInv[2][2] * z + mInv[2][3]);
    T wp = (mInv[3][0] * x + mInv[3][1] * y) + (mInv[3][2] * z + mInv[3][3]);
    CHECK_NE(wp, 0);
    if (wp == 1)
        return Point3<T>(xp, yp, zp);
    else
        return Point3<T>(xp, yp, zp) / wp;
}

template <typename T>
Vector3<T> Transform::operator()(const Vector3<T> &v) const {
    T x = v.x, y = v.y, z = v.z;
    return Vector3<T>(m[0][0] * x + m[0][1] * y + m[0][2] * z,
                      m[1][0] * x + m[1][1] * y + m[1][2] * z,
                      m[2][0] * x + m[2][1] * y + m[2][2] * z);
}

template <typename T>
inline Vector3<T> Transform::applyInverse(const Vector3<T> &v) const {
    T x = v.x, y = v.y, z = v.z;
    return Vector3<T>(mInv[0][0] * x + mInv[0][1] * y + mInv[0][2] * z,
                      mInv[1][0] * x + mInv[1][1] * y + mInv[1][2] * z,
                      mInv[2][0] * x + mInv[2][1] * y + mInv[2][2] * z);
}

template <typename T>
Normal3<T> Transform::operator()(const Normal3<T> &n) const {
    T x = n.x, y = n.y, z = n.z;
    return Normal3<T>(mInv[0][0] * x + mInv[1][0] * y + mInv[2][0] * z,
                      mInv[0][1] * x + mInv[1][1] * y + mInv[2][1] * z,
                      mInv[0][2] * x + mInv[1][2] * y + mInv[2][2] * z);
}

template <typename T>
inline Normal3<T> Transform::applyInverse(const Normal3<T> &n) const {
    T x = n.x, y = n.y, z = n.z;
    return Normal3<T>(m[0][0] * x + m[1][0] * y + m[2][0] * z,
                      m[0][1] * x + m[1][1] * y + m[2][1] * z,
                      m[0][2] * x + m[1][2] * y + m[2][2] * z);
}

inline Ray Transform::operator()(const Ray &r, Float *tMax) const {
    Point3f o = (*this)(r.o);
    Vector3f d = (*this)(r.d);

    return Ray(o, d, r.t);
}

inline Ray Transform::applyInverse(const Ray &r, Float *tMax) const {
    Point3f o = applyInverse(r.o);
    Vector3f d = applyInverse(r.d);

    return Ray(o, d, r.t);
}

inline Bounds3f Transform::operator()(const Bounds3f &b) const {
    Bounds3f bt;
    for (int i = 0; i < 8; ++i)
        bt = combine(bt, (*this)(b.corner(i)));
    return bt;
}
