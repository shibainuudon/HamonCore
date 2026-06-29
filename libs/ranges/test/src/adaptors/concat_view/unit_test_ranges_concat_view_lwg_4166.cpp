/**
 *	@file	unit_test_ranges_concat_view_lwg_4166_test.cpp
 *
 *	@brief	LWG 4166 のテスト
 *
 *	https://cplusplus.github.io/LWG/issue4166
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/factories/istream_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace lwg_4166_test
{

GTEST_TEST(RangesTest, ConcatViewLWG4166Test)
{
	auto range_copyable_it = hamon::vector<int>{ 1, 2, 3 };
	{
		std::stringstream ss{ "4 5 6" };
		auto range_noncopyable_it = hamon::views::istream<int>(ss);

		auto view1 = hamon::views::concat(range_copyable_it, range_noncopyable_it);
		static_assert(hamon::ranges::range<decltype(view1)>, "");               // ok
		EXPECT_TRUE(hamon::ranges::equal(view1, hamon::vector<int>{ 1, 2, 3, 4, 5, 6 })); // ok
	}
	{
		std::stringstream ss{ "4 5 6" };
		auto range_noncopyable_it = hamon::views::istream<int>(ss);

		auto view2 = hamon::views::concat(range_noncopyable_it, range_copyable_it);
		static_assert(hamon::ranges::range<decltype(view2)>, "");               // ok
		EXPECT_TRUE(hamon::ranges::equal(view2, hamon::vector<int>{ 4, 5, 6, 1, 2, 3 })); // ok
	}
}

}	// namespace lwg_4166_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
