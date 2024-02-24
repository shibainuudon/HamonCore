/**
 *	@file	unit_test_ranges_adjacent_view_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap() のテスト
 *
 *	friend constexpr void iter_swap(const iterator& l, const iterator& r) noexcept(see below)
 *	  requires indirectly_swappable<iterator_t<Base>>;
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace iterator_iter_swap_test
{

template <typename T, typename = void>
struct has_iter_swap
	: public hamon::false_type {};

template <typename T>
struct has_iter_swap<T, hamon::void_t<decltype(hamon::ranges::iter_swap(hamon::declval<T>(), hamon::declval<T>()))>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int const>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_iter_swap<I>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(has_iter_swap<I>::value, "");

		int a1[] = {11,12,13,14};
		int a2[] = {21,22,23,24,25};
		V v1(a1);
		V v2(a2);
		AV av1{v1};
		AV av2{v2};

		auto it1 = av1.begin();
		auto it2 = av2.begin();
		++it2;
		static_assert(!noexcept(hamon::ranges::iter_swap(it1, it2)), "");
		
		hamon::ranges::iter_swap(it1, it2);

		VERIFY(a1[0] == 22);
		VERIFY(a1[1] == 23);
		VERIFY(a1[2] == 13);
		VERIFY(a1[3] == 14);

		VERIFY(a2[0] == 21);
		VERIFY(a2[1] == 11);
		VERIFY(a2[2] == 12);
		VERIFY(a2[3] == 24);
		VERIFY(a2[4] == 25);
	}
	{
		using V = test_view<int, int*>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(has_iter_swap<I>::value, "");

		int a1[] = {11,12,13,14};
		int a2[] = {21,22,23,24,25};
		V v1(a1);
		V v2(a2);
		AV av1{v1};
		AV av2{v2};

		auto it1 = av1.begin();
		auto it2 = av2.begin();
		++it2;
		static_assert( noexcept(hamon::ranges::iter_swap(it1, it2)), "");
		
		hamon::ranges::iter_swap(it1, it2);

		VERIFY(a1[0] == 22);
		VERIFY(a1[1] == 23);
		VERIFY(a1[2] == 13);
		VERIFY(a1[3] == 14);

		VERIFY(a2[0] == 21);
		VERIFY(a2[1] == 11);
		VERIFY(a2[2] == 12);
		VERIFY(a2[3] == 24);
		VERIFY(a2[4] == 25);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewIteratorIterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_iter_swap_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
