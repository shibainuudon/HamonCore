/**
 *	@file	unit_test_ranges_stride_view_iterator_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	friend constexpr iterator operator-(const iterator& x, difference_type n)
 *	  requires random_access_range<Base>;
 *	friend constexpr difference_type operator-(const iterator& x, const iterator& y)
 *	  requires sized_sentinel_for<iterator_t<Base>, iterator_t<Base>>;
 *
 *	friend constexpr difference_type operator-(default_sentinel_t y, const iterator& x)
 *	  requires sized_sentinel_for<sentinel_t<Base>, iterator_t<Base>>;
 *	friend constexpr difference_type operator-(const iterator& x, default_sentinel_t y)
 *	  requires sized_sentinel_for<sentinel_t<Base>, iterator_t<Base>>;
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace iterator_sub_test
{

template <typename T>
struct SizedInputIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR SizedInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR SizedInputIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR SizedInputIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
	HAMON_CXX11_CONSTEXPR SizedInputIterator  operator+(difference_type n) const { return {m_ptr + n}; }
	HAMON_CXX14_CONSTEXPR SizedInputIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR SizedInputIterator  operator--(int) { auto t = *this; --m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR SizedInputIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
	HAMON_CXX11_CONSTEXPR SizedInputIterator  operator-(difference_type n) const { return {m_ptr - n}; }
	HAMON_CXX11_CONSTEXPR difference_type     operator-(SizedInputIterator const& rhs) const { return m_ptr - rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                  operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                  operator[](difference_type i) const { return m_ptr[i]; }
	HAMON_CXX11_CONSTEXPR bool operator==(const SizedInputIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const SizedInputIterator& rhs) const { return m_ptr != rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator< (const SizedInputIterator& rhs) const { return m_ptr <  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator> (const SizedInputIterator& rhs) const { return m_ptr >  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator<=(const SizedInputIterator& rhs) const { return m_ptr <= rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator>=(const SizedInputIterator& rhs) const { return m_ptr >= rhs.m_ptr; }
};

template <typename T>
HAMON_CXX14_CONSTEXPR SizedInputIterator<T>
operator+(hamon::ptrdiff_t, SizedInputIterator<T> const&);

template <typename T, typename U, typename = void>
struct has_sub
	: public hamon::false_type {};

template <typename T, typename U>
struct has_sub<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
		static_assert(!has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_sub<I const&, hamon::default_sentinel_t>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
		static_assert(!has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_sub<I const&, hamon::default_sentinel_t>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
		static_assert(!has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(!has_sub<I const&, hamon::default_sentinel_t>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_view<int, SizedInputIterator<int>, SizedInputIterator<int>>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), hamon::ptrdiff_t>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::stride_view<V>;

		int a[] = {10,20,30,40,50,60,70,80,90};
		V v(a);
		SV sv{v, 2};

		auto it1 = sv.begin() + 2;
		auto it2 = it1 - 1;
		auto it3 = it1 - 2;
		VERIFY(*it1 == 50);
		VERIFY(*it2 == 30);
		VERIFY(*it3 == 10);
		VERIFY((it1 - it1) ==  0);
		VERIFY((it1 - it2) ==  1);
		VERIFY((it1 - it3) ==  2);
		VERIFY((it3 - it1) == -2);
		VERIFY((it3 - it2) == -1);
		VERIFY((it3 - it3) ==  0);
		VERIFY((hamon::default_sentinel - it1) == 3);
		VERIFY((hamon::default_sentinel - it2) == 4);
		VERIFY((hamon::default_sentinel - it3) == 5);
		VERIFY((it1 - hamon::default_sentinel) == -3);
		VERIFY((it2 - hamon::default_sentinel) == -4);
		VERIFY((it3 - hamon::default_sentinel) == -5);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		using V = test_view<int, SizedInputIterator<int>, SizedInputIterator<int>>;
		using SV = hamon::ranges::stride_view<V>;

		int a[] = {10,20,30,40,50,60,70,80,90};
		V v(a);
		SV sv{v, 3};

		auto it1 = sv.begin();
		auto it2 = sv.begin();
		auto it3 = sv.begin();
		++it2;
		++it3;
		++it3;
		VERIFY(*it1 == 10);
		VERIFY(*it2 == 40);
		VERIFY(*it3 == 70);
		VERIFY((it1 - it1) ==  0);
		VERIFY((it1 - it2) == -1);
		VERIFY((it1 - it3) == -2);
		VERIFY((it3 - it1) ==  2);
		VERIFY((it3 - it2) ==  1);
		VERIFY((it3 - it3) ==  0);
		VERIFY((hamon::default_sentinel - it1) == 3);
		VERIFY((hamon::default_sentinel - it2) == 2);
		VERIFY((hamon::default_sentinel - it3) == 1);
		VERIFY((it1 - hamon::default_sentinel) == -3);
		VERIFY((it2 - hamon::default_sentinel) == -2);
		VERIFY((it3 - hamon::default_sentinel) == -1);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewIteratorSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_sub_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
