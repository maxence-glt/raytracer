#include <gtest/gtest.h>

#include "vecmath.hpp"
#include "random.hpp"

TEST(Vector3, Basics) {
    Vector3f vf(-1, 10, 2);
    EXPECT_EQ(vf, Vector3f(Vector3i(-1, 10, 2)));
    EXPECT_NE(vf, Vector3f(-1, 100, 2));
    EXPECT_EQ(Vector3f(-2, 20, 4), vf + vf);
    EXPECT_EQ(Vector3f(0, 0, 0), vf - vf);
    EXPECT_EQ(Vector3f(-2, 20, 4), vf * 2);
    EXPECT_EQ(Vector3f(-2, 20, 4), 2 * vf);
    EXPECT_EQ(Vector3f(-0.5, 5, 1), vf / 2);
    EXPECT_EQ(Vector3f(1, 10, 2), abs(vf));
    EXPECT_EQ(vf, ceil(Vector3f(-1.5, 9.9, 1.01)));
    EXPECT_EQ(vf, floor(Vector3f(-.5, 10.01, 2.99)));
    EXPECT_EQ(Vector3f(-20, 10, 1.5), min(vf, Vector3f(-20, 20, 1.5)));
    EXPECT_EQ(Vector3f(-1, 20, 2), max(vf, Vector3f(-20, 20, 0)));
    EXPECT_EQ(-1, minComponentValue(vf));
    EXPECT_EQ(-10, minComponentValue(-vf));
    EXPECT_EQ(10, maxComponentValue(vf));
    EXPECT_EQ(1, maxComponentValue(-vf));
    EXPECT_EQ(1, maxComponentIndex(vf));
    EXPECT_EQ(0, maxComponentIndex(-vf));
    EXPECT_EQ(0, minComponentIndex(vf));
    EXPECT_EQ(1, minComponentIndex(-vf));
    EXPECT_EQ(Vector3<float>(-1/sqrt(105), 10/sqrt(105), 2/sqrt(105)),
              normalize(vf));
    /*
    EXPECT_EQ(vf, Permute(vf, {0, 1, 2}));
    EXPECT_EQ(Vector3f(10, -1, 2), Permute(vf, {1, 0, 2}));
    EXPECT_EQ(Vector3f(2, -1, 10), Permute(vf, {2, 0, 1}));
    EXPECT_EQ(Vector3f(10, 10, -1), Permute(vf, {1, 1, 0}));
    */
}

TEST(Vector, AngleBetween) {
    EXPECT_EQ(0, angleBetween(Vector3f(1, 0, 0), Vector3f(1, 0, 0)));
    EXPECT_LT(std::abs(angleBetween(Vector3f(0, 0, 1), Vector3f(0, 0, -1))) - Pi,
              1e-7);
    EXPECT_LT(std::abs(angleBetween(Vector3f(1, 0, 0), Vector3f(0, 1, 0))) - Pi / 2,
              1e-7);

    Vector3f x = normalize(Vector3f(1, -3, 10));
    EXPECT_EQ(0, angleBetween(x, x));
    EXPECT_LT(std::abs(angleBetween(x, -x) - Pi), 3e-7);

    float maxErr = 0, sumErr = 0;
    for (int i = 0; i < 100000; ++i) {
        Random<float> rng;
        Vector3f a = normalize(Vector3f(-1 + 2 * rng.random(),
                                        -1 + 2 * rng.random(),
                                        -1 + 2 * rng.random()));
        Vector3f b = normalize(Vector3f(-1 + 2 * rng.random(),
                                        -1 + 2 * rng.random(),
                                        -1 + 2 * rng.random()));

        Vector3<double> ad(a), bd(b);
        ad = normalize(ad);
        bd = normalize(bd);

        float v[2] = {float(std::acos(dot(ad, bd))), angleBetween(a, b)};
        float err = std::abs(v[0] - v[1]) / v[0];
        maxErr = std::max(err, maxErr);
        sumErr += err;
        EXPECT_LT(err, 5e-6) << v[0] << "vs " << v[1] << ", a: " << a.toString() << ", b: " << b.toString();
    }

    maxErr = 0;
    sumErr = 0;

    for (int i = 0; i < 100000; ++i) {
        Random<float> rng;
        Vector3f a = normalize(Vector3f(-1 + 2 * rng.random(),
                                        -1 + 2 * rng.random(),
                                        -1 + 2 * rng.random()));
        Vector3f b = normalize(Vector3f(-1 + 2 * rng.random(),
                                        -1 + 2 * rng.random(),
                                        -1 + 2 * rng.random()));

        a.x = std::copysign(a.x, -b.x);
        a.y = std::copysign(a.y, -b.y);
        a.z = std::copysign(a.z, -b.z);

        Vector3<double> ad(a), bd(b);
        ad = normalize(ad);
        bd = normalize(bd);

        float v[2] = {float(std::acos(dot(ad, bd))), angleBetween(a, b)};
        float err = std::abs(v[0] - v[1]) / v[0];
        maxErr = std::max(err, maxErr);
        sumErr += err;
        EXPECT_LT(err, 5e-6) << v[0] << "vs " << v[1] << ", a: " << a.toString() << ", b: " << b.toString();
    }

    Vector3f a(1, 1, 1), b(-1, -1.0001, -1);
    a = normalize(a);
    b = normalize(b);
    Vector3<long double> ad(1, 1, 1), bd(-1, -1.0001, -1);
    ad = normalize(ad);
    bd = normalize(bd);

    float naive = safeACos(dot(a, b));
    float precise = std::acos(clamp(dot(ad, bd), -1, 1));
    float abet = angleBetween(a, b);
    EXPECT_EQ(abet, precise) << std::format("vs naive {}", naive);
}

TEST(Vector, CoordinateSystem) {
    // Duff et al 2017 footnote 1
    auto error = [](Vector3f a, Vector3f b, Vector3f c) {
        return (sqr(length(a) - 1) + sqr(length(b) - 1) + sqr(length(c) - 1) +
                sqr(dot(a, b)) + sqr(dot(b, c)) + sqr(dot(c, a))) /
               6;
    };

    // Coordinate axes.
    Vector3f a, b;
    for (Vector3f v : {Vector3f(1, 0, 0), Vector3f(-1, 0, 0), Vector3f(0, 1, 0),
                       Vector3f(0, -1, 0), Vector3f(0, 0, 1), Vector3f(0, 0, -1)}) {
        CoordinateSystem(v, &a, &b);
        for (int c = 0; c < 3; ++c) {
            if (v[c] != 0) {
                EXPECT_EQ(0, a[c]);
                EXPECT_EQ(0, b[c]);
            }
        }
    }

    // Bad vectors from Duff et al
    for (Vector3f v : {Vector3f(0.00038527316, 0.00038460016, -0.99999988079),
                       Vector3f(-0.00019813581, -0.00008946839, -0.99999988079)}) {
        CoordinateSystem(v, &a, &b);
        EXPECT_LT(error(v, a, b), 1e-10);
    }
}
