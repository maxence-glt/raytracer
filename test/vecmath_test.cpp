#include <gtest/gtest.h>
#include <type_traits>

#include "util/vecmath.hpp"
#include "raytracer.hpp"

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
    EXPECT_EQ(Vector3<Float>(-1/sqrt(105), 10/sqrt(105), 2/sqrt(105)),
              normalize(vf));
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

TEST(Point3, Basics) {
    Point3f p(-1, 10, 2);

    EXPECT_EQ(p, Point3f(Point3i(-1, 10, 2)));
    EXPECT_EQ(p, Point3f(Vector3f(-1, 10, 2)));
    EXPECT_EQ(Point3f(1, -10, -2), -p);

    Vector3f v(1, 2, 3);
    EXPECT_EQ(Point3f(0, 12, 5), p + v);

    Point3f p2 = p;
    p2 += v;
    EXPECT_EQ(Point3f(0, 12, 5), p2);
    EXPECT_EQ(Point3f(-2, 8, -1), p - v);

    p2 = p;
    p2 -= v;
    EXPECT_EQ(Point3f(-2, 8, -1), p2);

    Point3f q(0, 12, 5);
    EXPECT_EQ(Vector3f(1, 2, 3), q - p);

    Point3i pi(-1, 10, 2);
    auto mixedDiff = q - pi;
    EXPECT_EQ(Vector3f(1, 2, 3), mixedDiff);
}

TEST(Point3, Distance) {
    Point3f a(1, 2, 3);
    Point3f b(4, 6, 3);

    EXPECT_FLOAT_EQ(5.f, distance(a, b));
    EXPECT_FLOAT_EQ(25.f, distanceSquared(a, b));
    EXPECT_FLOAT_EQ(distance(a, b), distance(b, a));
    EXPECT_FLOAT_EQ(distanceSquared(a, b), distanceSquared(b, a));
    EXPECT_FLOAT_EQ(0.f, distance(a, a));
    EXPECT_FLOAT_EQ(0.f, distanceSquared(a, a));
}


TEST(Normal3, Basics) {
    Vector3f a(1, 2, 3);
    Vector3f b(4, 5, 6);
    Normal3f n = Normal3f(cross(a, b));
    EXPECT_EQ(n, Normal3f(-3, 6, -3));
}

template <typename V>
static inline void ExpectVecNear(const V& a, const V& b, Float eps = 1e-6f) {
    EXPECT_NEAR(a.x, b.x, eps);
    EXPECT_NEAR(a.y, b.y, eps);
    EXPECT_NEAR(a.z, b.z, eps);
}

// ---------------- Vector3 / Tuple3 ----------------

TEST(Vector3, IndexingAndNearZero) {
    Vector3f v(1, -2, 3);
    EXPECT_FLOAT_EQ(v[0], 1);
    EXPECT_FLOAT_EQ(v[1], -2);
    EXPECT_FLOAT_EQ(v[2], 3);

    v[0] = 10;
    v[1] = 20;
    v[2] = 30;
    EXPECT_EQ(v, Vector3f(10, 20, 30));

    EXPECT_TRUE(Vector3f(1e-9f, -1e-9f, 0).near_zero());
    EXPECT_FALSE(Vector3f(1e-6f, 0, 0).near_zero());
}

TEST(Vector3, HadamardMultiply) {
    Vector3f a(1, 2, 3);
    Vector3f b(4, 5, 6);
    EXPECT_EQ(a * b, Vector3f(4, 10, 18));
}

TEST(Vector3, MixedTypeArithmeticReturnTypes) {
    // compile-time checks on return types
    static_assert(std::is_same_v<decltype(Vector3i(1,2,3) + Vector3f(0.5f,1.5f,2.5f)), Vector3<Float>>);
    static_assert(std::is_same_v<decltype(Vector3f(1,2,3) * 2), Vector3<Float>>);

    auto v = Vector3i(1, 2, 3) + Vector3f(0.5f, 1.5f, 2.5f);
    ExpectVecNear(v, Vector3f(1.5f, 3.5f, 5.5f));
}

