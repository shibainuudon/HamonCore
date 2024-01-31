/**
 *	@file	unit_test_ranges_lazy_split_view_outer_iterator_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	constexpr outer-iterator(outer-iterator<!Const> i)
 *	  requires Const && convertible_to<iterator_t<V>, iterator_t<Base>>;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace outer_iterator_ctor_conv_test
{

template <typename T>
struct ConvertibleForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator(ConvertibleForwardIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ConvertibleForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ConvertibleForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T& operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ConvertibleForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ConvertibleForwardIterator& rhs) const { return !(*this == rhs); }
};

template <
	typename T,
	typename Iterator,
	typename ConstIterator,
	typename Sentinel = test_sentinel<Iterator>,
	typename ConstSentinel = test_sentinel<ConstIterator>
>
struct NotSimpleView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	using iterator = Iterator;
	using const_iterator = ConstIterator;
	using sentinel = Sentinel;
	using const_sentinel = ConstSentinel;

	HAMON_CXX11_CONSTEXPR NotSimpleView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR NotSimpleView(T (&arr)[N]) : NotSimpleView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR NotSimpleView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return sentinel{iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return const_sentinel{const_iterator{m_last}}; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = NotSimpleView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int const>>;
	using P = NotSimpleView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using I  = decltype(hamon::declval<RV&>().begin());
	using CI = decltype(hamon::declval<RV const&>().begin());
	static_assert(!hamon::is_same<I, CI>::value, "");
	static_assert(!hamon::is_constructible<I, CI>::value, "");
	static_assert(!hamon::is_constructible<CI, I>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = NotSimpleView<int,
		ConvertibleForwardIterator<int>,
		ConvertibleForwardIterator<int const>>;
	using P = NotSimpleView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using I  = decltype(hamon::declval<RV&>().begin());
	using CI = decltype(hamon::declval<RV const&>().begin());
	static_assert(!hamon::is_same<I, CI>::value, "");
	static_assert(!hamon::is_constructible<I, CI>::value, "");
	static_assert( hamon::is_constructible<CI, I>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	RV const& crv = rv;

	CI i = rv.begin();
	VERIFY(i == crv.begin());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewOuterIteratorCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace outer_iterator_ctor_conv_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
