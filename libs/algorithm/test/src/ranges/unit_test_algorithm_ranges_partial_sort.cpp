/**
 *	@file	unit_test_algorithm_ranges_partial_sort.cpp
 *
 *	@brief	ranges::partial_sort のテスト
 */

#include <hamon/algorithm/ranges/partial_sort.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_partial_sort_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		auto it = ranges::partial_sort(x, x, x+11);
		VERIFY(it == x+11);
		int const y[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		test_random_access_range<int> rx(x);
		auto it = ranges::partial_sort(rx.begin(), ranges::next(rx.begin(), 1), rx.end());
		VERIFY(it == rx.end());
		int const y[] = { 1 };
		VERIFY(ranges::equal(x, x+1, y, y+1));
	}
	{
		int x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		test_random_access_range<int> rx(x);
		auto it = ranges::partial_sort(rx, ranges::next(rx.begin(), 5));
		VERIFY(it == rx.end());
		int const y[] = { 1, 1, 2, 3, 3 };
		VERIFY(ranges::equal(x, x+5, y, y+5));
	}
	{
		int x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		test_random_access_range<int> rx(x);
		auto it = ranges::partial_sort(rx, ranges::next(rx.begin(), 7), ranges::greater{});
		VERIFY(it == rx.end());
		int const y[] = { 9, 6, 5, 5, 5, 4, 3 };
		VERIFY(ranges::equal(x, x+7, y, y+7));
	}
	{
		int x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		test_random_access_range<int> rx(x);
		auto it = ranges::partial_sort(rx, ranges::next(rx.begin(), 11));
		VERIFY(it == rx.end());
		int const y[] = { 1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9 };
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
		X x[] = { {5},{1},{3},{2},{4} };
		auto it = ranges::partial_sort(x, x+3, {}, &X::i);
		VERIFY(it == x+5);
		X y[] = { {1},{2},{3} };
		VERIFY(ranges::equal(x, x+3, y, y+3, {}, &X::i, &X::i));
	}
	{
		X x[] = { {5},{1},{3},{2},{4} };
		auto it = ranges::partial_sort(x, x+4, ranges::greater{}, &X::i);
		VERIFY(it == x+5);
		X y[] = { {5},{4},{3},{2} };
		VERIFY(ranges::equal(x, x+4, y, y+4, {}, &X::i, &X::i));
	}
	{
		hamon::vector<int> x = {};
		auto it = ranges::partial_sort(x, x.begin());
		VERIFY(it == x.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPartialSortTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_partial_sort_test

}	// namespace hamon_algorithm_test
