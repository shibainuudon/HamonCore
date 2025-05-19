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

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

struct S
{
	hamon::forward_list<S> cont;
};

FORWARD_LIST_TEST_CONSTEXPR bool test()
{
	S s;
	s.cont.push_front(S{});
	return true;
}

GTEST_TEST(ForwardListTest, IncompleteTypeTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace incomplete_type_test

}	// namespace hamon_forward_list_test
