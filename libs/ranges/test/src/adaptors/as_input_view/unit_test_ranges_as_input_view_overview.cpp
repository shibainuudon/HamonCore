/**
 *	@file	unit_test_ranges_as_input_view_overview.cpp
 *
 *	@brief	as_input_view のテスト
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, AsInputViewOverviewTest)
{
	hamon::vector<int> r{ 1,2,3 };
	auto v = r | hamon::views::as_input;
	using type = decltype(v);
	static_assert(hamon::ranges::input_range<type> && !hamon::ranges::forward_range<type>, "");

	EXPECT_TRUE(hamon::ranges::equal(v.base(), r));
	EXPECT_TRUE(v.size() == r.size());
	EXPECT_TRUE(v.end() == r.end());
	auto it = v.begin();
	EXPECT_TRUE(it != r.end());
	*it = 42;
	++it;
	*it = 43;
	it++;
	hamon::ranges::iter_swap(v.begin(), it);
	int const expected[] = { 3, 43, 42 };
	EXPECT_TRUE(hamon::ranges::equal(r, expected));
	*it = hamon::ranges::iter_move(it);
	EXPECT_TRUE(it == r.begin() + 2);
	EXPECT_TRUE(r.end() - it == 1);
	EXPECT_TRUE(it - r.end() == -1);
}

}	// namespace overview_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
