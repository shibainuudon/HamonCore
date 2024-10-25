/**
 *	@file	unit_test_ranges_adjacent_view_overview.cpp
 *
 *	@brief	adjacent_view のテスト
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/tuple.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, AdjacentViewOverviewTest)
{
	{
		// [range.adjacent.overview]/2.2
		// Example 1:
		hamon::vector<int> v = { 1, 2, 3, 4 };
		std::stringstream out;
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
		for (auto i : v | hamon::views::adjacent<2>)
#else
		for (auto i : v | hamon::views::adjacent_t<2>{})
#endif
		{
			out << "(" << hamon::adl_get<0>(i) << ", " << hamon::adl_get<1>(i) << ") ";  // prints (1, 2) (2, 3) (3, 4)
		}
		EXPECT_EQ("(1, 2) (2, 3) (3, 4) ", out.str());
	}
}

}	// namespace overview_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
