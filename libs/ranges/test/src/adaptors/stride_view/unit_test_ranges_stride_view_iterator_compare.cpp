/**
 *	@file	unit_test_ranges_stride_view_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, default_sentinel_t);
 *
 *	friend constexpr bool operator==(const iterator& x, const iterator& y)
 *	  requires equality_comparable<iterator_t<Base>>;
 *
 *	friend constexpr bool operator<(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base>;
 *
 *	friend constexpr bool operator>(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base>;
 *
 *	friend constexpr bool operator<=(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base>;
 *
 *	friend constexpr bool operator>=(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base>;
 *
 *	friend constexpr auto operator<=>(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base> && three_way_comparable<iterator_t<Base>>;
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
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

namespace hamon_ranges_test
{
namespace stride_view_test
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

template <typename T, typename U, typename = void>
struct has_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_not_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_not_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_less
	: public hamon::false_type {};

template <typename T, typename U>
struct has_less<T, U, hamon::void_t<decltype(hamon::declval<T>() < hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_less_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_less_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() <= hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_greater
	: public hamon::false_type {};

template <typename T, typename U>
struct has_greater<T, U, hamon::void_t<decltype(hamon::declval<T>() > hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_greater_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_greater_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() >= hamon::declval<U>())>>
	: public hamon::true_type {};

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename U, typename = void>
struct has_three_way
	: public hamon::false_type {};

template <typename T, typename U>
struct has_three_way<T, U, hamon::void_t<decltype(hamon::declval<T>() <=> hamon::declval<U>())>>
	: public hamon::true_type {};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_view<int, NonComparableIterator<int>>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_equal        <I const&, I const&>::value, "");
		static_assert(!has_not_equal    <I const&, I const&>::value, "");
		static_assert(!has_less         <I const&, I const&>::value, "");
		static_assert(!has_less_equal   <I const&, I const&>::value, "");
		static_assert(!has_greater      <I const&, I const&>::value, "");
		static_assert(!has_greater_equal<I const&, I const&>::value, "");

		static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less         <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less_equal   <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater      <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater_equal<I const&, hamon::default_sentinel_t>::value, "");

		static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less         <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less_equal   <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater      <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater_equal<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&, I const&>::value, "");
		static_assert(!has_three_way    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_three_way    <hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_input_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_equal        <I const&, I const&>::value, "");
		static_assert( has_not_equal    <I const&, I const&>::value, "");
		static_assert(!has_less         <I const&, I const&>::value, "");
		static_assert(!has_less_equal   <I const&, I const&>::value, "");
		static_assert(!has_greater      <I const&, I const&>::value, "");
		static_assert(!has_greater_equal<I const&, I const&>::value, "");

		static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less         <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less_equal   <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater      <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater_equal<I const&, hamon::default_sentinel_t>::value, "");

		static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less         <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less_equal   <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater      <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater_equal<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&, I const&>::value, "");
		static_assert(!has_three_way    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_three_way    <hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_equal        <I const&, I const&>::value, "");
		static_assert( has_not_equal    <I const&, I const&>::value, "");
		static_assert(!has_less         <I const&, I const&>::value, "");
		static_assert(!has_less_equal   <I const&, I const&>::value, "");
		static_assert(!has_greater      <I const&, I const&>::value, "");
		static_assert(!has_greater_equal<I const&, I const&>::value, "");

		static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less         <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less_equal   <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater      <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater_equal<I const&, hamon::default_sentinel_t>::value, "");

		static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less         <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less_equal   <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater      <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater_equal<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&, I const&>::value, "");
		static_assert(!has_three_way    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_three_way    <hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_equal        <I const&, I const&>::value, "");
		static_assert( has_not_equal    <I const&, I const&>::value, "");
		static_assert(!has_less         <I const&, I const&>::value, "");
		static_assert(!has_less_equal   <I const&, I const&>::value, "");
		static_assert(!has_greater      <I const&, I const&>::value, "");
		static_assert(!has_greater_equal<I const&, I const&>::value, "");

		static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less         <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less_equal   <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater      <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater_equal<I const&, hamon::default_sentinel_t>::value, "");

		static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less         <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less_equal   <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater      <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater_equal<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&, I const&>::value, "");
		static_assert(!has_three_way    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_three_way    <hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_equal        <I const&, I const&>::value, "");
		static_assert( has_not_equal    <I const&, I const&>::value, "");
		static_assert( has_less         <I const&, I const&>::value, "");
		static_assert( has_less_equal   <I const&, I const&>::value, "");
		static_assert( has_greater      <I const&, I const&>::value, "");
		static_assert( has_greater_equal<I const&, I const&>::value, "");

		static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less         <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less_equal   <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater      <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater_equal<I const&, hamon::default_sentinel_t>::value, "");

		static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less         <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less_equal   <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater      <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater_equal<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&, I const&>::value, "");
		static_assert(!has_three_way    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_three_way    <hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_contiguous_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_equal        <I const&, I const&>::value, "");
		static_assert( has_not_equal    <I const&, I const&>::value, "");
		static_assert( has_less         <I const&, I const&>::value, "");
		static_assert( has_less_equal   <I const&, I const&>::value, "");
		static_assert( has_greater      <I const&, I const&>::value, "");
		static_assert( has_greater_equal<I const&, I const&>::value, "");

		static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less         <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less_equal   <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater      <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater_equal<I const&, hamon::default_sentinel_t>::value, "");

		static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less         <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less_equal   <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater      <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater_equal<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_three_way    <I const&, I const&>::value, "");
		static_assert(!has_three_way    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_three_way    <hamon::default_sentinel_t, I const&>::value, "");
#endif
	}
	{
		using V = test_view<int, int*>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_equal        <I const&, I const&>::value, "");
		static_assert( has_not_equal    <I const&, I const&>::value, "");
		static_assert( has_less         <I const&, I const&>::value, "");
		static_assert( has_less_equal   <I const&, I const&>::value, "");
		static_assert( has_greater      <I const&, I const&>::value, "");
		static_assert( has_greater_equal<I const&, I const&>::value, "");

		static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less         <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_less_equal   <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater      <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_greater_equal<I const&, hamon::default_sentinel_t>::value, "");

		static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less         <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_less_equal   <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater      <hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_greater_equal<hamon::default_sentinel_t, I const&>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( has_three_way    <I const&, I const&>::value, "");
		static_assert(!has_three_way    <I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_three_way    <hamon::default_sentinel_t, I const&>::value, "");
#endif
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_input_view<int>;
	using SV = hamon::ranges::stride_view<V>;

	int a[] = {1,2,3,4,5,6,7,8,9};
	V v(a);
	SV sv{v, 2};

	auto it1 = sv.begin();
	auto it2 = sv.begin();
	auto it3 = sv.begin();
	auto it4 = sv.begin();
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
	using V = test_random_access_view<int>;
	using SV = hamon::ranges::stride_view<V>;

	int a[] = {1,2,3,4,5,6,7,8,9};
	V v(a);
	SV sv{v, 3};

	auto it1 = sv.begin();
	auto it2 = sv.begin();
	auto it3 = sv.begin();
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
	using V = test_view<int, int*>;
	using SV = hamon::ranges::stride_view<V>;

	int a[] = {1,2,3,4,5,6,7,8,9};
	V v(a);
	SV sv{v, 4};

	auto it1 = sv.begin();
	auto it2 = sv.begin();
	auto it3 = sv.begin();
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

GTEST_TEST(RangesTest, StrideViewIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace iterator_compare_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
