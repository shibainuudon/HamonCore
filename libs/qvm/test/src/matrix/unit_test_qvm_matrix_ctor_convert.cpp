/**
 *	@file	unit_test_qvm_matrix_ctor_convert.cpp
 *
 *	@brief	matrix の変換コンストラクタのテスト
 */

#include <hamon/qvm/matrix.hpp>
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
void Matrix3x3CtorConvertTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	using matrix3x3i = hamon::qvm::matrix<int, 3, 3>;
	using matrix3x3f = hamon::qvm::matrix<float, 3, 3>;

	static_assert(hamon::is_constructible<matrix3x3,  matrix3x3i const&>::value, "");
	static_assert(hamon::is_constructible<matrix3x3,  matrix3x3f const&>::value, "");
	static_assert(hamon::is_constructible<matrix3x3i, matrix3x3  const&>::value, "");
	static_assert(hamon::is_constructible<matrix3x3i, matrix3x3f const&>::value, "");
	static_assert(hamon::is_constructible<matrix3x3f, matrix3x3  const&>::value, "");
	static_assert(hamon::is_constructible<matrix3x3f, matrix3x3i const&>::value, "");

	static_assert(hamon::is_nothrow_constructible<matrix3x3,  matrix3x3i const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix3x3,  matrix3x3f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix3x3i, matrix3x3  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix3x3i, matrix3x3f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix3x3f, matrix3x3  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix3x3f, matrix3x3i const&>::value, "");

	static_assert(hamon::is_implicitly_constructible<matrix3x3,  matrix3x3i const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix3x3,  matrix3x3f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix3x3i, matrix3x3  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix3x3i, matrix3x3f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix3x3f, matrix3x3  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix3x3f, matrix3x3i const&>::value, "");

	// 要素数が違ったらコンストラクトできない
	static_assert(!hamon::is_constructible<matrix3x3, matrix3x4 const&>::value, "");
	static_assert(!hamon::is_constructible<matrix3x3, matrix4x3 const&>::value, "");
	static_assert(!hamon::is_constructible<matrix3x3, matrix4x4 const&>::value, "");

	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			 0,  1,  2,
			 4,  5,  6,
			 8,  9, 10,
		};

		HAMON_CONSTEXPR matrix3x3i const m2{m1};
		HAMON_CONSTEXPR matrix3x3f const m3{m1};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m2[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m2[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m2[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m2[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m2[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m2[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m2[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m2[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m2[2][2]);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m3[2][2]);
	}
}

template <typename T>
void Matrix3x4CtorConvertTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	using matrix3x4i = hamon::qvm::matrix<int, 3, 4>;
	using matrix3x4f = hamon::qvm::matrix<float, 3, 4>;

	static_assert(hamon::is_constructible<matrix3x4,  matrix3x4i const&>::value, "");
	static_assert(hamon::is_constructible<matrix3x4,  matrix3x4f const&>::value, "");
	static_assert(hamon::is_constructible<matrix3x4i, matrix3x4  const&>::value, "");
	static_assert(hamon::is_constructible<matrix3x4i, matrix3x4f const&>::value, "");
	static_assert(hamon::is_constructible<matrix3x4f, matrix3x4  const&>::value, "");
	static_assert(hamon::is_constructible<matrix3x4f, matrix3x4i const&>::value, "");

	static_assert(hamon::is_nothrow_constructible<matrix3x4,  matrix3x4i const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix3x4,  matrix3x4f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix3x4i, matrix3x4  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix3x4i, matrix3x4f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix3x4f, matrix3x4  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix3x4f, matrix3x4i const&>::value, "");

	static_assert(hamon::is_implicitly_constructible<matrix3x4,  matrix3x4i const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix3x4,  matrix3x4f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix3x4i, matrix3x4  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix3x4i, matrix3x4f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix3x4f, matrix3x4  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix3x4f, matrix3x4i const&>::value, "");

	// 要素数が違ったらコンストラクトできない
	static_assert(!hamon::is_constructible<matrix3x4, matrix3x3 const&>::value, "");
	static_assert(!hamon::is_constructible<matrix3x4, matrix4x3 const&>::value, "");
	static_assert(!hamon::is_constructible<matrix3x4, matrix4x4 const&>::value, "");

	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			 0,  1,  2,  3,
			 4,  5,  6,  7,
			 8,  9, 10, 11,
		};

		HAMON_CONSTEXPR matrix3x4i const m2{m1};
		HAMON_CONSTEXPR matrix3x4f const m3{m1};

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

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, m3[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, m3[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m3[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m3[2][3]);
	}
}

template <typename T>
void Matrix4x3CtorConvertTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	using matrix4x3i = hamon::qvm::matrix<int, 4, 3>;
	using matrix4x3f = hamon::qvm::matrix<float, 4, 3>;

	static_assert(hamon::is_constructible<matrix4x3,  matrix4x3i const&>::value, "");
	static_assert(hamon::is_constructible<matrix4x3,  matrix4x3f const&>::value, "");
	static_assert(hamon::is_constructible<matrix4x3i, matrix4x3  const&>::value, "");
	static_assert(hamon::is_constructible<matrix4x3i, matrix4x3f const&>::value, "");
	static_assert(hamon::is_constructible<matrix4x3f, matrix4x3  const&>::value, "");
	static_assert(hamon::is_constructible<matrix4x3f, matrix4x3i const&>::value, "");

	static_assert(hamon::is_nothrow_constructible<matrix4x3,  matrix4x3i const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix4x3,  matrix4x3f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix4x3i, matrix4x3  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix4x3i, matrix4x3f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix4x3f, matrix4x3  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix4x3f, matrix4x3i const&>::value, "");

	static_assert(hamon::is_implicitly_constructible<matrix4x3,  matrix4x3i const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix4x3,  matrix4x3f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix4x3i, matrix4x3  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix4x3i, matrix4x3f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix4x3f, matrix4x3  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix4x3f, matrix4x3i const&>::value, "");

	// 要素数が違ったらコンストラクトできない
	static_assert(!hamon::is_constructible<matrix4x3, matrix3x3 const&>::value, "");
	static_assert(!hamon::is_constructible<matrix4x3, matrix3x4 const&>::value, "");
	static_assert(!hamon::is_constructible<matrix4x3, matrix4x4 const&>::value, "");

	{
		HAMON_CONSTEXPR matrix4x3 const m1
		{
			 0,  1,  2,
			 4,  5,  6,
			 8,  9, 10,
			12, 13, 14,
		};

		HAMON_CONSTEXPR matrix4x3i const m2{m1};
		HAMON_CONSTEXPR matrix4x3f const m3{m1};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m2[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m2[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m2[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m2[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m2[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m2[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m2[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m2[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m2[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, m2[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, m2[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, m2[3][2]);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m3[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, m3[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, m3[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, m3[3][2]);
	}
}

template <typename T>
void Matrix4x4CtorConvertTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	using matrix4x4i = hamon::qvm::matrix<int, 4, 4>;
	using matrix4x4f = hamon::qvm::matrix<float, 4, 4>;

	static_assert(hamon::is_constructible<matrix4x4,  matrix4x4i const&>::value, "");
	static_assert(hamon::is_constructible<matrix4x4,  matrix4x4f const&>::value, "");
	static_assert(hamon::is_constructible<matrix4x4i, matrix4x4  const&>::value, "");
	static_assert(hamon::is_constructible<matrix4x4i, matrix4x4f const&>::value, "");
	static_assert(hamon::is_constructible<matrix4x4f, matrix4x4  const&>::value, "");
	static_assert(hamon::is_constructible<matrix4x4f, matrix4x4i const&>::value, "");

	static_assert(hamon::is_nothrow_constructible<matrix4x4,  matrix4x4i const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix4x4,  matrix4x4f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix4x4i, matrix4x4  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix4x4i, matrix4x4f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix4x4f, matrix4x4  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<matrix4x4f, matrix4x4i const&>::value, "");

	static_assert(hamon::is_implicitly_constructible<matrix4x4,  matrix4x4i const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix4x4,  matrix4x4f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix4x4i, matrix4x4  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix4x4i, matrix4x4f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix4x4f, matrix4x4  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<matrix4x4f, matrix4x4i const&>::value, "");

	// 要素数が違ったらコンストラクトできない
	static_assert(!hamon::is_constructible<matrix4x4, matrix3x3 const&>::value, "");
	static_assert(!hamon::is_constructible<matrix4x4, matrix3x4 const&>::value, "");
	static_assert(!hamon::is_constructible<matrix4x4, matrix4x3 const&>::value, "");

	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			 0,  1,  2,  3,
			 4,  5,  6,  7,
			 8,  9, 10, 11,
			12, 13, 14, 15,
		};

		HAMON_CONSTEXPR matrix4x4i const m2{m1};
		HAMON_CONSTEXPR matrix4x4f const m3{m1};

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

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, m3[0][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, m3[1][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, m3[2][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, m3[2][3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, m3[3][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, m3[3][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, m3[3][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, m3[3][3]);
	}
}

TYPED_TEST(MatrixTest, CtorConvertTest)
{
	using T = TypeParam;
	Matrix3x3CtorConvertTest<T>();
	Matrix3x4CtorConvertTest<T>();
	Matrix4x3CtorConvertTest<T>();
	Matrix4x4CtorConvertTest<T>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
