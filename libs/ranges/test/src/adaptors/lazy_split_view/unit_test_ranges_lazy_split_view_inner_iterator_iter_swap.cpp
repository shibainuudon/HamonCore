/**
 *	@file	unit_test_ranges_lazy_split_view_inner_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 *
 *	friend constexpr void iter_swap(const inner-iterator& x, const inner-iterator& y);
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace inner_iterator_iter_swap_test
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

template <typename T, typename = void>
struct has_iter_swap
	: public hamon::false_type {};

template <typename T>
struct has_iter_swap<T, hamon::void_t<decltype(hamon::ranges::iter_swap(hamon::declval<T>(), hamon::declval<T>()))>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter = hamon::ranges::iterator_t<RV>;
	using InnerRng = decltype(*hamon::declval<OuterIter&>());
	using I = decltype(hamon::declval<InnerRng&>().begin());

	static_assert(has_iter_swap<I const&>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	auto inner = *i;
	auto ii1 = inner.begin();
	auto ii2 = inner.begin();
	ii2++;
	hamon::ranges::iter_swap(ii1, ii2);
	VERIFY(a1[0] == 2);
	VERIFY(a1[1] == 1);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_view<int const>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter = hamon::ranges::iterator_t<RV>;
	using InnerRng = decltype(*hamon::declval<OuterIter&>());
	using I = decltype(hamon::declval<InnerRng&>().begin());

	static_assert(!has_iter_swap<I const&>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V = test_view<int, ValueForwardIterator<int>>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter = hamon::ranges::iterator_t<RV>;
	using InnerRng = decltype(*hamon::declval<OuterIter&>());
	using I = decltype(hamon::declval<InnerRng&>().begin());

	static_assert(!has_iter_swap<I const&>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewInnerIteratorIterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace inner_iterator_iter_swap_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
