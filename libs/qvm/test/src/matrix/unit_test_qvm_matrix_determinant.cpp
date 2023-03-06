/**
 *	@file	unit_test_qvm_matrix_determinant.cpp
 *
 *	@brief	determinant のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixTest, DeterminantTest)
{
	using T = TypeParam;
	using matrix2x2 = hamon::qvm::matrix<T, 2, 2>;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	// matrix2x2
	{
		HAMON_CONSTEXPR matrix2x2 const m
		{
			1, 0,
			0, 1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), determinant(m));
	}
	{
		HAMON_CONSTEXPR matrix2x2 const m
		{
			3, 1,
			5, 1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2), determinant(m));
	}
	{
		HAMON_CONSTEXPR matrix2x2 const m
		{
			4, 3,
			2, 5,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(14), determinant(m));
	}

	// matrix3x3
	{
		HAMON_CONSTEXPR matrix3x3 const m
		{
			1, 0, 2,
			3, 0, 1,
			2, 1, 1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(5), determinant(m));
	}
	{
		HAMON_CONSTEXPR matrix3x3 const m
		{
			1, 2, 1,
			2, 1, 0,
			1, 1, 2,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-5), determinant(m));
	}
	{
		HAMON_CONSTEXPR matrix3x3 const m
		{
			 9, -3,  2,
			 0,  8, -1,
			-2, -3,  5,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(359), determinant(m));
	}

	// matrix4x4
	{
		HAMON_CONSTEXPR matrix4x4 const m
		{
			3,  1,  1,  2,
			5,  1,  3,  4,
			2,  0,  1,  0,
			1,  3,  2,  1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-22), determinant(m));
	}
	{
		HAMON_CONSTEXPR matrix4x4 const m
		{
			 1, -2,  3,  2,
			-2,  2,  0,  2,
			 2,  4, -1, -2,
			 3,  5, -7, -6,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-102), determinant(m));
	}
	{
		HAMON_CONSTEXPR matrix4x4 const m
		{
			 2,  0,  0,  0,
			 1,  2,  1, -2,
			-3, -1,  1,  2,
			 1,  0,  0, -1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-6), determinant(m));
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
