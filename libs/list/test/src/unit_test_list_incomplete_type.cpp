/**
 *	@file	unit_test_list_incomplete_type.cpp
 *
 *	@brief	不完全型のテスト
 */

#include <hamon/list/list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace incomplete_type_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

struct S
{
	hamon::list<S> cont;
};

LIST_TEST_CONSTEXPR bool test()
{
	S s;
	s.cont.push_back(S{});
	return true;
}

GTEST_TEST(ListTest, IncompleteTypeTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace incomplete_type_test

}	// namespace hamon_list_test
