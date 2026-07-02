/**
 *	@file	unit_test_ranges_cartesian_product_view_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, const iterator& y)
 *	  requires equality_comparable<iterator_t<maybe-const<Const, First>>>;
 *
 *	friend constexpr bool operator==(const iterator& x, default_sentinel_t);
 *
 *	friend constexpr auto operator<=>(const iterator& x, const iterator& y)
 *	  requires all-random-access<Const, First, Vs...>;
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/compare/is_lt.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
{
namespace iterator_compare_test
{

template <typename T>
struct NonComparableIterator
{
	T*	m_ptr;

	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;

	NonComparableIterator& operator++();
	NonComparableIterator  operator++(int);
	T&                     operator*() const;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_view<int, NonComparableIterator<int>>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_eq  <I const&, I const&>::value, "");
		static_assert(!has_neq <I const&, I const&>::value, "");
		static_assert(!has_lt  <I const&, I const&>::value, "");
		static_assert(!has_lteq<I const&, I const&>::value, "");
		static_assert(!has_gt  <I const&, I const&>::value, "");
		static_assert(!has_gteq<I const&, I const&>::value, "");

		static_assert( has_eq  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lteq<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gteq<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I const&, I const&>::value, "");
		static_assert(!has_compare_three_way<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_compare_three_way<hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_eq  <I const&, I const&>::value, "");
		static_assert( has_neq <I const&, I const&>::value, "");
		static_assert(!has_lt  <I const&, I const&>::value, "");
		static_assert(!has_lteq<I const&, I const&>::value, "");
		static_assert(!has_gt  <I const&, I const&>::value, "");
		static_assert(!has_gteq<I const&, I const&>::value, "");

		static_assert( has_eq  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lteq<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gteq<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I const&, I const&>::value, "");
		static_assert(!has_compare_three_way<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_compare_three_way<hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_forward_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_eq  <I const&, I const&>::value, "");
		static_assert( has_neq <I const&, I const&>::value, "");
		static_assert(!has_lt  <I const&, I const&>::value, "");
		static_assert(!has_lteq<I const&, I const&>::value, "");
		static_assert(!has_gt  <I const&, I const&>::value, "");
		static_assert(!has_gteq<I const&, I const&>::value, "");

		static_assert( has_eq  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lteq<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gteq<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I const&, I const&>::value, "");
		static_assert(!has_compare_three_way<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_compare_three_way<hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_bidirectional_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_eq  <I const&, I const&>::value, "");
		static_assert( has_neq <I const&, I const&>::value, "");
		static_assert(!has_lt  <I const&, I const&>::value, "");
		static_assert(!has_lteq<I const&, I const&>::value, "");
		static_assert(!has_gt  <I const&, I const&>::value, "");
		static_assert(!has_gteq<I const&, I const&>::value, "");

		static_assert( has_eq  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lteq<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gteq<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I const&, I const&>::value, "");
		static_assert(!has_compare_three_way<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_compare_three_way<hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_eq  <I const&, I const&>::value, "");
		static_assert( has_neq <I const&, I const&>::value, "");
		static_assert( has_lt  <I const&, I const&>::value, "");
		static_assert( has_lteq<I const&, I const&>::value, "");
		static_assert( has_gt  <I const&, I const&>::value, "");
 		static_assert( has_gteq<I const&, I const&>::value, "");

		static_assert( has_eq  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lteq<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gteq<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( has_compare_three_way<I const&, I const&>::value, "");
		static_assert(!has_compare_three_way<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_compare_three_way<hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_contiguous_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_eq  <I const&, I const&>::value, "");
		static_assert( has_neq <I const&, I const&>::value, "");
		static_assert( has_lt  <I const&, I const&>::value, "");
		static_assert( has_lteq<I const&, I const&>::value, "");
		static_assert( has_gt  <I const&, I const&>::value, "");
 		static_assert( has_gteq<I const&, I const&>::value, "");

		static_assert( has_eq  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lteq<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gteq<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( has_compare_three_way<I const&, I const&>::value, "");
		static_assert(!has_compare_three_way<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_compare_three_way<hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_view<int, int*>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_eq  <I const&, I const&>::value, "");
		static_assert( has_neq <I const&, I const&>::value, "");
		static_assert( has_lt  <I const&, I const&>::value, "");
		static_assert( has_lteq<I const&, I const&>::value, "");
		static_assert( has_gt  <I const&, I const&>::value, "");
 		static_assert( has_gteq<I const&, I const&>::value, "");

		static_assert( has_eq  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lteq<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gteq<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( has_compare_three_way<I const&, I const&>::value, "");
		static_assert(!has_compare_three_way<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_compare_three_way<hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_eq  <I const&, I const&>::value, "");
		static_assert( has_neq <I const&, I const&>::value, "");
		static_assert( has_lt  <I const&, I const&>::value, "");
		static_assert( has_lteq<I const&, I const&>::value, "");
		static_assert( has_gt  <I const&, I const&>::value, "");
 		static_assert( has_gteq<I const&, I const&>::value, "");

		static_assert( has_eq  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lteq<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gteq<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( has_compare_three_way<I const&, I const&>::value, "");
		static_assert(!has_compare_three_way<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_compare_three_way<hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_bidirectional_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_eq  <I const&, I const&>::value, "");
		static_assert( has_neq <I const&, I const&>::value, "");
		static_assert(!has_lt  <I const&, I const&>::value, "");
		static_assert(!has_lteq<I const&, I const&>::value, "");
		static_assert(!has_gt  <I const&, I const&>::value, "");
 		static_assert(!has_gteq<I const&, I const&>::value, "");

		static_assert( has_eq  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lteq<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gteq<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I const&, I const&>::value, "");
		static_assert(!has_compare_three_way<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_compare_three_way<hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_eq  <I const&, I const&>::value, "");
		static_assert( has_neq <I const&, I const&>::value, "");
		static_assert(!has_lt  <I const&, I const&>::value, "");
		static_assert(!has_lteq<I const&, I const&>::value, "");
		static_assert(!has_gt  <I const&, I const&>::value, "");
 		static_assert(!has_gteq<I const&, I const&>::value, "");

		static_assert( has_eq  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_lteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gt  <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_gteq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_lteq<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gt  <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_gteq<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I const&, I const&>::value, "");
		static_assert(!has_compare_three_way<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_compare_three_way<hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_input_view<int>;
	using CV = hamon::ranges::cartesian_product_view<V>;

	int a[] = {1,2};
	V v(a);
	CV cv(v);

	auto it1 = cv.begin();
	auto it2 = cv.begin();
	auto it3 = cv.begin();
	auto it4 = cv.begin();
	auto it5 = cv.begin();
	++it3;
	++it4;
	++it5;
	++it5;

	VERIFY( (it1 == it1));
	VERIFY( (it1 == it2));
	VERIFY(!(it1 == it3));
	VERIFY(!(it1 == it4));
	VERIFY(!(it1 == it5));

	VERIFY(!(it3 == it1));
	VERIFY(!(it3 == it2));
	VERIFY( (it3 == it3));
	VERIFY( (it3 == it4));
	VERIFY(!(it3 == it5));

	VERIFY(!(it1 != it1));
	VERIFY(!(it1 != it2));
	VERIFY( (it1 != it3));
	VERIFY( (it1 != it4));
	VERIFY( (it1 != it5));

	VERIFY( (it3 != it1));
	VERIFY( (it3 != it2));
	VERIFY(!(it3 != it3));
	VERIFY(!(it3 != it4));
	VERIFY( (it3 != it5));

	VERIFY(!(it1 == hamon::default_sentinel));
	VERIFY(!(it2 == hamon::default_sentinel));
	VERIFY(!(it3 == hamon::default_sentinel));
	VERIFY(!(it4 == hamon::default_sentinel));
	VERIFY( (it5 == hamon::default_sentinel));

	VERIFY( (it1 != hamon::default_sentinel));
	VERIFY( (it2 != hamon::default_sentinel));
	VERIFY( (it3 != hamon::default_sentinel));
	VERIFY( (it4 != hamon::default_sentinel));
	VERIFY(!(it5 != hamon::default_sentinel));

	VERIFY(!(hamon::default_sentinel == it1));
	VERIFY(!(hamon::default_sentinel == it2));
	VERIFY(!(hamon::default_sentinel == it3));
	VERIFY(!(hamon::default_sentinel == it4));
	VERIFY( (hamon::default_sentinel == it5));

	VERIFY( (hamon::default_sentinel != it1));
	VERIFY( (hamon::default_sentinel != it2));
	VERIFY( (hamon::default_sentinel != it3));
	VERIFY( (hamon::default_sentinel != it4));
	VERIFY(!(hamon::default_sentinel != it5));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V = test_random_access_view<int>;
	using CV = hamon::ranges::cartesian_product_view<V, V>;

	int a1[] = {1,2};
	int a2[] = {3,4,5};
	V v1(a1);
	V v2(a2);
	CV cv(v1, v2);

	auto it1 = cv.begin();
	auto it2 = cv.begin();
	auto it3 = cv.begin();
	auto it4 = cv.begin();
	++it2;
	++it3;
	++it3;
	++it4;++it4;++it4;++it4;++it4;++it4;

	VERIFY(!(it2 == it1));
	VERIFY( (it2 == it2));
	VERIFY(!(it2 == it3));
	VERIFY(!(it2 == it4));

	VERIFY( (it2 != it1));
	VERIFY(!(it2 != it2));
	VERIFY( (it2 != it3));
	VERIFY( (it2 != it4));

	VERIFY(!(it2 <  it1));
	VERIFY(!(it2 <  it2));
	VERIFY( (it2 <  it3));
	VERIFY( (it2 <  it4));

	VERIFY(!(it2 <= it1));
	VERIFY( (it2 <= it2));
	VERIFY( (it2 <= it3));
	VERIFY( (it2 <= it4));

	VERIFY( (it2 >  it1));
	VERIFY(!(it2 >  it2));
	VERIFY(!(it2 >  it3));
	VERIFY(!(it2 >  it4));

	VERIFY( (it2 >= it1));
	VERIFY( (it2 >= it2));
	VERIFY(!(it2 >= it3));
	VERIFY(!(it2 >= it4));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_gt(it2 <=> it1));
	VERIFY(hamon::is_eq(it2 <=> it2));
	VERIFY(hamon::is_lt(it2 <=> it3));
	VERIFY(hamon::is_lt(it2 <=> it4));
#endif

	VERIFY(!(it1 == hamon::default_sentinel));
	VERIFY(!(it2 == hamon::default_sentinel));
	VERIFY(!(it3 == hamon::default_sentinel));
	VERIFY( (it4 == hamon::default_sentinel));

	VERIFY( (it1 != hamon::default_sentinel));
	VERIFY( (it2 != hamon::default_sentinel));
	VERIFY( (it3 != hamon::default_sentinel));
	VERIFY(!(it4 != hamon::default_sentinel));

	VERIFY(!(hamon::default_sentinel == it1));
	VERIFY(!(hamon::default_sentinel == it2));
	VERIFY(!(hamon::default_sentinel == it3));
	VERIFY( (hamon::default_sentinel == it4));

	VERIFY( (hamon::default_sentinel != it1));
	VERIFY( (hamon::default_sentinel != it2));
	VERIFY( (hamon::default_sentinel != it3));
	VERIFY(!(hamon::default_sentinel != it4));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_compare_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
