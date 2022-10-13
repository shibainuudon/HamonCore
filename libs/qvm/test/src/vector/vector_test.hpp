/**
 *	@file	vector_test.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_QVM_VECTOR_TEST_HPP
#define UNIT_TEST_QVM_VECTOR_TEST_HPP

#include <gtest/gtest.h>

namespace hamon_qvm_test
{

using VectorTestTypes = ::testing::Types<int, float, double, long double>;
using VectorTestFloatTypes = ::testing::Types<float, double, long double>;

template <typename T>
class VectorTest : public ::testing::Test {};
template <typename T>
class VectorFloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(VectorTest,      VectorTestTypes);
TYPED_TEST_SUITE(VectorFloatTest, VectorTestFloatTypes);

}	// namespace hamon_qvm_test

#endif // UNIT_TEST_QVM_VECTOR_TEST_HPP
