/**
 *	@file	unit_test_qvm_matrix_negate.cpp
 *
 *	@brief	unary operator-のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

template <typename T>
void Matrix3x3NegateTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;

	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			 0, -1,  2,
			 4,  5, -6,
			-8,  9, 10,
		};
		HAMON_CONSTEXPR auto const m2 = +m1;
		HAMON_CONSTEXPR auto const m3 = -m1;
		static_assert(hamon::is_same<decltype(m2), matrix3x3 const>::value, "");
		static_assert(hamon::is_same<decltype(m3), matrix3x3 const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, m2[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1, m2[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2, m2[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4, m2[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  5, m2[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -6, m2[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8, m2[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  9, m2[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 10, m2[2][2]);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1, m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2, m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4, m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -5, m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  6, m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8, m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -9, m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-10, m3[2][2]);
	}
}

template <typename T>
void Matrix3x4NegateTest()
{
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;

	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			 0, -1,  2, -3,
			 4,  5, -6, -7,
			-8,  9, 10, 11,
		};
		HAMON_CONSTEXPR auto const m2 = +m1;
		HAMON_CONSTEXPR auto const m3 = -m1;
		static_assert(hamon::is_same<decltype(m2), matrix3x4 const>::value, "");
		static_assert(hamon::is_same<decltype(m3), matrix3x4 const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, m2[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1, m2[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2, m2[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -3, m2[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4, m2[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  5, m2[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -6, m2[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -7, m2[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8, m2[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  9, m2[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 10, m2[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 11, m2[2][3]);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1, m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2, m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  3, m3[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4, m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -5, m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  6, m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  7, m3[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8, m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -9, m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-10, m3[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-11, m3[2][3]);
	}
}

template <typename T>
void Matrix4x3NegateTest()
{
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;

	{
		HAMON_CONSTEXPR matrix4x3 const m1
		{
			 0, -1,  2,
			 4,  5, -6,
			-8,  9, 10,
			12, 13, 14,
		};
		HAMON_CONSTEXPR auto const m2 = +m1;
		HAMON_CONSTEXPR auto const m3 = -m1;
		static_assert(hamon::is_same<decltype(m2), matrix4x3 const>::value, "");
		static_assert(hamon::is_same<decltype(m3), matrix4x3 const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, m2[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1, m2[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2, m2[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4, m2[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  5, m2[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -6, m2[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8, m2[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  9, m2[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 10, m2[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 12, m2[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 13, m2[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 14, m2[3][2]);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1, m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2, m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4, m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -5, m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  6, m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8, m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -9, m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-10, m3[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-12, m3[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-13, m3[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-14, m3[3][2]);
	}
}

template <typename T>
void Matrix4x4NegateTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			 0, -1,  2, -3,
			 4,  5, -6, -7,
			-8,  9, 10, 11,
			12, 13, 14, 15,
		};
		HAMON_CONSTEXPR auto const m2 = +m1;
		HAMON_CONSTEXPR auto const m3 = -m1;
		static_assert(hamon::is_same<decltype(m2), matrix4x4 const>::value, "");
		static_assert(hamon::is_same<decltype(m3), matrix4x4 const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, m2[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1, m2[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2, m2[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -3, m2[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4, m2[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  5, m2[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -6, m2[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -7, m2[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8, m2[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  9, m2[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 10, m2[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 11, m2[2][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 12, m2[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 13, m2[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 14, m2[3][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 15, m2[3][3]);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1, m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2, m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  3, m3[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4, m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -5, m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  6, m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  7, m3[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8, m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -9, m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-10, m3[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-11, m3[2][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-12, m3[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-13, m3[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-14, m3[3][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-15, m3[3][3]);
	}
}

TYPED_TEST(MatrixTest, NegateTest)
{
	using T = TypeParam;
	Matrix3x3NegateTest<T>();
	Matrix3x4NegateTest<T>();
	Matrix4x3NegateTest<T>();
	Matrix4x4NegateTest<T>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
