/**
 *	@file	unit_test_ranges_zip_view_iterator_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	friend constexpr iterator operator-(const iterator& i, difference_type n)
 *	  requires all-random-access<Const, Views...>;
 *
 *	friend constexpr difference_type operator-(const iterator& x, const iterator& y)
 *	  requires (sized_sentinel_for<
 *	    iterator_t<maybe-const<Const, Views>>,
 *	    iterator_t<maybe-const<Const, Views>>> && ...);
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace iterator_sub_test
{

template <typename T>
struct TestIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR TestIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
	HAMON_CXX11_CONSTEXPR TestIterator  operator+(difference_type n) const { return {m_ptr + n}; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator--(int) { auto t = *this; --m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
	HAMON_CXX11_CONSTEXPR TestIterator  operator-(difference_type n) const { return {m_ptr - n}; }
	HAMON_CXX11_CONSTEXPR difference_type operator-(TestIterator const& rhs) const { return m_ptr - rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR T&              operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T&              operator[](difference_type i) const { return m_ptr[i]; }
	HAMON_CXX11_CONSTEXPR bool operator==(const TestIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const TestIterator& rhs) const { return m_ptr != rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator< (const TestIterator& rhs) const { return m_ptr <  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator> (const TestIterator& rhs) const { return m_ptr >  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator<=(const TestIterator& rhs) const { return m_ptr <= rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator>=(const TestIterator& rhs) const { return m_ptr >= rhs.m_ptr; }
};

template <typename T>
HAMON_CXX14_CONSTEXPR TestIterator<T>
operator+(hamon::ptrdiff_t, TestIterator<T> const&);

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
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{Iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{ConstIterator{m_last}}; }
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
	{
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using V3 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<int>;
		using V3 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_bidirectional_view<int>;
		using V3 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using V3 = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<char>;
	using ZV = hamon::ranges::zip_view<V1, V2>;

	int a1[] = {1,2,3,4,5};
	char a2[] = {10,20,30,40};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(v1, v2);

	auto it = zv.begin();
	++it;
	++it;
	++it;
	auto it1 = it - 1;
	auto it2 = it - 3;
	VERIFY(hamon::adl_get<0>(*it1) == 3);
	VERIFY(hamon::adl_get<1>(*it1) == 30);
	VERIFY(hamon::adl_get<0>(*it2) == 1);
	VERIFY(hamon::adl_get<1>(*it2) == 10);

	VERIFY((it - it1) == 1);
	VERIFY((it - it2) == 3);
	VERIFY((it1 - it2) == 2);
	VERIFY((it2 - it1) == -2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V1 = TestView<int,
		TestIterator<int>,
		TestIterator<int>,
		TestIterator<int>,
		TestIterator<int>
	>;

	using V2 = TestView<int,
		TestIterator<int>,
		TestIterator<int>,
		TestIterator<int>,
		TestIterator<int>
	>;

	using ZV = hamon::ranges::zip_view<V1, V2>;
	using I = decltype(hamon::declval<ZV&>().begin());
	using S = decltype(hamon::declval<ZV&>().end());

	//static_assert( hamon::is_same<I, ZV::iterator<true>>::value, "");
	//static_assert( hamon::is_same<S, ZV::iterator<true>>::value, "");

	int a1[] = { 1,2,3 };
	int a2[] = { 4,5 };
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(v1, v2);

	I i = zv.begin();
	S s = zv.end();
	VERIFY(i - s == -2);
	VERIFY(s - i ==  2);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipViewIteratorSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_sub_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
