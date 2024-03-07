/**
 *	@file	unit_test_ranges_cartesian_product_view_overview.cpp
 *
 *	@brief	cartesian_product_view のテスト
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <iterator>

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, CartesianProductViewOverviewTest)
{
	// [range.cartesian.overview]/3
	// Example 1:
	std::stringstream out;
	std::vector<int> v {0, 1, 2};
#if defined(HAMON_HAS_CXX17_STRUCTURED_BINDINGS)
	for (auto&& [a, b, c] : hamon::views::cartesian_product(v, v, v))
	{
		out << a << ' ' << b << ' ' << c << '\n';
	}
#else
	for (auto&& t : hamon::views::cartesian_product(v, v, v))
	{
		auto&& a = hamon::adl_get<0>(t);
		auto&& b = hamon::adl_get<1>(t);
		auto&& c = hamon::adl_get<2>(t);
		out << a << ' ' << b << ' ' << c << '\n';
	}
#endif
	// The above prints
	// 0 0 0
	// 0 0 1
	// 0 0 2
	// 0 1 0
	// 0 1 1
	// ...
	EXPECT_EQ(R"(0 0 0
0 0 1
0 0 2
0 1 0
0 1 1
0 1 2
0 2 0
0 2 1
0 2 2
1 0 0
1 0 1
1 0 2
1 1 0
1 1 1
1 1 2
1 2 0
1 2 1
1 2 2
2 0 0
2 0 1
2 0 2
2 1 0
2 1 1
2 1 2
2 2 0
2 2 1
2 2 2
)", out.str());
}

}	// namespace overview_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
