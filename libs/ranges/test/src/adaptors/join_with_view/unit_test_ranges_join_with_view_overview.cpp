/**
 *	@file	unit_test_ranges_join_with_view_overview.cpp
 *
 *	@brief	join_with_view のテスト
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, JoinWithViewOverviewTest)
{
	// [range.join.with.overview]/3
	// Example 1:
	std::stringstream out;
	hamon::vector<std::string> vs = {"the", "quick", "brown", "fox"};
	for (char c : vs | hamon::views::join_with('-'))
	{
		out << c;
	}
	EXPECT_EQ("the-quick-brown-fox", out.str());
}

}	// namespace overview_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
