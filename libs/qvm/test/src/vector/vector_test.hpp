/**
 *	@file	vector_test.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_QVM_VECTOR_VECTOR_TEST_HPP
#define UNIT_TEST_QVM_VECTOR_VECTOR_TEST_HPP

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <gtest/gtest.h>
#include "get_random_value.hpp"

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


template <typename T, hamon::size_t N>
hamon::qvm::vector<T, N> make_random_vector()
{
	hamon::qvm::vector<T, N> result;
	for (auto& x : result)
	{
		x = get_random_value<T>();
	}
	return result;
}

}	// namespace hamon_qvm_test

#endif // UNIT_TEST_QVM_VECTOR_VECTOR_TEST_HPP
