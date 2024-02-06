/**
 *	@file	unit_test_ranges_common_view_overview.cpp
 *
 *	@brief	common_view のテスト
 */

#include <hamon/ranges/adaptors/common_view.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/counted_iterator.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/ssize.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include <list>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace common_view_test
{
namespace overview_test
{

// Legacy algorithm:
template <typename ForwardIterator>
void legacy_func(ForwardIterator, ForwardIterator)
{
}

GTEST_TEST(RangesTest, CommonViewOverviewTest)
{
	{
		// [range.common.overview]/4
		// Example 1:
		int a[] = {1,2,3};
		test_forward_range<int> r(a);
		//legacy_func(r.begin(), r.end());	// 呼び出し不可
		auto&& common = hamon::views::common(r);
		legacy_func(common.begin(), common.end());
	}

	// 無限長のiotaはcommon_rangeではない
	static_assert(!hamon::ranges::common_range_t<decltype(hamon::views::iota(0))>::value, "");
	// commonを適用するとcommon_rangeになる
	static_assert(hamon::ranges::common_range_t<decltype(hamon::views::iota(0) | hamon::views::common)>::value, "");

	// 元からcommon_rangeなviewに適用しても型は変わらない
	static_assert(hamon::same_as_t<decltype(hamon::string_view {} | hamon::views::common), hamon::string_view>::value, "");

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		auto v1 = {1, 2, 3, 4, 5};
		auto i1 = hamon::counted_iterator{v1.begin(), hamon::ssize(v1)};
		auto r1 = hamon::ranges::subrange{i1, hamon::default_sentinel};
//		auto e1 = hamon::accumulate(r1.begin(), r1.end(), 0); // error: "common range" required
		auto c1 = hamon::ranges::common_view{r1};
		auto e1 = hamon::accumulate(c1.begin(), c1.end(), 0);
		EXPECT_EQ(15, e1);

		// inherited from ranges::view_interface:
		EXPECT_EQ(1, c1.front());
		EXPECT_EQ(5, c1.back());
		EXPECT_EQ(v1.begin(), c1.data());
		EXPECT_EQ(1, c1[0]);
	}
	{
		auto v2 = std::list{1, 2, 3, 4, 5};
		auto i2 = hamon::counted_iterator{v2.begin(), hamon::ssize(v2)};
		auto r2 = hamon::ranges::subrange{i2, hamon::default_sentinel};
//		auto e2 = hamon::accumulate(r2.begin(), r2.end(), 0); // error: "common range" required
		auto c2 = hamon::ranges::common_view {r2};
		auto e2 = hamon::accumulate(c2.begin(), c2.end(), 0);
		EXPECT_EQ(15, e2);

		// inherited from ranges::view_interface:
		EXPECT_EQ(1, c2.front());
//		auto e3 = c2.back(); // error: "bidirectional range" required
//		auto e4 = c2.data(); // error: "contiguous range" required
//		auto e5 = c2[0];     // error: "random access range" required
	}
#endif
}

}	// namespace overview_test
}	// namespace common_view_test
}	// namespace hamon_ranges_test
