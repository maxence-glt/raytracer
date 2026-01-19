#include <gtest/gtest.h>

#include "util/math.hpp"
#include "util/transform.hpp"

constexpr Float kEps = static_cast<Float>(1e-5);
constexpr Float kEpsLoose = static_cast<Float>(1e-4);

template <typename T>
void ExpectNear3(T ax, T ay, T az, T bx, T by, T bz, T eps = static_cast<T>(kEps)) {
    EXPECT_NEAR(ax, bx, eps);
    EXPECT_NEAR(ay, by, eps);
    EXPECT_NEAR(az, bz, eps);
}

template <typename T>
void ExpectNearPoint(const Point3<T>& a, const Point3<T>& b, T eps = static_cast<T>(kEps)) {
    ExpectNear3(a.x, a.y, a.z, b.x, b.y, b.z, eps);
}

template <typename T>
void ExpectNearVector(const Vector3<T>& a, const Vector3<T>& b, T eps = static_cast<T>(kEps)) {
    ExpectNear3(a.x, a.y, a.z, b.x, b.y, b.z, eps);
}

template <typename T>
void ExpectNearNormal(const Normal3<T>& a, const Normal3<T>& b, T eps = static_cast<T>(kEps)) {
    ExpectNear3(a.x, a.y, a.z, b.x, b.y, b.z, eps);
}

template <int N>
void ExpectMatrixNear(const SquareMatrix<N>& a, const SquareMatrix<N>& b, Float eps = kEps) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            EXPECT_NEAR(a[i][j], b[i][j], eps) << "at (" << i << "," << j << ")";
}

testing::AssertionResult IsAffine(const Transform& t, Float eps = kEps) {
    const auto& m = t.getMatrix();
    auto bad = [&](int i, int j, Float expected) {
        return std::fabs(m[i][j] - expected) > eps;
    };

    if (bad(3, 0, 0) || bad(3, 1, 0) || bad(3, 2, 0) || bad(3, 3, 1)) {
        return testing::AssertionFailure()
            << "Not affine: bottom row is ["
            << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3]
            << "] but expected approx [0, 0, 0, 1]. "
            << "This usually indicates SquareMatrix ctor ordering/indexing mismatch.";
    }
    return testing::AssertionSuccess();
}

TEST(TransformMatrixLayout, TranslateIsAffineAndHasExpectedTranslationColumn) {
    Transform t = translate(Vector3f(1, 2, 3));
    ASSERT_TRUE(IsAffine(t));

    const auto& m = t.getMatrix();
    const auto& mi = t.getInverseMatrix();

    EXPECT_NEAR(m[0][3], 1, kEps);
    EXPECT_NEAR(m[1][3], 2, kEps);
    EXPECT_NEAR(m[2][3], 3, kEps);

    EXPECT_NEAR(mi[0][3], -1, kEps);
    EXPECT_NEAR(mi[1][3], -2, kEps);
    EXPECT_NEAR(mi[2][3], -3, kEps);
}

TEST(TransformMatrixLayout, ScaleIsAffineAndHasExpectedDiagonal) {
    Transform s = scale(2, 3, 4);
    ASSERT_TRUE(IsAffine(s));

    const auto& m = s.getMatrix();
    const auto& mi = s.getInverseMatrix();

    EXPECT_NEAR(m[0][0], 2, kEps);
    EXPECT_NEAR(m[1][1], 3, kEps);
    EXPECT_NEAR(m[2][2], 4, kEps);

    EXPECT_NEAR(mi[0][0], Float(1) / 2, kEps);
    EXPECT_NEAR(mi[1][1], Float(1) / 3, kEps);
    EXPECT_NEAR(mi[2][2], Float(1) / 4, kEps);
}

TEST(TransformMatrixLayout, RotateZIsAffineAndInverseEqualsTranspose) {
    Transform r = rotateZ(90);
    ASSERT_TRUE(IsAffine(r));

    SquareMatrix<4> mt = transpose(r.getMatrix());
    ExpectMatrixNear(r.getInverseMatrix(), mt, kEpsLoose);
}

