/**
 *	@file	unit_test_qvm_matrix_max_size.cpp
 *
 *	@brief	max_sizeのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

template <typename T, std::size_t N, std::size_t M>
void MaxSizeTest()
{
	using matrix_type = hamon::qvm::matrix<T, N, M>;

	{
		HAMON_CONSTEXPR matrix_type const m{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(N, m.max_size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(M, m[0].max_size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(M, m[N-1].max_size());
	}
	{
		matrix_type const m = make_random_matrix<T, N, M>();
		EXPECT_EQ(N, m.max_size());
		EXPECT_EQ(M, m[0].max_size());
		EXPECT_EQ(M, m[N-1].max_size());
	}
}

TYPED_TEST(MatrixTest, MaxSizeTest)
{
	using T = TypeParam;
	MaxSizeTest<T, 1, 1>();
	MaxSizeTest<T, 1, 2>();
	MaxSizeTest<T, 1, 3>();
	MaxSizeTest<T, 1, 4>();
	MaxSizeTest<T, 2, 1>();
	MaxSizeTest<T, 2, 2>();
	MaxSizeTest<T, 2, 3>();
	MaxSizeTest<T, 2, 4>();
	MaxSizeTest<T, 3, 1>();
	MaxSizeTest<T, 3, 2>();
	MaxSizeTest<T, 3, 3>();
	MaxSizeTest<T, 3, 4>();
	MaxSizeTest<T, 4, 1>();
	MaxSizeTest<T, 4, 2>();
	MaxSizeTest<T, 4, 3>();
	MaxSizeTest<T, 4, 4>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
