/**
 *	@file	unit_test_algorithm_ranges_inplace_merge.cpp
 *
 *	@brief	ranges::inplace_merge のテスト
 */

#include <hamon/algorithm/ranges/inplace_merge.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/functional/negate.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_inplace_merge_test
{

struct X
{
	int i;
	X(int x) : i(x) {}
};

GTEST_TEST(AlgorithmTest, RangesInplaceMergeTest)
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,4,5,  2,3,6 };
		test_bidirectional_range<int> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 3));
		EXPECT_TRUE(ret == rx.end());
		int const y[] = {1,2,3,4,5,6};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		int x[] = { 7,5,2,1,  6,5,3,3,2,2 };
		test_bidirectional_range<int> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 4), ranges::greater{});
		EXPECT_TRUE(ret == rx.end());
		int const y[] = {7,6,5,5,3,3,2,2,2,1};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,4,5,6,  3 };
		test_bidirectional_range<int> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 5), ranges::greater{}, hamon::negate<>{});
		EXPECT_TRUE(ret == rx.end());
		int const y[] = {1,2,3,4,5,6};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		X x[] = { {1},{2},{6},  {1},{3},{5} };
		test_bidirectional_range<X> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 3), {}, &X::i);
		EXPECT_TRUE(ret == rx.end());
		int const y[] = {1,1,2,3,5,6};
		EXPECT_TRUE(ranges::equal(x, y, {}, &X::i));
	}
}

}	// namespace ranges_inplace_merge_test

}	// namespace hamon_algorithm_test
