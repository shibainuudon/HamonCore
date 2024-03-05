/**
 *	@file	unit_test_ranges_chunk_by_view_overview.cpp
 *
 *	@brief	chunk_by_view のテスト
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/functional/ranges/less_equal.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, ChunkByViewOverviewTest)
{
	// [range.chunk.by.overview]/2
	// Example 1:
	std::vector<int> v = {1, 2, 2, 3, 0, 4, 5, 2};
	std::stringstream out;

	for (auto r : v | hamon::views::chunk_by(hamon::ranges::less_equal{}))
	{
		out << '[';
		auto sep = "";
		for (auto i : r)
		{
			out << sep << i;
			sep = ", ";
		}
		out << "] ";
	}
	// The above prints [1, 2, 2, 3] [0, 4, 5] [2]
	EXPECT_EQ("[1, 2, 2, 3] [0, 4, 5] [2] ", out.str());
}

}	// namespace overview_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
