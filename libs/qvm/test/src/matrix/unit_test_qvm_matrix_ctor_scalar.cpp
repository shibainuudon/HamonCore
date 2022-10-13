/**
 *	@file	unit_test_qvm_matrix_ctor_scalar.cpp
 *
 *	@brief	スカラー型を受け取る matrix のコンストラクタのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

template <typename T>
void Matrix3x3CtorScalarTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;

	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert( std::is_constructible<matrix3x3, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x3, T, T>::value, "");
	static_assert( std::is_constructible<matrix3x3, T>::value, "");

	static_assert( std::is_nothrow_constructible<matrix3x3, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<matrix3x3, T>::value, "");

	static_assert( hamon::is_implicitly_constructible<matrix3x3, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<matrix3x3, T>::value, "");

	// スカラー型を1つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix3x3 const m {42};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[2][2]);
	}

	// スカラー型を9個受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix3x3 const m
		{
			 0,  1,  2,
			 3,  4,  5,
			 6,  7,  8,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m[2][2]);
	}
}

template <typename T>
void Matrix3x4CtorScalarTest()
{
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;

	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert( std::is_constructible<matrix3x4, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix3x4, T, T>::value, "");
	static_assert( std::is_constructible<matrix3x4, T>::value, "");

	static_assert( std::is_nothrow_constructible<matrix3x4, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<matrix3x4, T>::value, "");

	static_assert( hamon::is_implicitly_constructible<matrix3x4, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<matrix3x4, T>::value, "");

	// スカラー型を1つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix3x4 const m {42};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[2][3]);
	}

	// スカラー型を12個受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix3x4 const m
		{
			 0,  1,  2,  3,
			 4,  5,  6,  7,
			 8,  9, 10, 11,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, m[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, m[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m[2][3]);
	}
}

template <typename T>
void Matrix4x3CtorScalarTest()
{
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;

	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert( std::is_constructible<matrix4x3, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x3, T, T>::value, "");
	static_assert( std::is_constructible<matrix4x3, T>::value, "");

	static_assert( std::is_nothrow_constructible<matrix4x3, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<matrix4x3, T>::value, "");

	static_assert( hamon::is_implicitly_constructible<matrix4x3, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<matrix4x3, T>::value, "");

	// スカラー型を1つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix4x3 const m {42};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[3][2]);
	}

	// スカラー型を12個受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix4x3 const m
		{
			 0,  1,  2,
			 3,  4,  5,
			 6,  7,  8,
			 9, 10, 11,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m[3][2]);
	}
}

template <typename T>
void Matrix4x4CtorScalarTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert( std::is_constructible<matrix4x4, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T, T>::value, "");
	static_assert(!std::is_constructible<matrix4x4, T, T>::value, "");
	static_assert( std::is_constructible<matrix4x4, T>::value, "");

	static_assert( std::is_nothrow_constructible<matrix4x4, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<matrix4x4, T>::value, "");

	static_assert( hamon::is_implicitly_constructible<matrix4x4, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<matrix4x4, T>::value, "");

	// スカラー型を1つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix4x4 const m {42};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[2][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[3][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[3][3]);
	}

	// スカラー型を16個受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix4x4 const m
		{
			 0,  1,  2,  3,
			 4,  5,  6,  7,
			 8,  9, 10, 11,
			12, 13, 14, 15,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, m[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, m[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m[2][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, m[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, m[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, m[3][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, m[3][3]);
	}
}

TYPED_TEST(MatrixTest, CtorScalarTest)
{
	using T = TypeParam;
	Matrix3x3CtorScalarTest<T>();
	Matrix3x4CtorScalarTest<T>();
	Matrix4x3CtorScalarTest<T>();
	Matrix4x4CtorScalarTest<T>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
