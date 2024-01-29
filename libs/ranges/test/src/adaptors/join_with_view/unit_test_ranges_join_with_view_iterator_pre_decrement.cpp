/**
 *	@file	unit_test_ranges_join_with_view_iterator_pre_decrement.cpp
 *
 *	@brief	前置デクリメントのテスト
 *
 *	constexpr iterator& operator--()
 *	  requires ref-is-glvalue && bidirectional_range<Base> &&
 *	    bidirectional-common<InnerBase> && bidirectional-common<PatternBase>;
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace iterator_pre_decrement_test
{

template <typename T>
struct ValueBidirectionalIterator
{
	T*	m_ptr;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator  operator--(int);
	HAMON_CXX11_CONSTEXPR T                           operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueBidirectionalIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueBidirectionalIterator& rhs) const { return !(*this == rhs); }
};

template <typename T, typename = void>
struct has_pre_decrement
	: public hamon::false_type {};

template <typename T>
struct has_pre_decrement<T, hamon::void_t<decltype(--hamon::declval<T>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using V = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(has_pre_decrement<I&>::value, "");
		static_assert(hamon::is_same<decltype(--hamon::declval<I&>()), I&>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>>;
		using V = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_pre_decrement<I&>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using V = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_pre_decrement<I&>::value, "");
	}
	{
		using InnerView = test_view<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using V = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_pre_decrement<I&>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using V = test_view<InnerView,
			forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_pre_decrement<I&>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using V = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_pre_decrement<I&>::value, "");
	}
	{
		using InnerView = test_view<int,
			ValueBidirectionalIterator<int>,
			ValueBidirectionalIterator<int>>;
		using V = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(has_pre_decrement<I&>::value, "");
		static_assert(hamon::is_same<decltype(--hamon::declval<I&>()), I&>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using V = test_view<InnerView,
			ValueBidirectionalIterator<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_pre_decrement<I&>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using V = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			ValueBidirectionalIterator<int>,
			ValueBidirectionalIterator<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(has_pre_decrement<I&>::value, "");
		static_assert(hamon::is_same<decltype(--hamon::declval<I&>()), I&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using InnerView = test_view<int,
		bidirectional_iterator_wrapper<int>,
		bidirectional_iterator_wrapper<int>>;
	using View = test_view<InnerView,
		bidirectional_iterator_wrapper<InnerView>,
		bidirectional_iterator_wrapper<InnerView>>;
	using Pattern = test_view<int,
		bidirectional_iterator_wrapper<int>,
		bidirectional_iterator_wrapper<int>>;
	using JV = hamon::ranges::join_with_view<View, Pattern>;

	int a0[] = {1,2,3};
	int a1[] = {4,5};
	int a2[] = {6,7,8,9};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	int a3[] = {-1,-2};
	Pattern pat(a3);

	JV jv(v, pat);
	auto it = jv.end();
	auto& t1 = --it;
	VERIFY(*it == 9);
	VERIFY(&t1 == &it);
	auto& t2 = --it;
	VERIFY(*it == 8);
	VERIFY(&t2 == &it);
	VERIFY(*--it == 7);
	VERIFY(*--it == 6);
	VERIFY(*--it == -2);
	VERIFY(*--it == -1);
	VERIFY(*--it == 5);
	VERIFY(*--it == 4);
	VERIFY(*--it == -2);
	VERIFY(*--it == -1);
	VERIFY(*--it == 3);
	VERIFY(*--it == 2);
	VERIFY(*--it == 1);
	VERIFY(it == jv.begin());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewIteratorPreDecrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace iterator_pre_decrement_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