TEST(TransformBehavior, TranslationAffectsPointsButNotVectors) {
    Transform t = translate(Vector3f(1, 2, 3));
    ASSERT_TRUE(IsAffine(t));

    Point3f p(4, 5, 6);
    Vector3f v(4, 5, 6);

    ExpectNearPoint(t(p), Point3f(5, 7, 9));
    ExpectNearVector(t(v), v);

    ExpectNearPoint(t.applyInverse(t(p)), p);
    ExpectNearVector(t.applyInverse(t(v)), v);
}

TEST(TransformBehavior, ScaleAffectsPointsVectorsAndNormalsCorrectly) {
    Transform s = scale(2, 3, 4);
    ASSERT_TRUE(IsAffine(s));

    Point3f p(1, 2, 3);
    Vector3f v(1, 2, 3);
    Normal3f n(1, 2, 3);

    ExpectNearPoint(s(p), Point3f(2, 6, 12));
    ExpectNearVector(s(v), Vector3f(2, 6, 12));

    ExpectNearNormal(s(n), Normal3f(Float(1) / 2, Float(2) / 3, Float(3) / 4));

    ExpectNearPoint(s.applyInverse(s(p)), p);
    ExpectNearVector(s.applyInverse(s(v)), v);
}

TEST(TransformBehavior, RotateAxes90Degrees) {
    Transform rz = rotateZ(90);
    Transform rx = rotateX(90);
    Transform ry = rotateY(90);

    ASSERT_TRUE(IsAffine(rz));
    ASSERT_TRUE(IsAffine(rx));
    ASSERT_TRUE(IsAffine(ry));

    ExpectNearVector(rz(Vector3f(1, 0, 0)), Vector3f(0, 1, 0), kEpsLoose);
    ExpectNearVector(rx(Vector3f(0, 1, 0)), Vector3f(0, 0, 1), kEpsLoose);
    ExpectNearVector(ry(Vector3f(0, 0, 1)), Vector3f(1, 0, 0), kEpsLoose);

    Vector3f v(0.3f, -1.2f, 5.0f);
    ExpectNearVector(rz.applyInverse(rz(v)), v, kEpsLoose);
}

TEST(TransformBehavior, CompositionMatrixAndInverseChainMatch) {
    Transform t1 = translate(Vector3f(10, 0, 0));
    Transform t2 = scale(2, 1, 1);
    ASSERT_TRUE(IsAffine(t1));
    ASSERT_TRUE(IsAffine(t2));

    Transform c = t1 * t2;
    ASSERT_TRUE(IsAffine(c));

    ExpectMatrixNear(c.getMatrix(), t1.getMatrix() * t2.getMatrix(), kEpsLoose);
    ExpectMatrixNear(c.getInverseMatrix(), t2.getInverseMatrix() * t1.getInverseMatrix(), kEpsLoose);

    Point3f p(1, 2, 3);
    ExpectNearPoint(c(p), t1(t2(p)), kEpsLoose);
}

TEST(TransformBehavior, TransposeReturnsTransposedMatrices) {
    Transform t = translate(Vector3f(1, 2, 3)) *
                  rotateX(17) *
                  scale(2, 3, 4);
    ASSERT_TRUE(IsAffine(t));

    Transform tt = transpose(t);
    ExpectMatrixNear(tt.getMatrix(), transpose(t.getMatrix()), kEpsLoose);
    ExpectMatrixNear(tt.getInverseMatrix(), transpose(t.getInverseMatrix()), kEpsLoose);
}

TEST(TransformBehavior, RayTransformsOriginAndDirection) {
    Transform t = translate(Vector3f(1, 2, 3)) * scale(2, 3, 4);
    ASSERT_TRUE(IsAffine(t));

    Ray r(Point3f(1, 1, 1), Vector3f(1, 0, 0), /*t=*/0);
    Ray rt = t(r, nullptr);

    ExpectNearPoint(rt.o, Point3f(1 * 2 + 1, 1 * 3 + 2, 1 * 4 + 3), kEpsLoose);
    ExpectNearVector(rt.d, Vector3f(2, 0, 0), kEpsLoose);

    Ray back = t.applyInverse(rt, nullptr);
    ExpectNearPoint(back.o, r.o, kEpsLoose);
    ExpectNearVector(back.d, r.d, kEpsLoose);
}

