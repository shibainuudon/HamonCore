/**
 *	@file	unit_test_qvm_matrix_compare.cpp
 *
 *	@brief	operator==のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

template <typename T>
void Matrix3x3CompareTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x3i = hamon::qvm::matrix<int, 3, 3>;

	HAMON_CONSTEXPR matrix3x3 const m1
	{
		11, 12, 13,
		21, 22, 23,
		31, 32, 33,
	};
	HAMON_CONSTEXPR matrix3x3i const m2
	{
		11, 12, 13,
		21, 22, 23,
		31, 32, 33,
	};
	HAMON_CONSTEXPR matrix3x3 const m3
	{
		10, 12, 13,
		21, 22, 23,
		31, 32, 33,
	};
	HAMON_CONSTEXPR matrix3x3 const m4
	{
		11, 12, 13,
		21, 23, 23,
		31, 32, 33,
	};
	HAMON_CONSTEXPR matrix3x3i const m5
	{
		11, 12, 13,
		21, 22, 23,
		31, 32,-33,
	};

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 == m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 == m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m5);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m5);
}

template <typename T>
void Matrix3x4CompareTest()
{
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix3x4i = hamon::qvm::matrix<int, 3, 4>;

	HAMON_CONSTEXPR matrix3x4 const m1
	{
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34,
	};
	HAMON_CONSTEXPR matrix3x4 const m2
	{
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34,
	};
	HAMON_CONSTEXPR matrix3x4 const m3
	{
		10, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34,
	};
	HAMON_CONSTEXPR matrix3x4i const m4
	{
		11, 12, 13, 14,
		21, 23, 23, 24,
		31, 32, 33, 34,
	};
	HAMON_CONSTEXPR matrix3x4 const m5
	{
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32,-33, 34,
	};

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 == m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 == m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m5);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m5);
}

template <typename T>
void Matrix4x3CompareTest()
{
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x3i = hamon::qvm::matrix<int, 4, 3>;

	HAMON_CONSTEXPR matrix4x3 const m1
	{
		11, 12, 13,
		21, 22, 23,
		31, 32, 33,
		41, 42, 43,
	};
	HAMON_CONSTEXPR matrix4x3 const m2
	{
		11, 12, 13,
		21, 22, 23,
		31, 32, 33,
		41, 42, 43,
	};
	HAMON_CONSTEXPR matrix4x3i const m3
	{
		10, 12, 13,
		21, 22, 23,
		31, 32, 33,
		41, 42, 43,
	};
	HAMON_CONSTEXPR matrix4x3 const m4
	{
		11, 12, 13,
		21, 23, 23,
		31, 32, 33,
		41, 42, 43,
	};
	HAMON_CONSTEXPR matrix4x3 const m5
	{
		11, 12, 13,
		21, 22, 23,
		31, 32,-33,
		41, 42, 43,
	};
	HAMON_CONSTEXPR matrix4x3 const m6
	{
		11, 12, 13,
		21, 22, 23,
		31, 32, 33,
		41, 40, 43,
	};

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 == m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 == m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m5);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m6);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m6);
}

template <typename T>
void Matrix4x4CompareTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using matrix4x4i = hamon::qvm::matrix<int, 4, 4>;

	HAMON_CONSTEXPR matrix4x4 const m1
	{
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34,
		41, 42, 43, 44,
	};
	HAMON_CONSTEXPR matrix4x4i const m2
	{
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34,
		41, 42, 43, 44,
	};
	HAMON_CONSTEXPR matrix4x4 const m3
	{
		10, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34,
		41, 42, 43, 44,
	};
	HAMON_CONSTEXPR matrix4x4 const m4
	{
		11, 12, 13, 14,
		21, 23, 23, 24,
		31, 32, 33, 34,
		41, 42, 43, 44,
	};
	HAMON_CONSTEXPR matrix4x4 const m5
	{
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32,-33, 34,
		41, 42, 43, 44,
	};
	HAMON_CONSTEXPR matrix4x4 const m6
	{
		11, 12, 13, 14,
		21, 22, 23, 24,
		31, 32, 33, 34,
		41, 42, 43, 45,
	};

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 == m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 == m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m5);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 == m6);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (m1 != m6);
}

TYPED_TEST(MatrixTest, CompareTest)
{
	using T = TypeParam;
	Matrix3x3CompareTest<T>();
	Matrix3x4CompareTest<T>();
	Matrix4x3CompareTest<T>();
	Matrix4x4CompareTest<T>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
