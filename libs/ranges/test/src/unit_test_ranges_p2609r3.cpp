/**
 *	@file	unit_test_ranges_p2609r3.cpp
 *
 *	@brief	P2609R3 のテスト
 *
 *	https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2609r3.html
 */

#include <hamon/algorithm/ranges/for_each.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/memory/make_unique.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(RangesTest, P2609R3Test)
{
	std::stringstream out;
	hamon::ranges::for_each(
		hamon::views::iota(0, 5),
		[&](std::unique_ptr<int> v) {
			out << *v << " ";
		},
		[](int v) {
			return hamon::make_unique<int>(v);
		});
	EXPECT_EQ("0 1 2 3 4 ", out.str());
}
