/**
 *	@file	unit_test_qvm_vector_dot.cpp
 *
 *	@brief	dot のテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/dot.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T>
void Vector2DotTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0, 0), vector2( 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0, 0), vector2( 1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0, 0), vector2(-1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0, 0), vector2( 0, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0, 0), vector2( 0,-1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 1, 0), vector2( 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(vector2( 1, 0), vector2( 1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(vector2( 1, 0), vector2(-1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 1, 0), vector2( 0, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 1, 0), vector2( 0,-1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2(-1, 0), vector2( 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(vector2(-1, 0), vector2( 1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(vector2(-1, 0), vector2(-1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2(-1, 0), vector2( 0, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2(-1, 0), vector2( 0,-1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0, 1), vector2( 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0, 1), vector2( 1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0, 1), vector2(-1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(vector2( 0, 1), vector2( 0, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(vector2( 0, 1), vector2( 0,-1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0,-1), vector2( 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0,-1), vector2( 1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector2( 0,-1), vector2(-1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(vector2( 0,-1), vector2( 0, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(vector2( 0,-1), vector2( 0,-1)));
}

template <typename T>
void Vector3DotTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 0, 0), vector3( 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 0, 0), vector3( 1, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 0, 0), vector3(-1, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 0, 0), vector3( 0, 2, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 0, 0), vector3( 0,-2, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 0, 0), vector3( 0, 0, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 0, 0), vector3( 0, 0,-3)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(1, 0, 0), vector3( 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(vector3(1, 0, 0), vector3( 1, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(vector3(1, 0, 0), vector3(-1, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(1, 0, 0), vector3( 0, 1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(1, 0, 0), vector3( 0,-1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(1, 0, 0), vector3( 0, 0, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(1, 0, 0), vector3( 0, 0,-1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(-2, 0, 0), vector3( 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, dot(vector3(-2, 0, 0), vector3( 1, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, dot(vector3(-2, 0, 0), vector3(-1, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(-2, 0, 0), vector3( 0, 1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(-2, 0, 0), vector3( 0,-1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(-2, 0, 0), vector3( 0, 0, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(-2, 0, 0), vector3( 0, 0,-1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 3, 0), vector3( 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 3, 0), vector3( 2, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 3, 0), vector3(-2, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, dot(vector3(0, 3, 0), vector3( 0, 2, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-6, dot(vector3(0, 3, 0), vector3( 0,-2, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 3, 0), vector3( 0, 0, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, 3, 0), vector3( 0, 0,-2)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, -4, 0), vector3( 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, -4, 0), vector3( 2, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, -4, 0), vector3(-2, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-8, dot(vector3(0, -4, 0), vector3( 0, 2, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, dot(vector3(0, -4, 0), vector3( 0,-2, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, -4, 0), vector3( 0, 0, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(vector3(0, -4, 0), vector3( 0, 0,-2)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, dot(vector3(0, 0, 5), vector3( 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, dot(vector3(0, 0, 5), vector3( 3, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, dot(vector3(0, 0, 5), vector3(-3, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, dot(vector3(0, 0, 5), vector3( 0, 3, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, dot(vector3(0, 0, 5), vector3( 0,-3, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 15, dot(vector3(0, 0, 5), vector3( 0, 0, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-15, dot(vector3(0, 0, 5), vector3( 0, 0,-3)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, dot(vector3(0, 0, -6), vector3( 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, dot(vector3(0, 0, -6), vector3( 3, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, dot(vector3(0, 0, -6), vector3(-3, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, dot(vector3(0, 0, -6), vector3( 0, 3, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, dot(vector3(0, 0, -6), vector3( 0,-3, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-18, dot(vector3(0, 0, -6), vector3( 0, 0, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 18, dot(vector3(0, 0, -6), vector3( 0, 0,-3)));
}

template <typename T>
void Vector4DotTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		HAMON_CONSTEXPR vector4 v { 0, 0, 0, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4(-1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0,-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector4 v { 1, 0, 0, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(v, vector4( 1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(v, vector4(-1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0,-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector4 v { -1, 0, 0, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(v, vector4( 1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(v, vector4(-1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0,-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector4 v { 0, 1, 0, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4(-1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(v, vector4( 0, 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(v, vector4( 0,-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector4 v { 0, -1, 0, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4(-1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(v, vector4( 0, 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(v, vector4( 0,-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector4 v { 0, 0, 1, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4(-1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0,-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(v, vector4( 0, 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(v, vector4( 0, 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector4 v { 0, 0, -1, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4(-1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0,-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(v, vector4( 0, 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(v, vector4( 0, 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector4 v { 0, 0, 0, 1 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4(-1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0,-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(v, vector4( 0, 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(v, vector4( 0, 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector4 v { 0, 0, 0, -1 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4(-1, 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0,-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(v, vector4( 0, 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(v, vector4( 0, 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(v, vector4( 0, 0, 0,-1)));
	}
}

TYPED_TEST(VectorTest, DotTest)
{
	using T = TypeParam;
	Vector2DotTest<T>();
	Vector3DotTest<T>();
	Vector4DotTest<T>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
