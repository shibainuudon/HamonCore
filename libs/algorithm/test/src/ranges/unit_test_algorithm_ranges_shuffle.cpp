/**
 *	@file	unit_test_algorithm_ranges_shuffle.cpp
 *
 *	@brief	ranges::shuffle のテスト
 */

#include <hamon/algorithm/ranges/shuffle.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/algorithm/ranges/is_sorted.hpp>
#include <hamon/algorithm/ranges/is_permutation.hpp>
#include <hamon/random/engines/xorshift.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_shuffle_test
{

GTEST_TEST(AlgorithmTest, RangesShuffleTest)
{
	namespace ranges = hamon::ranges;
	{
		int x[] = {0,1,2,3,4,5,6,7,8,9};
		int y[] = {0,1,2,3,4,5,6,7,8,9};
		EXPECT_TRUE (ranges::is_sorted(x));
		auto g = hamon::xorshift32();
		test_random_access_range<int> rx(x);
		auto res = ranges::shuffle(rx, g);
		EXPECT_TRUE (res == rx.end());
		EXPECT_FALSE(ranges::is_sorted(x));
		EXPECT_FALSE(ranges::equal(x, y));
		EXPECT_TRUE (ranges::is_permutation(x, y));
	}
}

}	// namespace ranges_shuffle_test

}	// namespace hamon_algorithm_test
