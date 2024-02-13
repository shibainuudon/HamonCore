/**
 *	@file	unit_test_ranges_enumerate_view_overview.cpp
 *
 *	@brief	enumerate_view のテスト
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, EnumerateViewOverviewTest)
{
#if defined(HAMON_HAS_CXX17_STRUCTURED_BINDINGS)
	{
		// [range.enumerate.overview]/2
		// Example 1:
		std::vector<int> vec {1, 2, 3};
		std::stringstream out;
		for (auto [index, value] : hamon::views::enumerate(vec))
		{
			out << index << ":" << value << ' ';         // prints 0:1 1:2 2:3
		}
		EXPECT_EQ("0:1 1:2 2:3 ", out.str());
	}
#endif
	{
		std::vector<int> vec {10, 20, 30};
		std::stringstream out;
		for (auto t : hamon::views::enumerate(vec))
		{
			auto index = hamon::adl_get<0>(t);
			auto value = hamon::adl_get<1>(t);
			out << index << ":" << value << ' ';
		}
		EXPECT_EQ("0:10 1:20 2:30 ", out.str());
	}
}

}	// namespace overview_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