TEST(TransformBehavior, BoundsTranslateAndScalePositive) {
    Bounds3f b(Point3f(-1, -2, -3), Point3f(4, 5, 6));

    Transform t = translate(Vector3f(10, 20, 30));
    Transform s = scale(2, 3, 4);
    ASSERT_TRUE(IsAffine(t));
    ASSERT_TRUE(IsAffine(s));

    Bounds3f bt = t(b);
    ExpectNearPoint(bt.pMin, Point3f(9, 18, 27), kEpsLoose);
    ExpectNearPoint(bt.pMax, Point3f(14, 25, 36), kEpsLoose);

    Bounds3f bs = s(b);
    ExpectNearPoint(bs.pMin, Point3f(-2, -6, -12), kEpsLoose);
    ExpectNearPoint(bs.pMax, Point3f(8, 15, 24), kEpsLoose);
}

TEST(TransformCtor, ConstructFromSingularMatrixSetsInverseToNaN) {
    // Determinant is 0 because last row is all zeros.
    SquareMatrix<4> singular(1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 0);

    Transform t(singular);
    const SquareMatrix<4>& inv = t.getInverseMatrix();

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            EXPECT_TRUE(std::isnan(inv[i][j])) << "Expected NaN at (" << i << "," << j << ")";
}

TEST(TransformOps, EqualityAndInequalityUseMatrix) {
    Transform a = translate(Vector3f(1, 2, 3));
    Transform b = translate(Vector3f(1, 2, 3));
    Transform c = translate(Vector3f(1, 2, 4));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a == c);
}

TEST(TransformLookAt, MapsCameraOriginToPosAndPosToOrigin) {
    const Point3f pos(1, 2, 3);
    const Point3f look(1, 2, 4);
    const Vector3f up(0, 1, 0);

    Transform t = lookAt(pos, look, up);
    ASSERT_TRUE(IsAffine(t));

    ExpectNearPoint(t.applyInverse(Point3f(0, 0, 0)), pos, kEpsLoose);
    ExpectNearPoint(t(pos), Point3f(0, 0, 0), kEpsLoose);
    ExpectNearPoint(t(Point3f(1, 2, 4)), Point3f(0, 0, 1), kEpsLoose);
}

TEST(TransformLookAt, WorldFromCameraHasExpectedTranslationInInverseMatrix) {
    const Point3f pos(10, -5, 7);
    const Point3f look(10, -5, 8);
    const Vector3f up(0, 1, 0);

    Transform t = lookAt(pos, look, up);
    ASSERT_TRUE(IsAffine(t));

    const SquareMatrix<4>& wfc = t.getInverseMatrix();

    EXPECT_NEAR(wfc[0][3], pos.x, kEpsLoose);
    EXPECT_NEAR(wfc[1][3], pos.y, kEpsLoose);
    EXPECT_NEAR(wfc[2][3], pos.z, kEpsLoose);
    EXPECT_NEAR(wfc[3][3], 1,     kEpsLoose);

    EXPECT_NEAR(wfc[3][0], 0, kEpsLoose);
    EXPECT_NEAR(wfc[3][1], 0, kEpsLoose);
    EXPECT_NEAR(wfc[3][2], 0, kEpsLoose);
}

// ---------------------------
TEST(TransformAxisRotate, RotateAroundZMatchesRotateZ) {
    Transform rz = rotateZ(90);
    Transform ra = rotate(90, Vector3f(0, 0, 2));

    ASSERT_TRUE(IsAffine(rz));
    ASSERT_TRUE(IsAffine(ra));

    Vector3f v(1, 0, 0);
    ExpectNearVector(ra(v), rz(v), kEpsLoose);
}
