/**
 *	@file	unit_test_ranges_stride_view_overview.cpp
 *
 *	@brief	stride_view のテスト
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/adaptors/reverse_view.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <iterator>

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, StrideViewOverviewTest)
{
#if 0	// TODO
	// [range.stride.overview]/3
	// Example 1:
	auto input = hamon::views::iota(0, 12) | hamon::views::stride(3);
	{
		std::stringstream out;
		hamon::ranges::copy(input, std::ostream_iterator<int>(out, " "));                  // prints 0 3 6 9
		EXPECT_EQ("0 3 6 9 ", out.str());
	}
	{
		std::stringstream out;
		hamon::ranges::copy(input | hamon::views::reverse, std::ostream_iterator<int>(out, " ")); // prints 9 6 3 0
		EXPECT_EQ("9 6 3 0 ", out.str());
	}
#endif
}

}	// namespace overview_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
