/**
 *	@file	unit_test_ranges_cache_latest_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin();
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace begin_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class ViewWrapper>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = ViewWrapper<int>;
	using CLV = hamon::ranges::cache_latest_view<V>;

	static_assert( has_begin<CLV&>::value, "");
	static_assert(!has_begin<CLV const&>::value, "");
	static_assert( has_cbegin<CLV&>::value, "");
	static_assert(!has_cbegin<CLV const&>::value, "");

	int a[] = { 1,2,3 };
	V v(a);

	CLV clv(v);
	auto it = clv.begin();
	VERIFY(*it == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CacheLatestViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_view>());
}

}	// namespace begin_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
