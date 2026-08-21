/**
 *	@file	unit_test_forward_list_incomplete_type.cpp
 *
 *	@brief	不完全型のテスト
 */

#include <hamon/forward_list/forward_list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace incomplete_type_test
{

struct S
{
	hamon::forward_list<S> cont;
};

HAMON_CXX20_CONSTEXPR bool test()
{
	S s;
	s.cont.push_front(S{});
	return true;
}

GTEST_TEST(ForwardListTest, IncompleteTypeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace incomplete_type_test

}	// namespace hamon_forward_list_test
