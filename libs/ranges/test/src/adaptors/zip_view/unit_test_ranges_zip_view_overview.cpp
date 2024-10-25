/**
 *	@file	unit_test_ranges_zip_view_overview.cpp
 *
 *	@brief	zip_view のテスト
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/list.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, ZipViewOverviewTest)
{
#if defined(HAMON_HAS_CXX17_RANGE_BASED_FOR) && \
	defined(HAMON_HAS_CXX17_STRUCTURED_BINDINGS) && \
	defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		// [range.zip.overview]/2
		// Example 1:
		std::vector v = {1, 2};
		hamon::list l = {'a', 'b', 'c'};

		auto z = hamon::views::zip(v, l);
		hamon::ranges::range_reference_t<decltype(z)> f = z.front();   // f is a tuple<int&, char&>
		(void)f;												// that refers to the first element of v and l

		std::stringstream out;
		for (auto&& [x, y] : z)
		{
			out << '(' << x << ", " << y << ") ";        // prints (1, a) (2, b)
		}
		EXPECT_EQ("(1, a) (2, b) ", out.str());
	}
#endif
}

}	// namespace overview_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
