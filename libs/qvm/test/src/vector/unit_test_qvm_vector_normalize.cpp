/**
 *	@file	unit_test_qvm_vector_normalize.cpp
 *
 *	@brief	normalize のテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/operators.hpp>
#include <hamon/qvm/vector/normalize.hpp>
#include <hamon/cmath/fabs.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T>
void Vector2NormalizeTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 0, 0), normalize(vector2(  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 1, 0), normalize(vector2(  1,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-1, 0), normalize(vector2( -1,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 1, 0), normalize(vector2( 10,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-1, 0), normalize(vector2(-10,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 0, 1), normalize(vector2(  0,  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 0,-1), normalize(vector2(  0, -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 0, 1), normalize(vector2(  0,  5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 0,-1), normalize(vector2(  0, -5)));

	HAMON_CONSTEXPR double error = 0.000001;
	{
		HAMON_CONSTEXPR auto const t = normalize(vector2(1, 2));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.44721359549995793, (double)t[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.89442719099991586, (double)t[1], error);
	}
	{
		HAMON_CONSTEXPR auto const t = normalize(vector2(-5, 6));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.64018439966447993, (double)t[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.76822127959737585, (double)t[1], error);
	}
}

template <typename T>
void Vector3NormalizeTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), normalize(vector3(  0,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 1, 0, 0), normalize(vector3(  1,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-1, 0, 0), normalize(vector3( -1,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 1, 0, 0), normalize(vector3( 10,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-1, 0, 0), normalize(vector3(-10,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 1, 0), normalize(vector3(  0,  1,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0,-1, 0), normalize(vector3(  0, -1,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 1, 0), normalize(vector3(  0,  5,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0,-1, 0), normalize(vector3(  0, -5,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 1), normalize(vector3(  0,  0,  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0,-1), normalize(vector3(  0,  0, -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 1), normalize(vector3(  0,  0, 42)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0,-1), normalize(vector3(  0,  0,-42)));

	HAMON_CONSTEXPR double error = 0.000001;
	{
		HAMON_CONSTEXPR auto const t = normalize(vector3(1, 2, 3));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2672612419124244,  (double)t.x(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.53452248382484879, (double)t.y(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.80178372573727319, (double)t.z(), error);
	}
	{
		HAMON_CONSTEXPR auto const t = normalize(vector3(-5, 6, 7));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.47673129462279618, (double)t.x(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.57207755354735534, (double)t.y(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.66742381247191462, (double)t.z(), error);
	}
}

template <typename T>
void Vector4NormalizeTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0, 0, 0, 0), normalize(vector4(  0,  0,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 1, 0, 0, 0), normalize(vector4(  1,  0,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-1, 0, 0, 0), normalize(vector4( -1,  0,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 1, 0, 0, 0), normalize(vector4( 10,  0,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-1, 0, 0, 0), normalize(vector4(-10,  0,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0, 1, 0, 0), normalize(vector4(  0,  1,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0,-1, 0, 0), normalize(vector4(  0, -1,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0, 1, 0, 0), normalize(vector4(  0,  5,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0,-1, 0, 0), normalize(vector4(  0, -5,  0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0, 0, 1, 0), normalize(vector4(  0,  0,  1,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0, 0,-1, 0), normalize(vector4(  0,  0, -1,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0, 0, 1, 0), normalize(vector4(  0,  0, 42,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0, 0,-1, 0), normalize(vector4(  0,  0,-42,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0, 0, 0, 1), normalize(vector4(  0,  0,  0,  3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0, 0, 0,-1), normalize(vector4(  0,  0,  0, -3)));

	HAMON_CONSTEXPR double error = 0.000001;
	{
		HAMON_CONSTEXPR auto const t = normalize(vector4(1, 2, 3, 4));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.18257418583505536, (double)t.x(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.36514837167011072, (double)t.y(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.54772255750516607, (double)t.z(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.73029674334022143, (double)t.w(), error);
	}
	{
		HAMON_CONSTEXPR auto const t = normalize(vector4(-5, 6, 7, -8));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.37904902178945171, (double)t.x(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.45485882614734202, (double)t.y(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.53066863050523239, (double)t.z(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.60647843486312270, (double)t.w(), error);
	}
}

TYPED_TEST(VectorFloatTest, NormalizeTest)
{
	using T = TypeParam;
	Vector2NormalizeTest<T>();
	Vector3NormalizeTest<T>();
	Vector4NormalizeTest<T>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
