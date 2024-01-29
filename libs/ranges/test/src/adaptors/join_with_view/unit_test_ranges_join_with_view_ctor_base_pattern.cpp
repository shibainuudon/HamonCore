/**
 *	@file	unit_test_ranges_join_with_view_ctor_base_pattern.cpp
 *
 *	@brief	baseとpatternを受け取るコンストラクタのテスト
 *
 *	constexpr explicit join_with_view(V base, Pattern pattern);
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace ctor_base_pattern_test
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
	using InnerView = test_input_view<int>;
	using View = test_input_view<InnerView>;
	using Pattern = test_forward_view<int>;
	using JV = hamon::ranges::join_with_view<View, Pattern>;

	static_assert(hamon::is_constructible<JV, View, Pattern>::value, "");
	// TODO
	// static_assert(hamon::is_nothrow_constructible<JV, View, Pattern>::value, "");

	int a0[] = {1,2,3};
	int a1[] = {4,5};
	int a2[] = {6,7,8,9};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	int a3[] = {40,41,42};
	Pattern pat(a3);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::join_with_view jv(v, pat);
	static_assert(hamon::is_same<decltype(jv), JV>::value, "");
#else
	JV jv(v, pat);
#endif

	int expected[] = {1,2,3,40,41,42,4,5,40,41,42,6,7,8,9};
	VERIFY(hamon::ranges::equal(jv, expected));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using InnerView = test_input_view<int>;
	using View = test_forward_view<InnerView>;
	using Pattern = test_forward_view<int>;
	using JV = hamon::ranges::join_with_view<View, Pattern>;

	static_assert(hamon::is_constructible<JV, View, Pattern>::value, "");
	// TODO
	// static_assert(hamon::is_nothrow_constructible<JV, View, Pattern>::value, "");

	int a0[] = {1,2,3};
	int a1[] = {4,5};
	int a2[] = {6,7,8,9};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	int a3[] = {40,41,42};
	Pattern pat(a3);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::join_with_view jv(v, pat);
	static_assert(hamon::is_same<decltype(jv), JV>::value, "");
#else
	JV jv(v, pat);
#endif
	
	int expected[] = {1,2,3,40,41,42,4,5,40,41,42,6,7,8,9};
	VERIFY(hamon::ranges::equal(jv, expected));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using InnerView = test_input_view<int>;
	using View = test_view<InnerView, ValueForwardIterator<InnerView>>;
	using Pattern = test_forward_view<int>;
	using JV = hamon::ranges::join_with_view<View, Pattern>;

	static_assert(hamon::is_constructible<JV, View, Pattern>::value, "");
	// TODO
	// static_assert(hamon::is_nothrow_constructible<JV, View, Pattern>::value, "");

	int a0[] = {1,2,3};
	int a1[] = {4,5};
	int a2[] = {6,7,8,9};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	int a3[] = {40,41,42};
	Pattern pat(a3);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::join_with_view jv(v, pat);
	static_assert(hamon::is_same<decltype(jv), JV>::value, "");
#else
	JV jv(v, pat);
#endif
	
	int expected[] = {1,2,3,40,41,42,4,5,40,41,42,6,7,8,9};
	VERIFY(hamon::ranges::equal(jv, expected));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewCtorBasePatternTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test02());
#else
	EXPECT_TRUE(test00());
	EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
#endif
}

}	// namespace ctor_base_pattern_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
