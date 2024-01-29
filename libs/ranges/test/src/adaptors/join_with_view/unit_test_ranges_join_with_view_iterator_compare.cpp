/**
 *	@file	unit_test_ranges_join_with_view_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, const iterator& y)
 *	  requires ref-is-glvalue && forward_range<Base> &&
 *	    equality_comparable<InnerIter>;
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace iterator_compare_test
{

template <typename T>
struct ValueForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	HAMON_CXX14_CONSTEXPR ValueForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueForwardIterator& rhs) const { return !(*this == rhs); }
};

template <typename T>
struct NonComparableForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	HAMON_CXX14_CONSTEXPR NonComparableForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR NonComparableForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T operator*() const { return *m_ptr; }
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(has_equal<I>::value, "");
		static_assert(has_not_equal<I>::value, "");
	}
	{
		using InnerView = test_view<int, input_iterator_wrapper<int>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(has_equal<I>::value, "");
		static_assert(has_not_equal<I>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using V = test_view<InnerView, input_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_equal<I>::value, "");
		static_assert(!has_not_equal<I>::value, "");
	}
	{
		using InnerView = test_view<int, ValueForwardIterator<int>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(has_equal<I>::value, "");
		static_assert(has_not_equal<I>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using V = test_view<InnerView, ValueForwardIterator<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_equal<I>::value, "");
		static_assert(!has_not_equal<I>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, ValueForwardIterator<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(has_equal<I>::value, "");
		static_assert(has_not_equal<I>::value, "");
	}
	{
		using InnerView = test_view<int, NonComparableForwardIterator<int>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_equal<I>::value, "");
		static_assert(!has_not_equal<I>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using InnerView = test_forward_view<int>;
	using View = test_forward_view<InnerView>;
	using Pattern = test_forward_view<int>;
	using JV = hamon::ranges::join_with_view<View, Pattern>;

	int a0[] = {1};
	int a1[] = {2,3};
	int a2[] = {4,5,6};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	int a3[] = {-1,-2};
	Pattern pat(a3);
	
	JV jv(v, pat);

	auto it1 = jv.begin();
	auto it2 = jv.begin();
	auto it3 = hamon::ranges::next(jv.begin(), 1);
	auto it4 = hamon::ranges::next(jv.begin(), 1);
	auto it5 = hamon::ranges::next(jv.begin(), 2);
	auto it6 = hamon::ranges::next(jv.begin(), 2);

	VERIFY( (it1 == it1));
	VERIFY( (it1 == it2));
	VERIFY(!(it1 == it3));
	VERIFY(!(it1 == it4));
	VERIFY(!(it1 == it5));
	VERIFY(!(it1 == it6));

	VERIFY(!(it3 == it1));
	VERIFY(!(it3 == it2));
	VERIFY( (it3 == it3));
	VERIFY( (it3 == it4));
	VERIFY(!(it3 == it5));
	VERIFY(!(it3 == it6));

	VERIFY(!(it5 == it1));
	VERIFY(!(it5 == it2));
	VERIFY(!(it5 == it3));
	VERIFY(!(it5 == it4));
	VERIFY( (it5 == it5));
	VERIFY( (it5 == it6));

	VERIFY(!(it1 != it1));
	VERIFY(!(it1 != it2));
	VERIFY( (it1 != it3));
	VERIFY( (it1 != it4));
	VERIFY( (it1 != it5));
	VERIFY( (it1 != it6));

	VERIFY( (it3 != it1));
	VERIFY( (it3 != it2));
	VERIFY(!(it3 != it3));
	VERIFY(!(it3 != it4));
	VERIFY( (it3 != it5));
	VERIFY( (it3 != it6));

	VERIFY( (it5 != it1));
	VERIFY( (it5 != it2));
	VERIFY( (it5 != it3));
	VERIFY( (it5 != it4));
	VERIFY(!(it5 != it5));
	VERIFY(!(it5 != it6));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace iterator_compare_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
