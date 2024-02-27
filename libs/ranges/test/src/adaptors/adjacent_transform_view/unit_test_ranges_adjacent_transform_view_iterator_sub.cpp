/**
 *	@file	unit_test_ranges_adjacent_transform_view_iterator_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	friend constexpr iterator operator-(const iterator& i, difference_type n)
 *	  requires random_access_range<Base>;
 *	friend constexpr difference_type operator-(const iterator& x, const iterator& y)
 *	  requires sized_sentinel_for<inner-iterator<Const>, inner-iterator<Const>>;
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace iterator_sub_test
{

struct F
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

template <typename T, typename U, typename = void>
struct has_sub
	: public hamon::false_type {};

template <typename T, typename U>
struct has_sub<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

		int a[] = {1,2,3,4};
		V v(a);
		AV av{v, F{}};

		auto it1 = av.begin() + 2;
		auto it2 = it1 - 1;
		auto it3 = it1 - 2;
		VERIFY(*it2 == 5);
		VERIFY(*it3 == 3);
		VERIFY((it1 - it1) ==  0);
		VERIFY((it1 - it2) ==  1);
		VERIFY((it1 - it3) ==  2);
		VERIFY((it3 - it1) == -2);
		VERIFY((it3 - it2) == -1);
		VERIFY((it3 - it3) ==  0);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewIteratorSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_sub_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
