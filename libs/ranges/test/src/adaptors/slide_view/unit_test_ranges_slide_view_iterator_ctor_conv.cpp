/**
 *	@file	unit_test_ranges_slide_view_iterator_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	constexpr iterator(iterator<!Const> i)
 *	  requires Const && convertible_to<iterator_t<V>, iterator_t<Base>>;
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace slide_view_test
{
namespace iterator_ctor_conv_test
{

template <typename T>
struct ConvertibleRandomAccessIterator
{
	T*	m_ptr;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR ConvertibleRandomAccessIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ConvertibleRandomAccessIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ConvertibleRandomAccessIterator(ConvertibleRandomAccessIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ConvertibleRandomAccessIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ConvertibleRandomAccessIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR ConvertibleRandomAccessIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
	HAMON_CXX11_CONSTEXPR ConvertibleRandomAccessIterator  operator+(difference_type n) const { return ConvertibleRandomAccessIterator{m_ptr + n}; }
	HAMON_CXX14_CONSTEXPR ConvertibleRandomAccessIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ConvertibleRandomAccessIterator  operator--(int) { auto t = *this; --m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR ConvertibleRandomAccessIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
	HAMON_CXX11_CONSTEXPR ConvertibleRandomAccessIterator  operator-(difference_type n) const { return {m_ptr - n}; }
	HAMON_CXX11_CONSTEXPR difference_type                 operator-(ConvertibleRandomAccessIterator const& rhs) const { return m_ptr - rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                              operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                              operator[](difference_type i) const { return m_ptr[i]; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ConvertibleRandomAccessIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ConvertibleRandomAccessIterator& rhs) const { return m_ptr != rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator< (const ConvertibleRandomAccessIterator& rhs) const { return m_ptr <  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator> (const ConvertibleRandomAccessIterator& rhs) const { return m_ptr >  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator<=(const ConvertibleRandomAccessIterator& rhs) const { return m_ptr <= rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator>=(const ConvertibleRandomAccessIterator& rhs) const { return m_ptr >= rhs.m_ptr; }
};

template <typename T>
HAMON_CXX14_CONSTEXPR ConvertibleRandomAccessIterator<T>
operator+(hamon::ptrdiff_t, ConvertibleRandomAccessIterator<T> const&);

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
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int const>,
			random_access_iterator_wrapper<int const>
		>;
		using SV = hamon::ranges::slide_view<V>;
		using I  = decltype(hamon::declval<SV&>().begin());
		using CI = decltype(hamon::declval<SV const&>().begin());
		static_assert(!hamon::is_constructible<I, CI>::value, "");
		static_assert(!hamon::is_constructible<CI, I>::value, "");
	}
	{
		using V = TestView<int,
			ConvertibleRandomAccessIterator<int>,
			ConvertibleRandomAccessIterator<int>,
			ConvertibleRandomAccessIterator<int const>,
			ConvertibleRandomAccessIterator<int const>
		>;
		using SV = hamon::ranges::slide_view<V>;
		using I  = decltype(hamon::declval<SV&>().begin());
		using CI = decltype(hamon::declval<SV const&>().begin());
		static_assert(!hamon::is_constructible<I, CI>::value, "");
		static_assert( hamon::is_constructible<CI, I>::value, "");
		static_assert( hamon::is_implicitly_constructible<CI, I>::value, "");

		int a[] = {1,2,3,4};
		V v(a);
		SV sv(v, 3);
		CI it = sv.begin();
		int const expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(*it, expected));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewIteratorCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_ctor_conv_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
