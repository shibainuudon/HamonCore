/**
 *	@file	unit_test_qvm_vector_length_sq.cpp
 *
 *	@brief	length_sq のテスト
 */

#include <hamon/qvm/vector.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T>
void Vector2LengthSqTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, length_sq(vector2(0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  9, length_sq(vector2(3, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16, length_sq(vector2(0, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  5, length_sq(vector2(1, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  5, length_sq(vector2(1,-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 80, length_sq(vector2(4,-8)));
}

template <typename T>
void Vector3LengthSqTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, length_sq(vector3(0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  9, length_sq(vector3(3, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16, length_sq(vector3(0, 4, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 25, length_sq(vector3(0, 0,-5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 14, length_sq(vector3(1, 2, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 14, length_sq(vector3(1,-2, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(105, length_sq(vector3(4,-8, 5)));
}

template <typename T>
void Vector4LengthSqTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, length_sq(vector4(0, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  9, length_sq(vector4(3, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16, length_sq(vector4(0, 4, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 25, length_sq(vector4(0, 0,-5, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 36, length_sq(vector4(0, 0, 0, 6)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 30, length_sq(vector4(1, 2, 3, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 30, length_sq(vector4(1,-2, 3, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 30, length_sq(vector4(1, 2, 3,-4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(109, length_sq(vector4(4,-8, 5, 2)));
}

TYPED_TEST(VectorTest, LengthSqTest)
{
	using T = TypeParam;
	Vector2LengthSqTest<T>();
	Vector3LengthSqTest<T>();
	Vector4LengthSqTest<T>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
