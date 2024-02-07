/**
 *	@file	unit_test_ranges_as_const_view_overview.cpp
 *
 *	@brief	as_const_view のテスト
 */

#include <hamon/ranges/adaptors/as_const_view.hpp>
#include <hamon/ranges/concepts/constant_range.hpp>
#include <hamon/span.hpp>
#include <gtest/gtest.h>
#include <vector>

namespace hamon_ranges_test
{
namespace as_const_view_test
{
namespace overview_test
{

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::constant_range, R)>
void cant_touch_this(R&&) {}

GTEST_TEST(RangesTest, AsConstViewOverviewTest)
{
	{
		// [range.as.const.overview]/3
		// Example 1:
		//std::vector<char> hammer = { 'm', 'c' };
		char hammer[] = { 'm', 'c' };
		hamon::span<char> beat = hammer;
		cant_touch_this(hamon::views::as_const(beat));
	}
}

}	// namespace overview_test
}	// namespace as_const_view_test
}	// namespace hamon_ranges_test
