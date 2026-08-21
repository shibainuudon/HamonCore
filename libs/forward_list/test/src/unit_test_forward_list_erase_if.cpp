/**
 *	@file	unit_test_forward_list_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	template<class T, class Allocator, class Predicate>
 *	typename forward_list<T, Allocator>::size_type
 *	erase_if(forward_list<T, Allocator>& c, Predicate pred);
 */

#include <hamon/forward_list/erase_if.hpp>
#include <hamon/forward_list/forward_list.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool
test()
{
	{
		hamon::forward_list<int> v = {3,1,4,5,2};
		auto r = hamon::erase_if(v, [](int x) { return x % 2 == 0; });
		VERIFY(r == 2);
		const int v2[] = {3,1,5,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		hamon::forward_list<int> v = {3,1,4,1,5,9,2,6,5,3,5,};
		auto r = hamon::erase_if(v, [](int x) { return x >= 5; });
		VERIFY(r == 5);
		const int v2[] = {3,1,4,1,2,3,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, EraseIfTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace erase_if_test

}	// namespace hamon_forward_list_test
