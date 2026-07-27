/**
 *	@file	unit_test_ranges_as_input_view_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap() のテスト
 *
 *	friend constexpr void iter_swap(const iterator& x, const iterator& y)
 *		noexcept(noexcept(ranges::iter_swap(x.current_, y.current_)))
 *		requires indirectly_swappable<iterator_t<Base>>;
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace iterator_iter_swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = test_input_view<T>;
	using AIV = hamon::ranges::as_input_view<V>;
	using I  = decltype(hamon::declval<AIV&>().begin());

	static_assert( has_iter_swap<I>::value, "");
	static_assert(!noexcept(hamon::ranges::iter_swap(hamon::declval<I>(), hamon::declval<I>())), "");
	static_assert( hamon::is_same<decltype(hamon::ranges::iter_swap(hamon::declval<I>(), hamon::declval<I>())), void>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using T = int const;
	using V = test_input_view<T>;
	using AIV = hamon::ranges::as_input_view<V>;
	using I  = decltype(hamon::declval<AIV&>().begin());

	static_assert(!has_iter_swap<I>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1,2,3,4};
	auto aiv = hamon::views::as_input(a);

	auto it = aiv.begin();
	using I = decltype(it);

	static_assert( has_iter_swap<I>::value, "");
	static_assert( noexcept(hamon::ranges::iter_swap(hamon::declval<I>(), hamon::declval<I>())), "");
	static_assert( hamon::is_same<decltype(hamon::ranges::iter_swap(hamon::declval<I>(), hamon::declval<I>())), void>::value, "");

	auto it1 = aiv.begin();
	auto it2 = aiv.begin();
	++it2;

	hamon::ranges::iter_swap(it1, it2);

	VERIFY(*it == 2);
	it++;
	VERIFY(*it == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewIteratorIterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_iter_swap_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
