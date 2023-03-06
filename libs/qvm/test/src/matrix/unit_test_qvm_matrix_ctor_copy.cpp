/**
 *	@file	unit_test_qvm_matrix_ctor_copy.cpp
 *
 *	@brief	matrix のコピーコンストラクタのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

template <typename T>
void Matrix3x3CtorCopyTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;

	static_assert( hamon::is_copy_constructible<matrix3x3>::value, "");
	static_assert( hamon::is_nothrow_copy_constructible<matrix3x3>::value, "");
	static_assert( hamon::is_trivially_copy_constructible<matrix3x3>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<matrix3x3>::value, "");

	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			 0,  1,  2,
			 3,  4,  5,
			 6,  7,  8,
		};
		HAMON_CONSTEXPR matrix3x3 const m2{m1};
		
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m2[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m2[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m2[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, m2[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m2[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m2[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m2[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, m2[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m2[2][2]);
	}
}

template <typename T>
void Matrix3x4CtorCopyTest()
{
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;

	static_assert( hamon::is_copy_constructible<matrix3x4>::value, "");
	static_assert( hamon::is_nothrow_copy_constructible<matrix3x4>::value, "");
	static_assert( hamon::is_trivially_copy_constructible<matrix3x4>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<matrix3x4>::value, "");

	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			 0,  1,  2,  3,
			 4,  5,  6,  7,
			 8,  9, 10, 11,
		};
		HAMON_CONSTEXPR matrix3x4 const m2{m1};
		
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m2[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m2[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m2[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, m2[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m2[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m2[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m2[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, m2[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m2[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m2[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m2[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m2[2][3]);
	}
}

template <typename T>
void Matrix4x3CtorCopyTest()
{
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;

	static_assert( hamon::is_copy_constructible<matrix4x3>::value, "");
	static_assert( hamon::is_nothrow_copy_constructible<matrix4x3>::value, "");
	static_assert( hamon::is_trivially_copy_constructible<matrix4x3>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<matrix4x3>::value, "");

	{
		HAMON_CONSTEXPR matrix4x3 const m1
		{
			 0,  1,  2,
			 3,  4,  5,
			 6,  7,  8,
			 9, 10, 11,
		};
		HAMON_CONSTEXPR matrix4x3 const m2{m1};
		
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m2[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m2[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m2[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, m2[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m2[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m2[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m2[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, m2[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m2[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m2[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m2[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m2[3][2]);
	}
}

template <typename T>
void Matrix4x4CtorCopyTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	static_assert( hamon::is_copy_constructible<matrix4x4>::value, "");
	static_assert( hamon::is_nothrow_copy_constructible<matrix4x4>::value, "");
	static_assert( hamon::is_trivially_copy_constructible<matrix4x4>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<matrix4x4>::value, "");

	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			 0,  1,  2,  3,
			 4,  5,  6,  7,
			 8,  9, 10, 11,
			12, 13, 14, 15,
		};
		HAMON_CONSTEXPR matrix4x4 const m2{m1};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m2[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m2[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m2[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, m2[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m2[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m2[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m2[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, m2[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m2[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m2[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m2[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m2[2][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, m2[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, m2[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, m2[3][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, m2[3][3]);
	}
}

TYPED_TEST(MatrixTest, CtorCopyTest)
{
	using T = TypeParam;
	Matrix3x3CtorCopyTest<T>();
	Matrix3x4CtorCopyTest<T>();
	Matrix4x3CtorCopyTest<T>();
	Matrix4x4CtorCopyTest<T>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
