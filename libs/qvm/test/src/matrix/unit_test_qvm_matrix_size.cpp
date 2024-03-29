﻿/**
 *	@file	unit_test_qvm_matrix_size.cpp
 *
 *	@brief	sizeのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/cstddef/size_t.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

template <typename T, hamon::size_t N, hamon::size_t M>
void SizeTest()
{
	using matrix_type = hamon::qvm::matrix<T, N, M>;

	{
		HAMON_CONSTEXPR matrix_type const m{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(N, m.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(M, m[0].size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(M, m[N-1].size());
	}
	{
		matrix_type const m = make_random_matrix<T, N, M>();
		EXPECT_EQ(N, m.size());
		EXPECT_EQ(M, m[0].size());
		EXPECT_EQ(M, m[N-1].size());
	}
}

TYPED_TEST(MatrixTest, SizeTest)
{
	using T = TypeParam;
	SizeTest<T, 1, 1>();
	SizeTest<T, 1, 2>();
	SizeTest<T, 1, 3>();
	SizeTest<T, 1, 4>();
	SizeTest<T, 2, 1>();
	SizeTest<T, 2, 2>();
	SizeTest<T, 2, 3>();
	SizeTest<T, 2, 4>();
	SizeTest<T, 3, 1>();
	SizeTest<T, 3, 2>();
	SizeTest<T, 3, 3>();
	SizeTest<T, 3, 4>();
	SizeTest<T, 4, 1>();
	SizeTest<T, 4, 2>();
	SizeTest<T, 4, 3>();
	SizeTest<T, 4, 4>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
