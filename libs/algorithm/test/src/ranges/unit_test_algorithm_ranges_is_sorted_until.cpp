/**
 *	@file	unit_test_algorithm_ranges_is_sorted_until.cpp
 *
 *	@brief	ranges::is_sorted_until のテスト
 */

#include <hamon/algorithm/ranges/is_sorted_until.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/forward_list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_is_sorted_until_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int a[] = {1,2,3,4,5};
		auto it = ranges::is_sorted_until(a);
		VERIFY(it == a+5);
	}
	{
		int a[] = {1,2,3,4,5};
		auto it = ranges::is_sorted_until(a, ranges::greater{});
		VERIFY(it == a+1);
	}
	{
		int a[] = {1,2,5,3,4};
		auto it = ranges::is_sorted_until(a);
		VERIFY(it == a+3);
	}
	{
		int a[] = {9,9,8,8,8,5,3,1,2};
		auto it = ranges::is_sorted_until(a, ranges::greater{});
		VERIFY(it == a+8);
	}
	{
		int a[] = {1,2,2,3,3,3,4,1};
		test_forward_range<int> r(a);
		auto it = ranges::is_sorted_until(r);
		VERIFY(it == ranges::next(r.begin(), 7));
	}
	return true;
}

struct X
{
	int i;
};

inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		X a[] = { {1},{2},{3},{0},{4},{5} };
		auto it = ranges::is_sorted_until(a, {}, &X::i);
		VERIFY(it == a+3);
	}
	{
		hamon::forward_list<int> const a = {3,3,4,4,5,5};
		auto it = ranges::is_sorted_until(a, [] (int x, int y) { return x < y; });
		EXPECT_TRUE(it == a.end());
	}
	{
		hamon::forward_list<int> const a = {3,3,4,4,5,5};
		auto it = ranges::is_sorted_until(a, [] (int x, int y) { return x > y; });
		EXPECT_TRUE(it == ranges::next(a.begin(), 2));
	}
	{
		hamon::forward_list<int> const a = {};
		auto it = ranges::is_sorted_until(a);
		EXPECT_TRUE(it == a.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesIsSortedUntilTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_is_sorted_until_test

}	// namespace hamon_algorithm_test
