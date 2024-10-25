/**
 *	@file	unit_test_ranges_chunk_view_overview.cpp
 *
 *	@brief	chunk_view のテスト
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_ranges_test
{
namespace chunk_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, ChunkViewOverviewTest)
{
	{
		// [range.chunk.overview]/2
		// Example 1:
		std::stringstream out;

		hamon::vector<int> v = {1, 2, 3, 4, 5};
		for (auto r : v | hamon::views::chunk(2))
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

		EXPECT_EQ("[1, 2] [3, 4] [5] ", out.str());
	}
}

}	// namespace overview_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
