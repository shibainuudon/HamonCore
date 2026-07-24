/**
 *	@file	unit_test_ranges_cache_latest_view_overview.cpp
 *
 *	@brief	cache_latest_view のテスト
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/ranges/adaptors/transform_view.hpp>
#include <hamon/ranges/adaptors/filter_view.hpp>
#include <hamon/algorithm/ranges/for_each.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, CacheLatestViewOverviewTest)
{
	// https://en.cppreference.com/cpp/ranges/cache_latest_view
	{
		hamon::vector<int> v = {1, 2, 3, 4, 5};

		std::stringstream ss;

		auto square = [&](int i)
		{
			ss << "transform: " << i << " ";
			return i * i;
		};

		auto is_even = [&](int i)
		{
			ss << "filter: " << i << " ";
			return i % 2 == 0;
		};

		auto print = [&](auto r)
		{
			hamon::ranges::for_each(r,
				[&](int i)
				{
					ss << "Got: " << i << "\n";
				}
			);
		};

		ss << "Without caching latest (note recalculations):\n";
		auto even_squares = v
			| hamon::views::transform(square)
			| hamon::views::filter(is_even);
		print(even_squares);

		EXPECT_EQ(
			"Without caching latest (note recalculations):\n"
			"transform: 1 filter: 1 transform: 2 filter: 4 transform: 2 Got: 4\n"
			"transform: 3 filter: 9 transform: 4 filter: 16 transform: 4 Got: 16\n"
			"transform: 5 filter: 25 ", ss.str());

		ss.str("");
		ss << "With caching latest:\n";
		auto fast_even_squares = v
			| hamon::views::transform(square)
			| hamon::views::cache_latest
			| hamon::views::filter(is_even);
		print(fast_even_squares);

		EXPECT_EQ(
			"With caching latest:\n"
			"transform: 1 filter: 1 transform: 2 filter: 4 Got: 4\n"
			"transform: 3 filter: 9 transform: 4 filter: 16 Got: 16\n"
			"transform: 5 filter: 25 ", ss.str());
	}
}

}	// namespace overview_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
