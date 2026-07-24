/**
 *	@file	unit_test_ranges_cache_latest_view_sentinel_sub.cpp
 *
 *	@brief	operator-() のテスト
 *
 *	friend constexpr range_difference_t<V> operator-(const iterator& x, const sentinel& y)
 *		requires sized_sentinel_for<sentinel_t<V>, iterator_t<V>>;
 *	friend constexpr range_difference_t<V> operator-(const sentinel& x, const iterator& y)
 *		requires sized_sentinel_for<sentinel_t<V>, iterator_t<V>>;
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
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
namespace sentinel_sub_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class ViewWrapper>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = ViewWrapper<T>;
	using CLV = hamon::ranges::cache_latest_view<V>;
	using I = decltype(hamon::declval<CLV&>().begin());
	using S = decltype(hamon::declval<CLV&>().end());
	using BaseIter = hamon::ranges::iterator_t<V>;
	using BaseSent = hamon::ranges::sentinel_t<V>;

	static_assert(has_minus<I, I>::value == false, "");
	static_assert(has_minus<I, S>::value == hamon::sized_sentinel_for<BaseSent, BaseIter>, "");
	static_assert(has_minus<S, I>::value == hamon::sized_sentinel_for<BaseSent, BaseIter>, "");
	static_assert(has_minus<S, S>::value == false, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1,2,3,4};
	auto clv = hamon::views::cache_latest(a);
	using V = decltype(clv.base());

	auto it = clv.begin();
	auto sent = clv.end();

	static_assert(hamon::is_same<decltype(it - sent), hamon::ranges::range_difference_t<V>>::value, "");
	static_assert(hamon::is_same<decltype(sent - it), hamon::ranges::range_difference_t<V>>::value, "");

	VERIFY((it - sent) == -4);
	VERIFY((sent - it) ==  4);
	it++;
	VERIFY((it - sent) == -3);
	VERIFY((sent - it) ==  3);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CacheLatestViewSentinelSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_sized_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace sentinel_sub_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
