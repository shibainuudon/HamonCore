/**
 *	@file	unit_test_ranges_lazy_split_view_inner_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr decltype(auto) operator*() const;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace inner_iterator_dereference_test
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
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter = hamon::ranges::iterator_t<RV>;
	using InnerRng = decltype(*hamon::declval<OuterIter&>());
	using I = decltype(hamon::declval<InnerRng&>().begin());

	static_assert(hamon::is_same<int&, decltype(*hamon::declval<I const&>())>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	auto inner = *i;
	auto ii = inner.begin();
	VERIFY(*ii == 1);

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

	static_assert(hamon::is_same<int const&, decltype(*hamon::declval<I const&>())>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	auto inner = *i;
	auto ii = inner.begin();
	VERIFY(*ii == 1);

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

	static_assert(hamon::is_same<int, decltype(*hamon::declval<I const&>())>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	auto inner = *i;
	auto ii = inner.begin();
	VERIFY(*ii == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewInnerIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace inner_iterator_dereference_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
