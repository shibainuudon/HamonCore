﻿/**
 *	@file	unit_test_qvm_matrix_empty.cpp
 *
 *	@brief	emptyのテスト
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
void EmptyTest()
{
	using matrix_type = hamon::qvm::matrix<T, N, M>;

	{
		HAMON_CONSTEXPR matrix_type const m{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!m.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!m[0].empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!m[N-1].empty());
	}
	{
		matrix_type const m = make_random_matrix<T, N, M>();
		EXPECT_TRUE(!m.empty());
		EXPECT_TRUE(!m[0].empty());
		EXPECT_TRUE(!m[N-1].empty());
	}
}

TYPED_TEST(MatrixTest, EmptyTest)
{
	using T = TypeParam;
	EmptyTest<T, 1, 1>();
	EmptyTest<T, 1, 2>();
	EmptyTest<T, 1, 3>();
	EmptyTest<T, 1, 4>();
	EmptyTest<T, 2, 1>();
	EmptyTest<T, 2, 2>();
	EmptyTest<T, 2, 3>();
	EmptyTest<T, 2, 4>();
	EmptyTest<T, 3, 1>();
	EmptyTest<T, 3, 2>();
	EmptyTest<T, 3, 3>();
	EmptyTest<T, 3, 4>();
	EmptyTest<T, 4, 1>();
	EmptyTest<T, 4, 2>();
	EmptyTest<T, 4, 3>();
	EmptyTest<T, 4, 4>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
