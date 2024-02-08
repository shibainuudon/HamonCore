﻿/**
 *	@file	unit_test_ranges_elements_view_iterator_ctor_conv.cpp
 *
 *	@brief	iterator<!Const>を引数に取るコンストラクタのテスト
 *
 *	constexpr iterator(iterator<!Const> i)
 *	  requires Const && convertible_to<iterator_t<V>, iterator_t<Base>>;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace iterator_ctor_conv_test
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
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{m_last}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{m_last}; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple const>,
			input_iterator_wrapper<Tuple const>
		>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I  = decltype(hamon::declval<EV&>().begin());
		using CI = decltype(hamon::declval<EV const&>().begin());
		static_assert(!hamon::is_constructible<I, CI>::value, "");
		static_assert(!hamon::is_constructible<CI, I>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			ConvertibleForwardIterator<Tuple>,
			ConvertibleForwardIterator<Tuple>,
			ConvertibleForwardIterator<Tuple const>,
			ConvertibleForwardIterator<Tuple const>
		>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I  = decltype(hamon::declval<EV&>().begin());
		using CI = decltype(hamon::declval<EV const&>().begin());
		static_assert(!hamon::is_constructible<I, CI>::value, "");
		static_assert( hamon::is_constructible<CI, I>::value, "");
		static_assert( hamon::is_implicitly_constructible<CI, I>::value, "");
		
		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev(v);
		CI it = ev.begin();
		VERIFY(*it == 1);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewIteratorCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_ctor_conv_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
