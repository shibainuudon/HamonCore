/**
 *	@file	unit_test_ranges_join_with_view_iterator_post_increment.cpp
 *
 *	@brief	後置インクリメントのテスト
 *
 *	constexpr void operator++(int);
 *	constexpr iterator operator++(int)
 *	  requires ref-is-glvalue && forward_iterator<OuterIter> &&
 *	    forward_iterator<InnerIter>;
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace iterator_post_increment_test
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
	HAMON_CXX11_CONSTEXPR ValueForwardIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ValueForwardIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ValueForwardIterator(ValueForwardIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ValueForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueForwardIterator& rhs) const { return !(*this == rhs); }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	{
		using InnerView = test_view<int, input_iterator_wrapper<int>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using V = test_view<InnerView, input_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");
	}
	{
		using InnerView = test_view<int, ValueForwardIterator<int>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using V = test_view<InnerView, ValueForwardIterator<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using InnerView = test_forward_view<int>;
	using View = test_forward_view<InnerView>;
	using Pattern = test_forward_view<int>;
	using JV = hamon::ranges::join_with_view<View, Pattern>;

	int a0[] = {1,2,3};
	int a1[] = {4,5};
	int a2[] = {6,7,8,9};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	int a3[] = {-1,-2};
	Pattern pat(a3);

	JV jv(v, pat);
	auto it = jv.begin();
	VERIFY(*it == 1);
	auto t1 = it++;
	VERIFY(*it == 2);
	VERIFY(*t1 == 1);
	auto t2 = it++;
	VERIFY(*it == 3);
	VERIFY(*t2 == 2);
	auto t3 = it++;
	VERIFY(*it == -1);
	VERIFY(*t3 == 3);
	auto t4 = it++;
	VERIFY(*it == -2);
	VERIFY(*t4 == -1);
	auto t5 = it++;
	VERIFY(*it == 4);
	VERIFY(*t5 == -2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using InnerView = test_input_view<int>;
	using View = test_forward_view<InnerView>;
	using Pattern = test_forward_view<int>;
	using JV = hamon::ranges::join_with_view<View, Pattern>;

	int a0[] = {1,2,3};
	int a1[] = {4,5};
	int a2[] = {6,7,8,9};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	int a3[] = {-1,-2};
	Pattern pat(a3);

	JV jv(v, pat);
	auto it = jv.begin();
	VERIFY(*it == 1);
	it++;
	VERIFY(*it == 2);
	it++;
	VERIFY(*it == 3);
	it++;
	VERIFY(*it == -1);
	it++;
	VERIFY(*it == -2);
	it++;
	VERIFY(*it == 4);
	it++;
	VERIFY(*it == 5);
	it++;
	VERIFY(*it == -1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewIteratorPostIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test02());
#else
	EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
#endif
}

}	// namespace iterator_post_increment_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