TEST(Vector3, DotCrossIdentities) {
    Vector3f a(1, 2, 3);
    Vector3f b(-4, 5, -6);

    // anti-commutativity
    EXPECT_EQ(cross(a, b), -cross(b, a));

    // orthogonality: a·(a×b)=0 and b·(a×b)=0
    Vector3f c = cross(a, b);
    EXPECT_NEAR(dot(a, c), 0.0f, 1e-6f);
    EXPECT_NEAR(dot(b, c), 0.0f, 1e-6f);

    // distributivity: a×(b+c)=a×b + a×c
    Vector3f d(7, -8, 9);
    ExpectVecNear(cross(a, b + d), cross(a, b) + cross(a, d));
}

TEST(Vector3, NormalizeLength) {
    Vector3f v(3, 4, 12);
    auto n = normalize(v);
    EXPECT_NEAR(length(n), 1.0f, 1e-6f);

    // direction preserved: n is v / |v|
    ExpectVecNear(n * length(v), v, 1e-5f);
}

TEST(Vector3, GramSchmidtOrthogonalizes) {
    Vector3f v(1, 1, 0);
    Vector3f w(1, 0, 0);
    Vector3f u = gramSchmidt(v, w);
    // should remove component along w, leaving (0,1,0)
    ExpectVecNear(u, Vector3f(0, 1, 0));
    EXPECT_NEAR(dot(u, w), 0.0f, 1e-6f);
}

TEST(Vector3, ReflectBasics) {
    // reflect across +Y normal plane
    Vector3f v(1, -1, 0);
    Vector3f n(0, 1, 0);
    ExpectVecNear(reflect(v, n), Vector3f(1, 1, 0));

    // using Normal3 overload
    Normal3f nn(0, 1, 0);
    ExpectVecNear(reflect(v, nn), Vector3f(1, 1, 0));
}

TEST(Vector3, RefractNormalIncidence) {
    // At normal incidence, refraction direction should be unchanged (no bending).
    Vector3f uv = normalize(Vector3f(0, 0, -1));
    Normal3f n(0, 0, 1);

    for (Float eta : {0.5f, 1.0f, 1.5f}) {
        Vector3f r = refract(uv, n, eta);
        ExpectVecNear(r, Vector3f(0, 0, -1));
        EXPECT_NEAR(length(r), 1.0f, 1e-6f);
    }
}

TEST(Vector3, RandomGeneratorsProperties) {
    // Keep iteration count modest so tests run fast.
    for (int i = 0; i < 2000; ++i) {
        Vector3f u = random_unit_vector<Float>();
        EXPECT_NEAR(length(u), 1.0f, 1e-4f);

        Vector3f d = random_in_unit_disk<Float>();
        EXPECT_FLOAT_EQ(d.z, 0.0f);
        EXPECT_LT(lengthSquared(d), 1.0f);

        Vector3f n(0, 1, 0);
        Vector3f h = random_on_hemisphere<Float>(n);
        EXPECT_GE(dot(h, n), 0.0f);
        EXPECT_NEAR(length(h), 1.0f, 1e-4f);
    }
}

// ---------------- Point3 / Normal3 ----------------

TEST(Normal3, DotAbsDotSanity) {
    Normal3f n(0, 1, 0);
    Vector3f v(0, -2, 0);

    EXPECT_FLOAT_EQ(dot(n, v), -2.0f);
    EXPECT_FLOAT_EQ(absDot(n, v), 2.0f);
    EXPECT_FLOAT_EQ(absDot(v, n), 2.0f);

    Normal3f n2(0, -1, 0);
    EXPECT_FLOAT_EQ(dot(n, n2), -1.0f);
    EXPECT_FLOAT_EQ(absDot(n, n2), 1.0f);
}

TEST(Point3, MixedTypeSubtractionReturnType) {
    Point3i a(1, 2, 3);
    Point3f b(1.25f, 1.5f, -0.5f);
    static_assert(std::is_same_v<decltype(b - a), Vector3<Float>>);
    auto d = b - a;
    ExpectVecNear(d, Vector3f(0.25f, -0.5f, -3.5f));
}

// ---------------- Bounds3 ----------------

TEST(Bounds3, DefaultIsEmpty) {
    Bounds3f b;
    EXPECT_TRUE(b.isEmpty());
    EXPECT_FALSE(!b.isDegenerate()); // note: per your implementation, default is "empty" but not necessarily "degenerate"
}

