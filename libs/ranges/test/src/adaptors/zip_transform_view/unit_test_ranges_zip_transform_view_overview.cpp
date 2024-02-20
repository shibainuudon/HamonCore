/**
 *	@file	unit_test_ranges_zip_transform_view_overview.cpp
 *
 *	@brief	zip_transform_view のテスト
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/functional/ranges/plus.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, ZipTransformViewOverviewTest)
{
	{
		// [range.zip.transform.overview]/3
		// Example 1:
		std::vector<int> v1 = {1, 2};
		std::vector<int> v2 = {4, 5, 6};

		std::stringstream out;
		for (auto i : hamon::views::zip_transform(hamon::ranges::plus{}, v1, v2))
		{
			out << i << ' ';     // prints 5 7
		}
		EXPECT_EQ("5 7 ", out.str());
	}
}

}	// namespace overview_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
