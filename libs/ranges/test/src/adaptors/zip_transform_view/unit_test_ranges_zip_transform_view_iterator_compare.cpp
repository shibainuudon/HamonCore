/**
 *	@file	unit_test_ranges_zip_transform_view_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, const iterator& y)
 *	  requires equality_comparable<ziperator<Const>>;
 *
 *	friend constexpr auto operator<=>(const iterator& x, const iterator& y)
 *	  requires random_access_range<Base>;
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/compare/is_lt.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace iterator_compare_test
{

struct F1
{
	int operator()(int) const;
};

struct Add
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

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

template <typename T, typename Iterator, typename Sentinel, typename ConstIterator, typename ConstSentinel>
struct TestView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	HAMON_CXX11_CONSTEXPR TestView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR TestView(T (&arr)[N]) : TestView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR TestView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR Iterator      begin()       noexcept { return Iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR ConstIterator begin() const noexcept { return ConstIterator{m_first}; }
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{Iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{ConstIterator{m_last}}; }
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
		using V = test_view<int, NonComparableIterator<int>>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
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
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
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
		using V = test_forward_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
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
		using V = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
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
		using V = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
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
	{
		using V = test_contiguous_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
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
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
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
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
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
		using V1 = test_random_access_view<int>;
		using V2 = test_view<int, NonComparableIterator<int>>;
		using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
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
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V1 = test_input_view<int>;
	using V2 = test_forward_view<int>;
	using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;

	int a1[] = {3,2,1};
	int a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv{Add{}, v1, v2};

	auto it1 = zv.begin();
	auto it2 = zv.begin();
	auto it3 = zv.begin();
	auto it4 = zv.begin();
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
	using V1 = test_random_access_view<int>;
	using V2 = test_contiguous_view<int>;
	using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;

	int a1[] = {3,2,1};
	int a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv{Add{}, v1, v2};

	auto it1 = zv.begin();
	auto it2 = zv.begin();
	auto it3 = zv.begin();
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

HAMON_CXX14_CONSTEXPR bool test03()
{
	using V1 = TestView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>
	>;

	using V2 = TestView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>
	>;

	using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
	using I = decltype(hamon::declval<ZV&>().begin());
	using S = decltype(hamon::declval<ZV&>().end());

	//static_assert( hamon::is_same<I, ZV::iterator<true>>::value, "");
	//static_assert( hamon::is_same<S, ZV::iterator<true>>::value, "");
	static_assert( hamon::is_same<I, S>::value, "");

	int a1[] = { 1,2,3 };
	int a2[] = { 4,5 };
	V1 v1(a1);
	V2 v2(a2);
	ZV zv{Add{}, v1, v2};
	I i = zv.begin();
	S s = zv.end();
	VERIFY(i != s);
	++i;
	VERIFY(i != s);
	++i;
	VERIFY(i == s);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace iterator_compare_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