TEST(Bounds3, GeometryBasics) {
    Bounds3f b(Point3f(-1, -2, -3), Point3f(4, 5, 6));
    EXPECT_FALSE(b.isEmpty());
    EXPECT_FALSE(b.isDegenerate());

    EXPECT_EQ(b.diagonal(), Vector3f(5, 7, 9));
    EXPECT_FLOAT_EQ(b.surfaceArea(), 2.0f * (5*7 + 5*9 + 7*9));
    EXPECT_FLOAT_EQ(b.volume(), 5.0f * 7.0f * 9.0f);
    EXPECT_EQ(b.maxDimension(), 2); // z is largest (9)

    // corners
    EXPECT_EQ(b.corner(0), Point3f(-1, -2, -3));
    EXPECT_EQ(b.corner(7), Point3f(4, 5, 6));
}

TEST(Bounds3, LerpAndOffset) {
    Bounds3f b(Point3f(0, 0, 0), Point3f(2, 4, 6));

    EXPECT_EQ(b.lerp(Point3f(0, 0, 0)), Point3f(0, 0, 0));
    EXPECT_EQ(b.lerp(Point3f(1, 1, 1)), Point3f(2, 4, 6));
    EXPECT_EQ(b.lerp(Point3f(0.5f, 0.5f, 0.5f)), Point3f(1, 2, 3));

    ExpectVecNear(b.offset(Point3f(0, 0, 0)), Vector3f(0, 0, 0));
    ExpectVecNear(b.offset(Point3f(2, 4, 6)), Vector3f(1, 1, 1));
    ExpectVecNear(b.offset(Point3f(1, 2, 3)), Vector3f(0.5f, 0.5f, 0.5f));
}

TEST(Bounds3, CombineIntersectOverlapsInside) {
    Bounds3f a(Point3f(0, 0, 0), Point3f(2, 2, 2));
    Bounds3f b(Point3f(1, 1, 1), Point3f(3, 3, 3));

    EXPECT_TRUE(overlaps(a, b));
    Bounds3f c = intersect(a, b);
    EXPECT_EQ(c.pMin, Point3f(1, 1, 1));
    EXPECT_EQ(c.pMax, Point3f(2, 2, 2));

    Bounds3f u = combine(a, b);
    EXPECT_EQ(u.pMin, Point3f(0, 0, 0));
    EXPECT_EQ(u.pMax, Point3f(3, 3, 3));

    EXPECT_TRUE(inside(Point3f(1, 1, 1), a));
    EXPECT_TRUE(insideExclusive(Point3f(1, 1, 1), a));
    EXPECT_TRUE(inside(Point3f(2, 2, 2), a));
    EXPECT_FALSE(insideExclusive(Point3f(2, 2, 2), a));
}

TEST(Bounds3, DistanceToBounds) {
    Bounds3f b(Point3f(0, 0, 0), Point3f(1, 1, 1));

    EXPECT_FLOAT_EQ(distance(Point3f(0.5f, 0.5f, 0.5f), b), 0.0f);
    EXPECT_FLOAT_EQ(distanceSquared(Point3f(0.5f, 0.5f, 0.5f), b), 0.0f);

    EXPECT_FLOAT_EQ(distance(Point3f(2, 0.5f, 0.5f), b), 1.0f);
    EXPECT_FLOAT_EQ(distanceSquared(Point3f(2, 0.5f, 0.5f), b), 1.0f);

    // diagonal outside
    EXPECT_FLOAT_EQ(distanceSquared(Point3f(2, 3, 4), b),
                    sqr(1.0f) + sqr(2.0f) + sqr(3.0f)); // (2-1)^2+(3-1)^2+(4-1)^2
}

TEST(Bounds3, BoundingSphere) {
    Bounds3f b(Point3f(-1, -1, -1), Point3f(1, 1, 1));
    Point3f c;
    Float r;
    b.boundingSphere(&c, &r);

    ExpectVecNear(Vector3f(c.x, c.y, c.z), Vector3f(0, 0, 0));
    EXPECT_NEAR(r, std::sqrt(3.0f), 1e-6f);
}
