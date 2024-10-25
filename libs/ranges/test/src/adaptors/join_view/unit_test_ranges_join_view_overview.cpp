/**
 *	@file	unit_test_ranges_join_view_overview.cpp
 *
 *	@brief	join_view のテスト
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, JoinViewOverviewTest)
{
	// [range.join.overview]/3
	// Example 1:
	{
		std::stringstream out;
		hamon::vector<std::string> ss {"hello", " ", "world", "!"};
		for (char ch : ss | hamon::views::join)
		{
			out << ch;                                   // prints hello world!
		}
		EXPECT_EQ("hello world!", out.str());
	}
}

}	// namespace overview_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
