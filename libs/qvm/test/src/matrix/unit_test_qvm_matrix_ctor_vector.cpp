/**
 *	@file	unit_test_qvm_matrix_ctor_vector.cpp
 *
 *	@brief	ベクトル型を受け取るmatrixのコンストラクタのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/qvm/vector.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

template <typename T>
void Matrix3x3CtorVectorTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(!hamon::is_constructible<matrix3x3, vector3, vector3, vector3, vector3, vector3>::value, "");
	static_assert(!hamon::is_constructible<matrix3x3, vector3, vector3, vector3, vector3>::value, "");
	static_assert( hamon::is_constructible<matrix3x3, vector3, vector3, vector3>::value, "");
	static_assert(!hamon::is_constructible<matrix3x3, vector3, vector3>::value, "");

	static_assert( hamon::is_nothrow_constructible<matrix3x3, vector3, vector3, vector3>::value, "");

	static_assert( hamon::is_implicitly_constructible<matrix3x3, vector3, vector3, vector3>::value, "");

	static_assert(!hamon::is_constructible<matrix3x3, vector2, vector2, vector2>::value, "");
	static_assert(!hamon::is_constructible<matrix3x3, vector4, vector4, vector4>::value, "");

	// vector4型を4つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix3x3 const m
		{
			vector3{ 0,  1,  2},
			vector3{ 4,  5,  6},
			vector3{ 8,  9, 10},
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m[2][2]);
	}
	{
		HAMON_CONSTEXPR matrix3x3 const m(
			vector3(11, 12, 13),
			vector3(21, 22, 23),
			vector3(31, 32, 33)
		);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, m[2][2]);
	}
}

template <typename T>
void Matrix3x4CtorVectorTest()
{
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(!hamon::is_constructible<matrix3x4, vector4, vector4, vector4, vector4, vector4>::value, "");
	static_assert(!hamon::is_constructible<matrix3x4, vector4, vector4, vector4, vector4>::value, "");
	static_assert( hamon::is_constructible<matrix3x4, vector4, vector4, vector4>::value, "");
	static_assert(!hamon::is_constructible<matrix3x4, vector4, vector4>::value, "");

	static_assert( hamon::is_nothrow_constructible<matrix3x4, vector4, vector4, vector4>::value, "");

	static_assert( hamon::is_implicitly_constructible<matrix3x4, vector4, vector4, vector4>::value, "");

	static_assert(!hamon::is_constructible<matrix3x4, vector2, vector2, vector2>::value, "");
	static_assert(!hamon::is_constructible<matrix3x4, vector3, vector3, vector3>::value, "");

	// vector4型を4つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix3x4 const m
		{
			vector4{ 0,  1,  2,  3},
			vector4{ 4,  5,  6,  7},
			vector4{ 8,  9, 10, 11},
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
	{
		HAMON_CONSTEXPR matrix3x4 const m(
			vector4(11, 12, 13, 14),
			vector4(21, 22, 23, 24),
			vector4(31, 32, 33, 34)
		);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, m[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, m[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, m[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(34, m[2][3]);
	}
}

template <typename T>
void Matrix4x3CtorVectorTest()
{
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(!hamon::is_constructible<matrix4x3, vector3, vector3, vector3, vector3, vector3>::value, "");
	static_assert( hamon::is_constructible<matrix4x3, vector3, vector3, vector3, vector3>::value, "");
	static_assert(!hamon::is_constructible<matrix4x3, vector3, vector3, vector3>::value, "");
	static_assert(!hamon::is_constructible<matrix4x3, vector3, vector3>::value, "");

	static_assert( hamon::is_nothrow_constructible<matrix4x3, vector3, vector3, vector3, vector3>::value, "");

	static_assert( hamon::is_implicitly_constructible<matrix4x3, vector3, vector3, vector3, vector3>::value, "");

	static_assert(!hamon::is_constructible<matrix4x3, vector2, vector2, vector2, vector2>::value, "");
	static_assert(!hamon::is_constructible<matrix4x3, vector4, vector4, vector4, vector4>::value, "");

	// vector4型を4つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix4x3 const m
		{
			vector3{ 0,  1,  2},
			vector3{ 4,  5,  6},
			vector3{ 8,  9, 10},
			vector3{12, 13, 14},
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, m[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, m[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, m[3][2]);
	}
	{
		HAMON_CONSTEXPR matrix4x3 const m(
			vector3(11, 12, 13),
			vector3(21, 22, 23),
			vector3(31, 32, 33),
			vector3(41, 42, 43)
		);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, m[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(41, m[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(43, m[3][2]);
	}
}

template <typename T>
void Matrix4x4CtorVectorTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(!hamon::is_constructible<matrix4x4, vector4, vector4, vector4, vector4, vector4>::value, "");
	static_assert( hamon::is_constructible<matrix4x4, vector4, vector4, vector4, vector4>::value, "");
	static_assert(!hamon::is_constructible<matrix4x4, vector4, vector4, vector4>::value, "");
	static_assert(!hamon::is_constructible<matrix4x4, vector4, vector4>::value, "");

	static_assert( hamon::is_nothrow_constructible<matrix4x4, vector4, vector4, vector4, vector4>::value, "");

	static_assert( hamon::is_implicitly_constructible<matrix4x4, vector4, vector4, vector4, vector4>::value, "");

	static_assert(!hamon::is_constructible<matrix4x4, vector2, vector2, vector2, vector2>::value, "");
	static_assert(!hamon::is_constructible<matrix4x4, vector3, vector3, vector3, vector3>::value, "");

	// vector4型を4つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR matrix4x4 const m
		{
			vector4{ 0,  1,  2,  3},
			vector4{ 4,  5,  6,  7},
			vector4{ 8,  9, 10, 11},
			vector4{12, 13, 14, 15},
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
	{
		HAMON_CONSTEXPR matrix4x4 const m(
			vector4(11, 12, 13, 14),
			vector4(21, 22, 23, 24),
			vector4(31, 32, 33, 34),
			vector4(41, 42, 43, 44)
		);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, m[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, m[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, m[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, m[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, m[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, m[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, m[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, m[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, m[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, m[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(34, m[2][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(41, m[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, m[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(43, m[3][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(44, m[3][3]);
	}
}

TYPED_TEST(MatrixTest, CtorVectorTest)
{
	using T = TypeParam;
	Matrix3x3CtorVectorTest<T>();
	Matrix3x4CtorVectorTest<T>();
	Matrix4x3CtorVectorTest<T>();
	Matrix4x4CtorVectorTest<T>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
