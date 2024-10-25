/**
 *	@file	unit_test_ranges_lazy_split_view_overview.cpp
 *
 *	@brief	lazy_split_view のテスト
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/factories/istream_view.hpp>
#include <hamon/list.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, LazySplitViewOverviewTest)
{
#if defined(HAMON_HAS_CXX17_RANGE_BASED_FOR)
	{
		// [range.lazy.split.overview]/3
		// Example 1:
		std::stringstream out;
		std::string str {"the quick brown fox"};
		for (auto word : str | hamon::views::lazy_split(' '))
		{
			for (char ch : word)
			{
				out << ch;
			}
			out << '*';
		}
		EXPECT_EQ("the*quick*brown*fox*", out.str());
	}
	{
		std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::vector<int> pattern = {4, 5};
		std::stringstream out;
		for (auto inner_range : v | hamon::views::lazy_split(pattern))
		{
			for (int n : inner_range)
			{
				out << n;
			}
			out << '\n';
		}
		EXPECT_EQ("123\n6789\n", out.str());
	}
	{
		std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::vector<int> pattern = {};
		std::stringstream out;
		for (auto inner_range : v | hamon::views::lazy_split(pattern))
		{
			for (int n : inner_range)
			{
				out << n;
			}
			out << '\n';
		}
		EXPECT_EQ("1\n2\n3\n4\n5\n6\n7\n8\n9\n", out.str());
	}
	{
		std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::vector<int> pattern = {8, 9};
		std::stringstream out;
		for (auto inner_range : v | hamon::views::lazy_split(pattern))
		{
			for (int n : inner_range)
			{
				out << n;
			}
			out << '\n';
		}
		EXPECT_EQ("1234567\n\n", out.str());
	}
	{
		std::vector<int> v = {1, 2, 4, 4, 1, 1, 1, 10, 23, 67, 9, 1, 1, 1, 1111, 1, 1, 1, 1, 1, 1, 9, 0};
		hamon::list<int> delimiter = {1, 1, 1};
		std::stringstream out;
		for (auto inner_range : v | hamon::views::lazy_split(delimiter))
		{
			for (int n : inner_range)
			{
				out << n;
			}
			out << '\n';
		}
		EXPECT_EQ("1244\n1023679\n1111\n\n90\n", out.str());
	}
	{
		auto iss = std::istringstream {"1 2 3 1 4 5 6 1 7 8 1 9 1"};
		std::stringstream out;
		for (auto inner_range : hamon::views::istream<int>(iss) | hamon::views::lazy_split(1))
		{
			for (int n : inner_range)
			{
				out << n;
			}
			out << '\n';
		}
		EXPECT_EQ("\n23\n456\n78\n9\n\n", out.str());
	}
	{
		const auto str = hamon::string_view("1, 12434, 5, 0000, 3942");
		std::stringstream out;
		for (auto inner_range : str | hamon::views::lazy_split(hamon::string_view(", ", 2)))
		{
			for (char c : inner_range)
			{
				out << c;
			}
			out << '\n';
		}
		EXPECT_EQ("1\n12434\n5\n0000\n3942\n", out.str());
	}
#endif
}

}	// namespace overview_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
