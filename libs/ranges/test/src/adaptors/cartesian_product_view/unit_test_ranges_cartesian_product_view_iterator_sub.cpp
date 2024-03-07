/**
 *	@file	unit_test_ranges_cartesian_product_view_iterator_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	friend constexpr iterator operator-(const iterator& x, difference_type y)
 *	  requires cartesian-product-is-random-access<Const, First, Vs...>;
 *	friend constexpr difference_type operator-(const iterator& x, const iterator& y)
 *	  requires cartesian-is-sized-sentinel<Const, iterator_t, First, Vs...>;
 *	
 *	friend constexpr difference_type operator-(const iterator& i, default_sentinel_t)
 *	  requires cartesian-is-sized-sentinel<Const, sentinel_t, First, Vs...>;
 *	friend constexpr difference_type operator-(default_sentinel_t, const iterator& i)
 *	  requires cartesian-is-sized-sentinel<Const, sentinel_t, First, Vs...>;
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
{
namespace iterator_sub_test
{

template <typename T>
struct TestIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = int;
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
	HAMON_CXX11_CONSTEXPR difference_type operator-(TestIterator const& rhs) const { return static_cast<difference_type>(m_ptr - rhs.m_ptr); }
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
		using V = test_view<int, TestIterator<int>, TestIterator<int>>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
	}
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
		static_assert(!has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_sub<hamon::default_sentinel_t, I const&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
		static_assert(!has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_sub<hamon::default_sentinel_t, I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
		static_assert(!has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_sub<hamon::default_sentinel_t, I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
	}
	{
		using V1 = test_view<int, TestIterator<int>, TestIterator<int>>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_view<int, TestIterator<int>, TestIterator<int>>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), typename I::difference_type>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), typename I::difference_type>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_random_access_view<int>;
	using CV = hamon::ranges::cartesian_product_view<V>;

	int a[] = {1,2,3,4,5};
	V v(a);
	CV cv(v);

	auto it = cv.begin();
	++it; ++it; ++it; ++it;

	auto it1 = it - 1;
	auto it2 = it - 2;
	auto it3 = it - 3;

	VERIFY(*it1 == hamon::make_tuple(4));
	VERIFY(*it2 == hamon::make_tuple(3));
	VERIFY(*it3 == hamon::make_tuple(2));

	VERIFY((it - it1) == 1);
	VERIFY((it - it2) == 2);
	VERIFY((it - it3) == 3);
	VERIFY((it1 - it) == -1);
	VERIFY((it2 - it) == -2);
	VERIFY((it3 - it) == -3);

	VERIFY((hamon::default_sentinel - it1) == 2);
	VERIFY((hamon::default_sentinel - it2) == 3);
	VERIFY((hamon::default_sentinel - it3) == 4);

	VERIFY((it1 - hamon::default_sentinel) == -2);
	VERIFY((it2 - hamon::default_sentinel) == -3);
	VERIFY((it3 - hamon::default_sentinel) == -4);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<char>;
	using V3 = test_random_access_view<float>;
	using CV = hamon::ranges::cartesian_product_view<V1, V2, V3>;

	int a1[] = {1,2,3};
	char a2[] = {'a', 'b'};
	float a3[] = {0.5f, 1.5f, 2.5f};
	V1 v1(a1);
	V2 v2(a2);
	V3 v3(a3);
	CV cv(v1, v2, v3);
	auto it = cv.begin();
	it += 17;

	auto it01 = it - 17;
	auto it02 = it - 16;
	auto it03 = it - 15;
	auto it04 = it - 14;
	auto it05 = it - 13;
	auto it06 = it - 12;
	auto it07 = it - 11;
	auto it08 = it - 10;
	auto it09 = it -  9;
	auto it10 = it -  8;
	auto it11 = it -  7;
	auto it12 = it -  6;
	auto it13 = it -  5;
	auto it14 = it -  4;
	auto it15 = it -  3;
	auto it16 = it -  2;
	auto it17 = it -  1;
	auto it18 = it -  0;
	VERIFY(*it01 == hamon::make_tuple(1, 'a', 0.5f));
	VERIFY(*it02 == hamon::make_tuple(1, 'a', 1.5f));
	VERIFY(*it03 == hamon::make_tuple(1, 'a', 2.5f));
	VERIFY(*it04 == hamon::make_tuple(1, 'b', 0.5f));
	VERIFY(*it05 == hamon::make_tuple(1, 'b', 1.5f));
	VERIFY(*it06 == hamon::make_tuple(1, 'b', 2.5f));
	VERIFY(*it07 == hamon::make_tuple(2, 'a', 0.5f));
	VERIFY(*it08 == hamon::make_tuple(2, 'a', 1.5f));
	VERIFY(*it09 == hamon::make_tuple(2, 'a', 2.5f));
	VERIFY(*it10 == hamon::make_tuple(2, 'b', 0.5f));
	VERIFY(*it11 == hamon::make_tuple(2, 'b', 1.5f));
	VERIFY(*it12 == hamon::make_tuple(2, 'b', 2.5f));
	VERIFY(*it13 == hamon::make_tuple(3, 'a', 0.5f));
	VERIFY(*it14 == hamon::make_tuple(3, 'a', 1.5f));
	VERIFY(*it15 == hamon::make_tuple(3, 'a', 2.5f));
	VERIFY(*it16 == hamon::make_tuple(3, 'b', 0.5f));
	VERIFY(*it17 == hamon::make_tuple(3, 'b', 1.5f));
	VERIFY(*it18 == hamon::make_tuple(3, 'b', 2.5f));

	VERIFY((it - it01) == 17);
	VERIFY((it - it02) == 16);
	VERIFY((it - it03) == 15);
	VERIFY((it - it04) == 14);
	VERIFY((it - it05) == 13);
	VERIFY((it - it06) == 12);
	VERIFY((it - it07) == 11);
	VERIFY((it - it08) == 10);
	VERIFY((it - it09) ==  9);
	VERIFY((it - it10) ==  8);
	VERIFY((it - it11) ==  7);
	VERIFY((it - it12) ==  6);
	VERIFY((it - it13) ==  5);
	VERIFY((it - it14) ==  4);
	VERIFY((it - it15) ==  3);
	VERIFY((it - it16) ==  2);
	VERIFY((it - it17) ==  1);
	VERIFY((it - it18) ==  0);

	VERIFY((it01 - it) == -17);
	VERIFY((it02 - it) == -16);
	VERIFY((it03 - it) == -15);
	VERIFY((it04 - it) == -14);
	VERIFY((it05 - it) == -13);
	VERIFY((it06 - it) == -12);
	VERIFY((it07 - it) == -11);
	VERIFY((it08 - it) == -10);
	VERIFY((it09 - it) ==  -9);
	VERIFY((it10 - it) ==  -8);
	VERIFY((it11 - it) ==  -7);
	VERIFY((it12 - it) ==  -6);
	VERIFY((it13 - it) ==  -5);
	VERIFY((it14 - it) ==  -4);
	VERIFY((it15 - it) ==  -3);
	VERIFY((it16 - it) ==  -2);
	VERIFY((it17 - it) ==  -1);
	VERIFY((it18 - it) ==  -0);

	VERIFY((it08 - it01) ==  7);
	VERIFY((it08 - it02) ==  6);
	VERIFY((it08 - it03) ==  5);
	VERIFY((it08 - it04) ==  4);
	VERIFY((it08 - it05) ==  3);
	VERIFY((it08 - it06) ==  2);
	VERIFY((it08 - it07) ==  1);
	VERIFY((it08 - it08) ==  0);
	VERIFY((it08 - it09) == -1);
	VERIFY((it08 - it10) == -2);
	VERIFY((it08 - it11) == -3);
	VERIFY((it08 - it12) == -4);
	VERIFY((it08 - it13) == -5);
	VERIFY((it08 - it14) == -6);
	VERIFY((it08 - it15) == -7);
	VERIFY((it08 - it16) == -8);
	VERIFY((it08 - it17) == -9);
	VERIFY((it08 - it18) == -10);

	VERIFY((hamon::default_sentinel - it01) == 18);
	VERIFY((hamon::default_sentinel - it02) == 17);
	VERIFY((hamon::default_sentinel - it03) == 16);
	VERIFY((hamon::default_sentinel - it04) == 15);
	VERIFY((hamon::default_sentinel - it05) == 14);
	VERIFY((hamon::default_sentinel - it06) == 13);
	VERIFY((hamon::default_sentinel - it07) == 12);
	VERIFY((hamon::default_sentinel - it08) == 11);
	VERIFY((hamon::default_sentinel - it09) == 10);
	VERIFY((hamon::default_sentinel - it10) ==  9);
	VERIFY((hamon::default_sentinel - it11) ==  8);
	VERIFY((hamon::default_sentinel - it12) ==  7);
	VERIFY((hamon::default_sentinel - it13) ==  6);
	VERIFY((hamon::default_sentinel - it14) ==  5);
	VERIFY((hamon::default_sentinel - it15) ==  4);
	VERIFY((hamon::default_sentinel - it16) ==  3);
	VERIFY((hamon::default_sentinel - it17) ==  2);
	VERIFY((hamon::default_sentinel - it18) ==  1);

	VERIFY((it01 - hamon::default_sentinel) == -18);
	VERIFY((it02 - hamon::default_sentinel) == -17);
	VERIFY((it03 - hamon::default_sentinel) == -16);
	VERIFY((it04 - hamon::default_sentinel) == -15);
	VERIFY((it05 - hamon::default_sentinel) == -14);
	VERIFY((it06 - hamon::default_sentinel) == -13);
	VERIFY((it07 - hamon::default_sentinel) == -12);
	VERIFY((it08 - hamon::default_sentinel) == -11);
	VERIFY((it09 - hamon::default_sentinel) == -10);
	VERIFY((it10 - hamon::default_sentinel) ==  -9);
	VERIFY((it11 - hamon::default_sentinel) ==  -8);
	VERIFY((it12 - hamon::default_sentinel) ==  -7);
	VERIFY((it13 - hamon::default_sentinel) ==  -6);
	VERIFY((it14 - hamon::default_sentinel) ==  -5);
	VERIFY((it15 - hamon::default_sentinel) ==  -4);
	VERIFY((it16 - hamon::default_sentinel) ==  -3);
	VERIFY((it17 - hamon::default_sentinel) ==  -2);
	VERIFY((it18 - hamon::default_sentinel) ==  -1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewIteratorSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_sub_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
