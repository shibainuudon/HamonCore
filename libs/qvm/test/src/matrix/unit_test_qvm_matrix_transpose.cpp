/**
 *	@file	unit_test_qvm_matrix_transpose.cpp
 *
 *	@brief	transpose のテスト
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
void Matrix3x3TransposeTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;

	HAMON_CONSTEXPR matrix3x3 const m1
	{
		11, 12, 13,
		21, 22, 23,
		31, 32, 33,
	};

	HAMON_CONSTEXPR matrix3x3 const expected
	{
		11, 21, 31,
		12, 22, 32,
		13, 23, 33,
	};

	HAMON_CONSTEXPR auto const m2 = transpose(m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m2);

	HAMON_CONSTEXPR auto const m3 = transpose(m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m1, m3);
}

template <typename T>
void Matrix3x4TransposeTest()
{
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;

	HAMON_CONSTEXPR matrix3x4 const m1
	{
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34,
	};

	HAMON_CONSTEXPR matrix4x3 const expected
	{
		11, 21, 31,
		12, 22, 32,
		13, 23, 33,
		14, 24, 34,
	};

	HAMON_CONSTEXPR auto const m2 = transpose(m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m2);

	HAMON_CONSTEXPR auto const m3 = transpose(m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m1, m3);
}

template <typename T>
void Matrix4x3TransposeTest()
{
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;

	HAMON_CONSTEXPR matrix4x3 const m1
	{
		11, 12, 13,
		21, 22, 23,
		31, 32, 33,
		41, 42, 43,
	};

	HAMON_CONSTEXPR matrix3x4 const expected
	{
		11, 21, 31, 41,
		12, 22, 32, 42,
		13, 23, 33, 43,
	};

	HAMON_CONSTEXPR auto const m2 = transpose(m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m2);

	HAMON_CONSTEXPR auto const m3 = transpose(m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m1, m3);
}

template <typename T>
void Matrix4x4TransposeTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	HAMON_CONSTEXPR matrix4x4 const m1
	{
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34,
		41, 42, 43, 44,
	};

	HAMON_CONSTEXPR matrix4x4 const expected
	{
		11, 21, 31, 41,
		12, 22, 32, 42,
		13, 23, 33, 43,
		14, 24, 34, 44,
	};

	HAMON_CONSTEXPR auto const m2 = transpose(m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m2);

	HAMON_CONSTEXPR auto const m3 = transpose(m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m1, m3);
}

TYPED_TEST(MatrixTest, TransposeTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	static_assert(hamon::is_same<decltype(transpose(matrix3x3{})), matrix3x3>::value, "");
	static_assert(hamon::is_same<decltype(transpose(matrix3x4{})), matrix4x3>::value, "");
	static_assert(hamon::is_same<decltype(transpose(matrix4x3{})), matrix3x4>::value, "");
	static_assert(hamon::is_same<decltype(transpose(matrix4x4{})), matrix4x4>::value, "");

	Matrix3x3TransposeTest<T>();
	Matrix3x4TransposeTest<T>();
	Matrix4x3TransposeTest<T>();
	Matrix4x4TransposeTest<T>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
