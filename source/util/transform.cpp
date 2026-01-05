#include "transform.hpp"
#include "log.hpp"
#include "vecmath.hpp"

Transform translate(const Vector3f &delta) {
    SquareMatrix<4> m(1, 0, 0, delta.x,
                      0, 1, 0, delta.y,
                      0, 0, 1, delta.z,
                      0, 0, 0, 1);
    SquareMatrix<4> minv(1, 0, 0, -delta.x,
                         0, 1, 0, -delta.y,
                         0, 0, 1, -delta.z,
                         0, 0, 0, 1);
    return Transform(m, minv);
}

Transform scale(Float x, Float y, Float z) {
    SquareMatrix<4> m(x, 0, 0, 0,
                      0, y, 0, 0,
                      0, 0, z, 0,
                      0, 0, 0, 1);
    SquareMatrix<4> minv(1 / x,     0,     0, 0,
                             0, 1 / y,     0, 0,
                             0,     0, 1 / z, 0,
                             0,     0,     0, 1);
    return Transform(m, minv);
}

Transform rotateX(Float theta) {
    Float sinTheta = std::sin(radians(theta));
    Float cosTheta = std::cos(radians(theta));
    SquareMatrix<4> m(1,        0,         0, 0,
                      0, cosTheta, -sinTheta, 0,
                      0, sinTheta,  cosTheta, 0,
                      0,        0,         0, 1);
    return Transform(m, transpose(m));
}

Transform rotateY(Float theta) {
    Float sinTheta = std::sin(radians(theta));
    Float cosTheta = std::cos(radians(theta));
    SquareMatrix<4> m( cosTheta, 0, sinTheta, 0,
                              0, 1,        0, 0,
                      -sinTheta, 0, cosTheta, 0,
                              0, 0,        0, 1);
    return Transform(m, transpose(m));
}

Transform rotateZ(Float theta) {
    Float sinTheta = std::sin(radians(theta));
    Float cosTheta = std::cos(radians(theta));
    SquareMatrix<4> m(cosTheta, -sinTheta, 0, 0,
                      sinTheta,  cosTheta, 0, 0,
                             0,         0, 1, 0,
                             0,         0, 0, 1);
    return Transform(m, transpose(m));
}

Transform rotate(Float sinTheta, Float cosTheta, const Vector3f &axis) {
    Vector3f a = normalize(axis);
    SquareMatrix<4> m;

    m[0][0] = a.x * a.x + (1 - a.x * a.x) * cosTheta;
    m[0][1] = a.x * a.y * (1 - cosTheta) - a.z * sinTheta;
    m[0][2] = a.x * a.z * (1 - cosTheta) + a.y * sinTheta;
    m[0][3] = 0;

    m[1][0] = a.x * a.y * (1 - cosTheta) + a.z * sinTheta;
    m[1][1] = a.y * a.y + (1 - a.y * a.y) * cosTheta;
    m[1][2] = a.y * a.z * (1 - cosTheta) - a.x * sinTheta;
    m[1][3] = 0;

    m[2][0] = a.x * a.z * (1 - cosTheta) - a.y * sinTheta;
    m[2][1] = a.y * a.z * (1 - cosTheta) + a.x * sinTheta;
    m[2][2] = a.z * a.z + (1 - a.z * a.z) * cosTheta;
    m[2][3] = 0;

    return Transform(m, transpose(m));
}

Transform rotate(Float theta, const Vector3f &axis) {
    Float sinTheta = std::sin(radians(theta));
    Float cosTheta = std::cos(radians(theta));
    return rotate(sinTheta, cosTheta, axis);
}


Transform lookAt(const Point3f &pos, const Point3f &look, const Vector3f &up) {
    SquareMatrix<4> worldFromCamera;
    worldFromCamera[0][3] = pos.x;
    worldFromCamera[1][3] = pos.y;
    worldFromCamera[2][3] = pos.z;
    worldFromCamera[3][3] = 1;

    Vector3f dir = normalize(look - pos);
    if (length(cross(normalize(up), dir)) ==  0)
        LOG_FATAL("LookAt: \"up\" vector ({}, {}, {}) and viewing direction "
                  "({}, {}, {}) "
                  "passed to LookAt are pointing in the same direction.",
                  up.x, up.y, up.z, dir.x, dir.y, dir.z);
    Vector3f right = normalize(cross(normalize(up), dir));
    Vector3f newUp = cross(dir, right);
    worldFromCamera[0][0] = right.x;
    worldFromCamera[1][0] = right.y;
    worldFromCamera[2][0] = right.z;
    worldFromCamera[3][0] = 0.;
    worldFromCamera[0][1] = newUp.x;
    worldFromCamera[1][1] = newUp.y;
    worldFromCamera[2][1] = newUp.z;
    worldFromCamera[3][1] = 0.;
    worldFromCamera[0][2] = dir.x;
    worldFromCamera[1][2] = dir.y;
    worldFromCamera[2][2] = dir.z;
    worldFromCamera[3][2] = 0.;

    SquareMatrix<4> cameraFromWorld = invertOrExit(worldFromCamera);
    return Transform(cameraFromWorld, worldFromCamera);
}
