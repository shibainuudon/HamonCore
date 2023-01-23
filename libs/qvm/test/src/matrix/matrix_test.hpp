/**
 *	@file	matrix_test.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_QVM_MATRIX_MATRIX_TEST_HPP
#define UNIT_TEST_QVM_MATRIX_MATRIX_TEST_HPP

#include <hamon/qvm/matrix/matrix.hpp>
#include <gtest/gtest.h>
#include "get_random_value.hpp"

namespace hamon_qvm_test
{

using MatrixTestTypes = ::testing::Types<int, float, double, long double>;
using MatrixTestFloatTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MatrixTest : public ::testing::Test {};
template <typename T>
class MatrixFloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MatrixTest,      MatrixTestTypes);
TYPED_TEST_SUITE(MatrixFloatTest, MatrixTestFloatTypes);

template <typename T, std::size_t N, std::size_t M>
hamon::qvm::matrix<T, N, M> make_random_matrix()
{
	hamon::qvm::matrix<T, N, M> result;
	for (auto& y : result)
	{
		for (auto& x : y)
		{
			x = get_random_value<T>();
		}
	}
	return result;
}

}	// namespace hamon_qvm_test

#endif // UNIT_TEST_QVM_MATRIX_MATRIX_TEST_HPP
