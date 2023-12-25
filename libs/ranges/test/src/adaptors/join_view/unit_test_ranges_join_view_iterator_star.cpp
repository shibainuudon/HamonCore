/**
 *	@file	unit_test_ranges_join_view_iterator_star.cpp
 *
 *	@brief	operator*のテスト
 *
 *	constexpr decltype(auto) operator*() const;
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace iterator_star_test
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
	int a[2][3] =
	{
		{1, 2, 3},
		{4, 5, 6},
	};
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::join_view rv(a);
	static_assert(hamon::is_same<decltype(rv), hamon::ranges::join_view<hamon::ranges::ref_view<int[2][3]>>>::value, "");
#else
	hamon::ranges::join_view<hamon::ranges::ref_view<int[2][3]>> rv(a);
#endif
	auto it = rv.begin();
	static_assert(hamon::is_same<decltype(*it), int&>::value, "");
	VERIFY(*it == 1);
	*it = 2;
	VERIFY(*it == 2);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int const a[2][3] =
	{
		{1, 2, 3},
		{4, 5, 6},
	};
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::join_view rv(a);
	static_assert(hamon::is_same<decltype(rv), hamon::ranges::join_view<hamon::ranges::ref_view<int const[2][3]>>>::value, "");
#else
	hamon::ranges::join_view<hamon::ranges::ref_view<int const[2][3]>> rv(a);
#endif
	auto it = rv.begin();
	static_assert(hamon::is_same<decltype(*it), int const&>::value, "");
	VERIFY(*it == 1);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a0[] = {11,12};
	int a1[] = {13,14,15};
	int a2[] = {16};
	using InnerView = test_input_view<int>;
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	using View = test_input_view<InnerView>;
	View v(iv);
	hamon::ranges::join_view<View> rv(v);
	auto it = rv.begin();
	static_assert(hamon::is_same<decltype(*it), int&>::value, "");
	VERIFY(*it == 11);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a0[] = {21,22};
	int a1[] = {23,24,25};
	int a2[] = {26};
	using InnerView = test_view<int, ValueForwardIterator<int>>;
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	using View = test_input_view<InnerView>;
	View v(iv);
	hamon::ranges::join_view<View> rv(v);
	auto it = rv.begin();
	static_assert(hamon::is_same<decltype(*it), int>::value, "");
	VERIFY(*it == 21);
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewIteratorStarTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test00());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace iterator_star_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
