/**
 *	@file	unit_test_qvm_vector_length.cpp
 *
 *	@brief	length のテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/length.hpp>
#include <hamon/cmath/fabs.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T>
void Vector2LengthTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	HAMON_CONSTEXPR double error = 0.000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, length(vector2( 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, length(vector2( 3, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, length(vector2(-3, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, length(vector2( 0, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, length(vector2( 0,-4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.2360679774997898, (double)length(vector2( 1, 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.2360679774997898, (double)length(vector2( 1,-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(8.9442719099991592, (double)length(vector2( 4,-8)), error);
}

template <typename T>
void Vector3LengthTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	HAMON_CONSTEXPR double error = 0.000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, length(vector3( 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, length(vector3( 3, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, length(vector3(-3, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, length(vector3( 0, 4, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, length(vector3( 0,-4, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, length(vector3( 0, 0, 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, length(vector3( 0, 0,-5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.7416573867739413, (double)length(vector3( 1, 2, 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.7416573867739413, (double)length(vector3( 1,-2,-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.246950765959598, (double)length(vector3( 4,-8, 5)), error);
}

template <typename T>
void Vector4LengthTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	HAMON_CONSTEXPR double error = 0.000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, length(vector4( 0, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, length(vector4( 3, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, length(vector4(-3, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, length(vector4( 0, 4, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, length(vector4( 0,-4, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, length(vector4( 0, 0, 5, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, length(vector4( 0, 0,-5, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, length(vector4( 0, 0, 0, 6)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, length(vector4( 0, 0, 0,-6)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(5.47722557505, (double)length(vector4( 1, 2, 3, 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(5.47722557505, (double)length(vector4( 1,-2,-3, 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.4403065089, (double)length(vector4( 4,-8, 5, 2)), error);
}

TYPED_TEST(VectorTest, LengthTest)
{
	using T = TypeParam;
	Vector2LengthTest<T>();
	Vector3LengthTest<T>();
	Vector4LengthTest<T>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
