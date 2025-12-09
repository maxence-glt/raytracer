#include <gtest/gtest.h>

#include "vecmath.hpp"

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
    /*
    EXPECT_EQ(vf, Permute(vf, {0, 1, 2}));
    EXPECT_EQ(Vector3f(10, -1, 2), Permute(vf, {1, 0, 2}));
    EXPECT_EQ(Vector3f(2, -1, 10), Permute(vf, {2, 0, 1}));
    EXPECT_EQ(Vector3f(10, 10, -1), Permute(vf, {1, 1, 0}));
    */
}
