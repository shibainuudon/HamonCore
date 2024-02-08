/**
 *	@file	unit_test_ranges_elements_view_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, const iterator& y)
 *	  requires equality_comparable<iterator_t<Base>>;
 *	friend constexpr bool operator<(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base>;
 *	friend constexpr bool operator>(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base>;
 *	friend constexpr bool operator<=(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base>;
 *	friend constexpr bool operator>=(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base>;
 *	friend constexpr auto operator<=>(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base> && three_way_comparable<iterator_t<Base>>;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/compare/is_lt.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/tuple.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
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

template <typename T, typename = void>
struct has_equal
	: public hamon::false_type {};

template <typename T>
struct has_equal<T, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_not_equal
	: public hamon::false_type {};

template <typename T>
struct has_not_equal<T, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_less
	: public hamon::false_type {};

template <typename T>
struct has_less<T, hamon::void_t<decltype(hamon::declval<T>() < hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_less_equal
	: public hamon::false_type {};

template <typename T>
struct has_less_equal<T, hamon::void_t<decltype(hamon::declval<T>() <= hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_greater
	: public hamon::false_type {};

template <typename T>
struct has_greater<T, hamon::void_t<decltype(hamon::declval<T>() > hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_greater_equal
	: public hamon::false_type {};

template <typename T>
struct has_greater_equal<T, hamon::void_t<decltype(hamon::declval<T>() >= hamon::declval<T>())>>
	: public hamon::true_type {};

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename = void>
struct has_three_way
	: public hamon::false_type {};

template <typename T>
struct has_three_way<T, hamon::void_t<decltype(hamon::declval<T>() <=> hamon::declval<T>())>>
	: public hamon::true_type {};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_view<Tuple, NonComparableIterator<Tuple>>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_equal        <I const&>::value, "");
		static_assert(!has_not_equal    <I const&>::value, "");
		static_assert(!has_less         <I const&>::value, "");
		static_assert(!has_less_equal   <I const&>::value, "");
		static_assert(!has_greater      <I const&>::value, "");
		static_assert(!has_greater_equal<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&>::value, "");
#endif
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_equal        <I const&>::value, "");
		static_assert( has_not_equal    <I const&>::value, "");
		static_assert(!has_less         <I const&>::value, "");
		static_assert(!has_less_equal   <I const&>::value, "");
		static_assert(!has_greater      <I const&>::value, "");
		static_assert(!has_greater_equal<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&>::value, "");
#endif
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_forward_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_equal        <I const&>::value, "");
		static_assert( has_not_equal    <I const&>::value, "");
		static_assert(!has_less         <I const&>::value, "");
		static_assert(!has_less_equal   <I const&>::value, "");
		static_assert(!has_greater      <I const&>::value, "");
		static_assert(!has_greater_equal<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&>::value, "");
#endif
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_bidirectional_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_equal        <I const&>::value, "");
		static_assert( has_not_equal    <I const&>::value, "");
		static_assert(!has_less         <I const&>::value, "");
		static_assert(!has_less_equal   <I const&>::value, "");
		static_assert(!has_greater      <I const&>::value, "");
		static_assert(!has_greater_equal<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&>::value, "");
#endif
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_random_access_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_equal        <I const&>::value, "");
		static_assert( has_not_equal    <I const&>::value, "");
		static_assert( has_less         <I const&>::value, "");
		static_assert( has_less_equal   <I const&>::value, "");
		static_assert( has_greater      <I const&>::value, "");
		static_assert( has_greater_equal<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&>::value, "");
#endif
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_contiguous_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_equal        <I const&>::value, "");
		static_assert( has_not_equal    <I const&>::value, "");
		static_assert( has_less         <I const&>::value, "");
		static_assert( has_less_equal   <I const&>::value, "");
		static_assert( has_greater      <I const&>::value, "");
		static_assert( has_greater_equal<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&>::value, "");
#endif
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_view<Tuple, Tuple*>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_equal        <I const&>::value, "");
		static_assert( has_not_equal    <I const&>::value, "");
		static_assert( has_less         <I const&>::value, "");
		static_assert( has_less_equal   <I const&>::value, "");
		static_assert( has_greater      <I const&>::value, "");
		static_assert( has_greater_equal<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( has_three_way    <I const&>::value, "");
#endif
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Tuple = hamon::tuple<int, long const>;
	using V = test_input_view<Tuple>;
	using EV = hamon::ranges::elements_view<V, 0>;

	Tuple a[] =
	{
		Tuple{1,2},
		Tuple{3,4},
		Tuple{5,6},
	};
	V v(a);
	EV ev{v};

	auto it1 = ev.begin();
	auto it2 = ev.begin();
	auto it3 = ev.begin();
	auto it4 = ev.begin();
	++it3;
	++it4;

	VERIFY( (it1 == it1));
	VERIFY( (it1 == it2));
	VERIFY(!(it1 == it3));
	VERIFY(!(it1 == it4));

	VERIFY(!(it3 == it1));
	VERIFY(!(it3 == it2));
	VERIFY( (it3 == it3));
	VERIFY( (it3 == it4));

	VERIFY(!(it1 != it1));
	VERIFY(!(it1 != it2));
	VERIFY( (it1 != it3));
	VERIFY( (it1 != it4));

	VERIFY( (it3 != it1));
	VERIFY( (it3 != it2));
	VERIFY(!(it3 != it3));
	VERIFY(!(it3 != it4));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using Tuple = hamon::tuple<int, long const>;
	using V = test_random_access_view<Tuple>;
	using EV = hamon::ranges::elements_view<V, 0>;

	Tuple a[] =
	{
		Tuple{1,2},
		Tuple{3,4},
		Tuple{5,6},
	};
	V v(a);
	EV ev{v};

	auto it1 = ev.begin();
	auto it2 = ev.begin();
	auto it3 = ev.begin();
	++it2;
	++it3;
	++it3;

	VERIFY(!(it2 == it1));
	VERIFY( (it2 == it2));
	VERIFY(!(it2 == it3));

	VERIFY( (it2 != it1));
	VERIFY(!(it2 != it2));
	VERIFY( (it2 != it3));

	VERIFY(!(it2 <  it1));
	VERIFY(!(it2 <  it2));
	VERIFY( (it2 <  it3));

	VERIFY(!(it2 <= it1));
	VERIFY( (it2 <= it2));
	VERIFY( (it2 <= it3));

	VERIFY( (it2 >  it1));
	VERIFY(!(it2 >  it2));
	VERIFY(!(it2 >  it3));

	VERIFY( (it2 >= it1));
	VERIFY( (it2 >= it2));
	VERIFY(!(it2 >= it3));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using Tuple = hamon::tuple<int, long const>;
	using V = test_view<Tuple, Tuple*>;
	using EV = hamon::ranges::elements_view<V, 0>;

	Tuple a[] =
	{
		Tuple{1,2},
		Tuple{3,4},
		Tuple{5,6},
	};
	V v(a);
	EV ev{v};

	auto it1 = ev.begin();
	auto it2 = ev.begin();
	auto it3 = ev.begin();
	++it2;
	++it3;
	++it3;

	VERIFY(!(it2 == it1));
	VERIFY( (it2 == it2));
	VERIFY(!(it2 == it3));

	VERIFY( (it2 != it1));
	VERIFY(!(it2 != it2));
	VERIFY( (it2 != it3));

	VERIFY(!(it2 <  it1));
	VERIFY(!(it2 <  it2));
	VERIFY( (it2 <  it3));

	VERIFY(!(it2 <= it1));
	VERIFY( (it2 <= it2));
	VERIFY( (it2 <= it3));

	VERIFY( (it2 >  it1));
	VERIFY(!(it2 >  it2));
	VERIFY(!(it2 >  it3));

	VERIFY( (it2 >= it1));
	VERIFY( (it2 >= it2));
	VERIFY(!(it2 >= it3));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_gt(it2 <=> it1));
	VERIFY(hamon::is_eq(it2 <=> it2));
	VERIFY(hamon::is_lt(it2 <=> it3));
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace iterator_compare_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
