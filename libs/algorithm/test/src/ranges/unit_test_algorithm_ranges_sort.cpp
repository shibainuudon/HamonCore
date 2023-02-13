/**
 *	@file	unit_test_algorithm_ranges_sort.cpp
 *
 *	@brief	ranges::sort のテスト
 */

#include <hamon/algorithm/ranges/sort.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_sort_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 3,1,4,1,5,9,2,6 };
		auto res = ranges::sort(x, x+6);
		VERIFY(res == x+6);
		int const y[] = { 1,1,3,4,5,9,2,6 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 3,1,4,1,5,9,2,6 };
		auto res = ranges::sort(x, ranges::greater{});
		VERIFY(res == x+8);
		int const y[] = { 9,6,5,4,3,2,1,1 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,9,7,2,3,6,4,8,5 };
		test_random_access_range<int> r(x);
		auto res = ranges::sort(r);
		VERIFY(res == r.end());
		int const y[] = { 1,2,3,4,5,6,7,8,9 };
		VERIFY(ranges::equal(x, y));
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
		X x[] = { {3},{4},{2},{1},{5} };
		auto res = ranges::sort(x, x+4, ranges::greater{}, &X::i);
		VERIFY(res == x+4);
		X const y[] = { {4},{3},{2},{1},{5} };
		VERIFY(ranges::equal(x, y, {}, &X::i, &X::i));
	}
	{
		X x[] = { {3},{4},{2},{1},{5} };
		auto res = ranges::sort(x, ranges::greater{}, &X::i);
		VERIFY(res == x+5);
		X const y[] = { {5},{4},{3},{2},{1} };
		VERIFY(ranges::equal(x, y, {}, &X::i, &X::i));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesSortTest)
{
	EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_sort_test

}	// namespace hamon_algorithm_test
