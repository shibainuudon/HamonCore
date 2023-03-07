/**
 *	@file	unit_test_qvm_matrix_data.cpp
 *
 *	@brief	dataのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

template <typename T, hamon::size_t N, hamon::size_t M>
void DataTest()
{
	using matrix = hamon::qvm::matrix<T, N, M>;

	{
		matrix const m;
		auto p = m.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(p == &m[0][0]);
		static_assert(hamon::is_same<decltype(p), T const*>::value, "");
	}
	{
		matrix m;
		auto p = m.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(p == &m[0][0]);
		static_assert(hamon::is_same<decltype(p), T*>::value, "");
	}
}

TYPED_TEST(MatrixTest, DataTest)
{
	using T = TypeParam;

	DataTest<T, 1, 1>();
	DataTest<T, 1, 2>();
	DataTest<T, 1, 3>();
	DataTest<T, 1, 4>();
	DataTest<T, 2, 1>();
	DataTest<T, 2, 2>();
	DataTest<T, 2, 3>();
	DataTest<T, 2, 4>();
	DataTest<T, 3, 1>();
	DataTest<T, 3, 2>();
	DataTest<T, 3, 3>();
	DataTest<T, 3, 4>();
	DataTest<T, 4, 1>();
	DataTest<T, 4, 2>();
	DataTest<T, 4, 3>();
	DataTest<T, 4, 4>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
