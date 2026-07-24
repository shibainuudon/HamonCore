/**
 *	@file	unit_test_ranges_cache_latest_view_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap() のテスト
 *
 *	friend constexpr void iter_swap(const iterator& x, const iterator& y)
 *		noexcept(noexcept(ranges::iter_swap(x.current_, y.current_)))
 *		requires indirectly_swappable<iterator_t<V>>;
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
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
namespace iterator_iter_swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = test_input_view<T>;
	using CLV = hamon::ranges::cache_latest_view<V>;
	using I  = decltype(hamon::declval<CLV&>().begin());

	static_assert( has_iter_swap<I>::value, "");
	static_assert(!noexcept(hamon::ranges::iter_swap(hamon::declval<I>(), hamon::declval<I>())), "");
	static_assert( hamon::is_same<decltype(hamon::ranges::iter_swap(hamon::declval<I>(), hamon::declval<I>())), void>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using T = int const;
	using V = test_input_view<T>;
	using CLV = hamon::ranges::cache_latest_view<V>;
	using I  = decltype(hamon::declval<CLV&>().begin());

	static_assert(!has_iter_swap<I>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1,2,3,4};
	auto clv = hamon::views::cache_latest(a);

	auto it = clv.begin();
	using I = decltype(it);

	static_assert( has_iter_swap<I>::value, "");
	static_assert( noexcept(hamon::ranges::iter_swap(hamon::declval<I>(), hamon::declval<I>())), "");
	static_assert( hamon::is_same<decltype(hamon::ranges::iter_swap(hamon::declval<I>(), hamon::declval<I>())), void>::value, "");

	auto it1 = clv.begin();
	auto it2 = clv.begin();
	++it2;

	hamon::ranges::iter_swap(it1, it2);

	VERIFY(*it == 2);
	it++;
	VERIFY(*it == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CacheLatestViewIteratorIterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_iter_swap_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
