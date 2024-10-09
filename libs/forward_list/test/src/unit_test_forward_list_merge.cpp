/**
 *	@file	unit_test_forward_list_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	void merge(forward_list& x);
 *	void merge(forward_list&& x);
 *	template<class Compare> void merge(forward_list& x, Compare comp);
 *	template<class Compare> void merge(forward_list&& x, Compare comp);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace merge_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, MergeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace merge_test

}	// namespace hamon_forward_list_test
