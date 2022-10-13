/**
 *	@file	matrix_test.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_QVM_MATRIX_TEST_HPP
#define UNIT_TEST_QVM_MATRIX_TEST_HPP

#include <gtest/gtest.h>

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

}	// namespace hamon_qvm_test

#endif // UNIT_TEST_QVM_MATRIX_TEST_HPP
