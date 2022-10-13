/**
 *	@file	quaternion_test.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_QVM_QUATERNION_TEST_HPP
#define UNIT_TEST_QVM_QUATERNION_TEST_HPP

#include <gtest/gtest.h>

namespace hamon_qvm_test
{

using QuaternionTestTypes = ::testing::Types<int, float, double, long double>;
using QuaternionTestFloatTypes = ::testing::Types<float, double, long double>;

template <typename T>
class QuaternionTest : public ::testing::Test {};
template <typename T>
class QuaternionFloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(QuaternionTest,      QuaternionTestTypes);
TYPED_TEST_SUITE(QuaternionFloatTest, QuaternionTestFloatTypes);

}	// namespace hamon_qvm_test

#endif // UNIT_TEST_QVM_QUATERNION_TEST_HPP
