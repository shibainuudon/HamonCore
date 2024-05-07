/**
 *	@file	unit_test_vector_incomplete_type.cpp
 *
 *	@brief	不完全型のテスト
 */

#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace incomplete_type_test
{

struct S
{
	hamon::vector<S> vec;
};

HAMON_CXX20_CONSTEXPR bool test()
{
	S s;
	s.vec.push_back(S{});
	return true;
}

GTEST_TEST(VectorTest, IncompleteTypeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace incomplete_type_test

}	// namespace hamon_vector_test
