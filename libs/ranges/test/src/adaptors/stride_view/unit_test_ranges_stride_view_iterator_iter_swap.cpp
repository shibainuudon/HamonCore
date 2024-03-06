/**
 *	@file	unit_test_ranges_stride_view_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 *
 *	friend constexpr void iter_swap(const iterator& x, const iterator& y)
 *	  noexcept(noexcept(ranges::iter_swap(x.current_, y.current_)))
 *	  requires indirectly_swappable<iterator_t<Base>>;
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
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
		using V = test_input_view<int const>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_iter_swap<I>::value, "");
	}
	{
		using V = test_input_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_iter_swap<I>::value, "");

		int a1[] = {11,12,13,14};
		int a2[] = {21,22,23,24,25};
		V v1(a1);
		V v2(a2);
		SV sv1{v1, 2};
		SV sv2{v2, 3};

		auto it1 = sv1.begin();
		auto it2 = sv2.begin();
		++it1;
		++it2;
		static_assert(!noexcept(hamon::ranges::iter_swap(it1, it2)), "");

		hamon::ranges::iter_swap(it1, it2);

		VERIFY(a1[0] == 11);
		VERIFY(a1[1] == 12);
		VERIFY(a1[2] == 24);
		VERIFY(a1[3] == 14);

		VERIFY(a2[0] == 21);
		VERIFY(a2[1] == 22);
		VERIFY(a2[2] == 23);
		VERIFY(a2[3] == 13);
		VERIFY(a2[4] == 25);
	}
	{
		using V = test_view<int, int*>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_iter_swap<I>::value, "");

		int a1[] = {11,12,13,14};
		int a2[] = {21,22,23,24,25};
		V v1(a1);
		V v2(a2);
		SV sv1{v1, 2};
		SV sv2{v2, 3};

		auto it1 = sv1.begin();
		auto it2 = sv2.begin();
		++it1;
		++it2;
		static_assert( noexcept(hamon::ranges::iter_swap(it1, it2)), "");

		hamon::ranges::iter_swap(it1, it2);

		VERIFY(a1[0] == 11);
		VERIFY(a1[1] == 12);
		VERIFY(a1[2] == 24);
		VERIFY(a1[3] == 14);

		VERIFY(a2[0] == 21);
		VERIFY(a2[1] == 22);
		VERIFY(a2[2] == 23);
		VERIFY(a2[3] == 13);
		VERIFY(a2[4] == 25);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewIteratorIterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_iter_swap_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
