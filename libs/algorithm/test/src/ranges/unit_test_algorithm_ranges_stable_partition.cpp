/**
 *	@file	unit_test_algorithm_ranges_stable_partition.cpp
 *
 *	@brief	ranges::stable_partition のテスト
 */

#include <hamon/algorithm/ranges/stable_partition.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_stable_partition_test
{

HAMON_CONSTEXPR bool is_even(int x)
{
	return (x % 2) == 0;
}

GTEST_TEST(AlgorithmTest, RangesStablePartitionTest)
{
	namespace ranges = hamon::ranges;
	{
		int x[] = {1,2,3,4,5};
		test_bidirectional_range<int> rx(x);
		auto ret = ranges::stable_partition(rx, is_even);
		EXPECT_TRUE(ret.begin() == ranges::next(rx.begin(), 2));
		EXPECT_TRUE(ret.end()   == rx.end());
		int const y[] = {2,4,1,3,5};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		hamon::vector<int> x = {1,2,3,4,5};
		auto ret = ranges::stable_partition(x, is_even);
		EXPECT_TRUE(ret.begin() == ranges::next(x.begin(), 2));
		EXPECT_TRUE(ret.end()   == x.end());
		int const y[] = {2,4,1,3,5};
		EXPECT_TRUE(ranges::equal(x, y));
	}
	{
		hamon::list<int> x = {3,1,4,1,5,9,2,6,5};
		auto ret = ranges::stable_partition(x, [](int a) { return a > 3;});
		EXPECT_TRUE(ret.begin() == ranges::next(x.begin(), 5));
		EXPECT_TRUE(ret.end()   == x.end());
		int const y[] = {4,5,9,6,5,3,1,1,2};
		EXPECT_TRUE(ranges::equal(x, y));
	}
}

}	// namespace ranges_stable_partition_test

}	// namespace hamon_algorithm_test
