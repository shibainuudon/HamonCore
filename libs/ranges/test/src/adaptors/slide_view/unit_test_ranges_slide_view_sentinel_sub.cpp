/**
 *	@file	unit_test_ranges_slide_view_sentinel_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	friend constexpr range_difference_t<V>
 *	  operator-(const iterator<false>& x, const sentinel& y)
 *	    requires sized_sentinel_for<sentinel_t<V>, iterator_t<V>>;
 *	
 *	friend constexpr range_difference_t<V>
 *	  operator-(const sentinel& y, const iterator<false>& x)
 *	    requires sized_sentinel_for<sentinel_t<V>, iterator_t<V>>;
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace slide_view_test
{
namespace sentinel_sub_test
{

template <typename T>
struct SizedForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR SizedForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR SizedForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR SizedForwardIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
	HAMON_CXX11_CONSTEXPR SizedForwardIterator  operator+(difference_type n) const { return {m_ptr + n}; }
	HAMON_CXX14_CONSTEXPR SizedForwardIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR SizedForwardIterator  operator--(int) { auto t = *this; --m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR SizedForwardIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
	HAMON_CXX11_CONSTEXPR SizedForwardIterator  operator-(difference_type n) const { return {m_ptr - n}; }
	HAMON_CXX11_CONSTEXPR difference_type       operator-(SizedForwardIterator const& rhs) const { return m_ptr - rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                    operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                    operator[](difference_type i) const { return m_ptr[i]; }
	HAMON_CXX11_CONSTEXPR bool operator==(const SizedForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const SizedForwardIterator& rhs) const { return m_ptr != rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator< (const SizedForwardIterator& rhs) const { return m_ptr <  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator> (const SizedForwardIterator& rhs) const { return m_ptr >  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator<=(const SizedForwardIterator& rhs) const { return m_ptr <= rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator>=(const SizedForwardIterator& rhs) const { return m_ptr >= rhs.m_ptr; }
};

template <typename T>
HAMON_CXX14_CONSTEXPR SizedForwardIterator<T>
operator+(hamon::ptrdiff_t, SizedForwardIterator<T> const&);

template <typename Iterator>
struct TestSentinel
{
	Iterator m_it;

	HAMON_CONSTEXPR bool
	operator==(TestSentinel const& i) const noexcept
	{
		return base(m_it) == base(i.m_it);
	}

	HAMON_CONSTEXPR bool
	operator==(Iterator const& i) const noexcept
	{
		return base(m_it) == base(i);
	}

	HAMON_CONSTEXPR bool
	operator!=(Iterator const& i) const noexcept
	{
		return !(*this == i);
	}
};

template <typename Iterator>
HAMON_CONSTEXPR bool
operator==(Iterator const& i, TestSentinel<Iterator> const& s) noexcept
{
	return s == i;
}

template <typename Iterator>
HAMON_CONSTEXPR bool
operator!=(Iterator const& i, TestSentinel<Iterator> const& s) noexcept
{
	return !(i == s);
}

template <typename Iterator>
HAMON_CONSTEXPR auto
operator-(TestSentinel<Iterator> const& s, Iterator const& i) noexcept
->decltype(base(s.m_it) - base(i))
{
	return base(s.m_it) - base(i);
}

template <typename Iterator>
HAMON_CONSTEXPR auto
operator-(Iterator const& i, TestSentinel<Iterator> const& s) noexcept
->decltype(base(i) - base(s.m_it))
{
	return base(i) - base(s.m_it);
}

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

template <typename T, typename U, typename = void>
struct has_sub
	: public hamon::false_type {};

template <typename T, typename U>
struct has_sub<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// iterator<true>, sentinel
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>
		>;

		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV const&>().begin());
		using S = decltype(hamon::declval<SV&>().end());
		//static_assert(hamon::is_same<I, SV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, SV::sentinel>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}

	// iterator<false>, sentinel
	{
		using V = TestView<int,
			SizedForwardIterator<int>,
			TestSentinel<SizedForwardIterator<int>>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>
		>;

		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		using S = decltype(hamon::declval<SV&>().end());
		//static_assert(hamon::is_same<I, SV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, SV::sentinel>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		SV sv{v, 3};
		I i = sv.begin();
		S s = sv.end();

		VERIFY(i - s == -3);
		VERIFY(s - i ==  3);

		++i;

		VERIFY(i - s == -2);
		VERIFY(s - i ==  2);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewSentinelSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace sentinel_sub_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
