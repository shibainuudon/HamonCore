/**
 *	@file	unit_test_ranges_split_view_overview.cpp
 *
 *	@brief	split_view のテスト
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, SplitViewOverviewTest)
{
	{
		// [range.split.overview]/3
		// Example 1:
		std::stringstream out;
		hamon::string str {"the quick brown fox"};
		for (auto word : hamon::views::split(str, ' '))
		{
			out << hamon::string_view(word) << '*';
		}
		EXPECT_EQ("the*quick*brown*fox*", out.str());
	}
	{
		hamon::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		hamon::vector<int> pattern = {};
		std::stringstream out;
		for (auto inner_range : v | hamon::views::split(pattern))
		{
			for (int n : inner_range)
			{
				out << n;
			}
			out << '\n';
		}
		EXPECT_EQ("1\n2\n3\n4\n5\n6\n7\n8\n9\n", out.str());
	}
}

}	// namespace overview_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
