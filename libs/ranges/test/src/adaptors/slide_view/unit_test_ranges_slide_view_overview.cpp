/**
 *	@file	unit_test_ranges_slide_view_overview.cpp
 *
 *	@brief	slide_view のテスト
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_ranges_test
{
namespace slide_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, SlideViewOverviewTest)
{
	// [range.slide.overview]/2
	// Example 1:
	hamon::vector<int> v = { 1, 2, 3, 4 };
	std::stringstream out;
	for (auto i : v | hamon::views::slide(2))
	{
		out << '[' << i[0] << ", " << i[1] << "] ";          // prints [1, 2] [2, 3] [3, 4]
	}
	EXPECT_EQ("[1, 2] [2, 3] [3, 4] ", out.str());
}

}	// namespace overview_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
