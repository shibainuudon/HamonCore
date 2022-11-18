/**
 *	@file	quaternion_test.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_QVM_QUATERNION_TEST_HPP
#define UNIT_TEST_QVM_QUATERNION_TEST_HPP

#include <hamon/qvm/quaternion.hpp>
#include <gtest/gtest.h>
#include "get_random_value.hpp"

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

template <typename T>
hamon::qvm::quaternion<T> make_random_quaternion()
{
	hamon::qvm::quaternion<T> result;
	for (auto& x : result)
	{
		x = get_random_value<T>();
	}
	return result;
}

}	// namespace hamon_qvm_test

#endif // UNIT_TEST_QVM_QUATERNION_TEST_HPP
