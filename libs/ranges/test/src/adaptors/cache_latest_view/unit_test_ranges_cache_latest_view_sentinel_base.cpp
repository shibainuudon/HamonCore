/**
 *	@file	unit_test_ranges_cache_latest_view_sentinel_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr sentinel_t<V> base() const;
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace sentinel_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class ViewWrapper>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = ViewWrapper<T>;
	using CLV = hamon::ranges::cache_latest_view<V>;
	using S  = decltype(hamon::declval<CLV&>().end());
	using BaseSent = hamon::ranges::sentinel_t<V>;

	static_assert(hamon::is_same<decltype(hamon::declval<S>().base()), BaseSent>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<S const>().base()), BaseSent>::value, "");

	int a[] = {1,2,3};
	V v(a);
	CLV clv(v);
	auto sent = clv.end();
	VERIFY(v.begin() != sent.base());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CacheLatestViewSentinelBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_view>());
}

}	// namespace sentinel_base_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
