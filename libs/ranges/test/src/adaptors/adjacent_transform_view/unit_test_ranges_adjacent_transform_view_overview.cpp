/**
 *	@file	unit_test_ranges_adjacent_transform_view_overview.cpp
 *
 *	@brief	adjacent_transform_view のテスト
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/functional/ranges/multiplies.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, AdjacentTransformViewOverviewTest)
{
	{
		// [range.adjacent.transform.overview]/3
		// Example 1:
		hamon::vector<int> v = {1, 2, 3, 4};
		std::stringstream out;
		for (auto i : v | hamon::views::adjacent_transform<2>(hamon::ranges::multiplies()))
		{
			out << i << ' ';     // prints 2 6 12
		}
		EXPECT_EQ("2 6 12 ", out.str());
	}
}

}	// namespace overview_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
