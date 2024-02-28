/**
 *	@file	unit_test_ranges_chunk_view_inner_iterator.cpp
 *
 *	@brief	chunk_view::inner_iterator のテスト
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#include <hamon/ranges/concepts.hpp>

namespace hamon_ranges_test
{
namespace chunk_view_test
{
namespace inner_iterator_test
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

template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_dereference
	: public hamon::false_type {};

template <typename T>
struct has_dereference<T, hamon::void_t<decltype(*hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_pre_increment
	: public hamon::false_type {};

template <typename T>
struct has_pre_increment<T, hamon::void_t<decltype(++hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_post_increment
	: public hamon::false_type {};

template <typename T>
struct has_post_increment<T, hamon::void_t<decltype(hamon::declval<T>()++)>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_pre_decrement
	: public hamon::false_type {};

template <typename T>
struct has_pre_decrement<T, hamon::void_t<decltype(--hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_post_decrement
	: public hamon::false_type {};

template <typename T>
struct has_post_decrement<T, hamon::void_t<decltype(hamon::declval<T>()--)>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_add_assign
	: public hamon::false_type {};

template <typename T>
struct has_add_assign<T, hamon::void_t<decltype(hamon::declval<T>() += hamon::declval<int>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_sub_assign
	: public hamon::false_type {};

template <typename T>
struct has_sub_assign<T, hamon::void_t<decltype(hamon::declval<T>() -= hamon::declval<int>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_subscript
	: public hamon::false_type {};

template <typename T>
struct has_subscript<T, hamon::void_t<decltype(hamon::declval<T>()[hamon::declval<int>()])>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_add
	: public hamon::false_type {};

template <typename T, typename U>
struct has_add<T, U, hamon::void_t<decltype(hamon::declval<T>() + hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_sub
	: public hamon::false_type {};

template <typename T, typename U>
struct has_sub<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_not_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_not_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_less
	: public hamon::false_type {};

template <typename T, typename U>
struct has_less<T, U, hamon::void_t<decltype(hamon::declval<T>() < hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_less_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_less_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() <= hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_greater
	: public hamon::false_type {};

template <typename T, typename U>
struct has_greater<T, U, hamon::void_t<decltype(hamon::declval<T>() > hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_greater_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_greater_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() >= hamon::declval<U>())>>
	: public hamon::true_type {};

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename U, typename = void>
struct has_three_way
	: public hamon::false_type {};

template <typename T, typename U>
struct has_three_way<T, U, hamon::void_t<decltype(hamon::declval<T>() <=> hamon::declval<U>())>>
	: public hamon::true_type {};
#endif

template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_iter_swap
	: public hamon::false_type {};

template <typename T>
struct has_iter_swap<T, hamon::void_t<decltype(hamon::ranges::iter_swap(hamon::declval<T>(), hamon::declval<T>()))>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V  = test_input_view<int const>;
	using CV = hamon::ranges::chunk_view<V>;
	using OI  = decltype(hamon::declval<CV&>().begin());
	using I = decltype((*hamon::declval<OI&>()).begin());
	//static_assert(hamon::is_same<I, CV::inner_iterator>::value, "");

	static_assert(!has_iterator_category<I>::value, "");
	static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::difference_type,  hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<typename I::value_type, int>::value, "");

	static_assert(!hamon::is_default_constructible<I>::value, "");
	static_assert(!hamon::is_copy_constructible<I>::value, "");
	static_assert( hamon::is_move_constructible<I>::value, "");
	static_assert(!hamon::is_copy_assignable<I>::value, "");
	static_assert( hamon::is_move_assignable<I>::value, "");

	static_assert( has_dereference<I&>::value, "");
	static_assert( has_dereference<I const&>::value, "");
	static_assert( has_pre_increment<I&>::value, "");
	static_assert(!has_pre_increment<I const&>::value, "");
	static_assert( has_post_increment<I&>::value, "");
	static_assert(!has_post_increment<I const&>::value, "");
	static_assert(!has_pre_decrement<I&>::value, "");
	static_assert(!has_pre_decrement<I const&>::value, "");
	static_assert(!has_post_decrement<I&>::value, "");
	static_assert(!has_post_decrement<I const&>::value, "");
	static_assert(!has_add_assign<I&>::value, "");
	static_assert(!has_add_assign<I const&>::value, "");
	static_assert(!has_sub_assign<I&>::value, "");
	static_assert(!has_sub_assign<I const&>::value, "");
	static_assert(!has_subscript<I&>::value, "");
	static_assert(!has_subscript<I const&>::value, "");
	static_assert(!has_add<I const&, int>::value, "");
	static_assert(!has_add<int, I const&>::value, "");
	static_assert(!has_sub<I const&, int>::value, "");
	static_assert(!has_sub<int, I const&>::value, "");
	static_assert(!has_sub<I const&, I const&>::value, "");
	static_assert(!has_sub<I const&, hamon::default_sentinel_t>::value, "");
	static_assert(!has_sub<hamon::default_sentinel_t, I const&>::value, "");
	static_assert(!has_equal        <I const&, I const&>::value, "");
	static_assert(!has_not_equal    <I const&, I const&>::value, "");
	static_assert(!has_less         <I const&, I const&>::value, "");
	static_assert(!has_less_equal   <I const&, I const&>::value, "");
	static_assert(!has_greater      <I const&, I const&>::value, "");
	static_assert(!has_greater_equal<I const&, I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_three_way    <I const&, I const&>::value, "");
#endif
	static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
	static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");

	static_assert( has_base<I&>::value, "");
	static_assert( has_base<I const&>::value, "");

	static_assert(!has_iter_swap<I&>::value, "");
	static_assert(!has_iter_swap<I const&>::value, "");

	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<I&      >().base()), input_iterator_wrapper<int const> const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().base()), input_iterator_wrapper<int const> const&>::value, "");

	static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(hamon::declval<I const&>())), int const&&>::value, "");

	int a[] = {0,1,2,3,4,5,6};
	V v(a);
	CV cv(v, 3);
	auto outer_iter = cv.begin();
	{
		auto x = *outer_iter;
		auto inner_iter = x.begin();
		VERIFY(inner_iter.base() == v.begin());
		VERIFY(*inner_iter == 0);
		VERIFY(inner_iter != x.end());
		VERIFY(x.end() != inner_iter);
		VERIFY(hamon::ranges::iter_move(inner_iter) == 0);
		auto& t = ++inner_iter;
		VERIFY(&t == &inner_iter);
		VERIFY(inner_iter.base() == hamon::next(v.begin(), 1));
		VERIFY(*inner_iter == 1);
		VERIFY(inner_iter != x.end());
		VERIFY(x.end() != inner_iter);
		VERIFY(hamon::ranges::iter_move(inner_iter) == 1);
		inner_iter++;
		VERIFY(inner_iter.base() == hamon::next(v.begin(), 2));
		VERIFY(*inner_iter == 2);
		VERIFY(inner_iter != x.end());
		VERIFY(x.end() != inner_iter);
		VERIFY(hamon::ranges::iter_move(inner_iter) == 2);
		inner_iter++;
		VERIFY(inner_iter.base() == hamon::next(v.begin(), 3));
		VERIFY(inner_iter == x.end());
		VERIFY(x.end() == inner_iter);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V  = test_view<int, SizedInputIterator<int>, SizedInputIterator<int>>;
	using CV = hamon::ranges::chunk_view<V>;
	using OI  = decltype(hamon::declval<CV&>().begin());
	using I = decltype((*hamon::declval<OI&>()).begin());
	//static_assert(hamon::is_same<I, CV::inner_iterator>::value, "");

	static_assert(!has_iterator_category<I>::value, "");
	static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::difference_type,  hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<typename I::value_type, int>::value, "");

	static_assert(!hamon::is_default_constructible<I>::value, "");
	static_assert(!hamon::is_copy_constructible<I>::value, "");
	static_assert( hamon::is_move_constructible<I>::value, "");
	static_assert(!hamon::is_copy_assignable<I>::value, "");
	static_assert( hamon::is_move_assignable<I>::value, "");

	static_assert( has_dereference<I&>::value, "");
	static_assert( has_dereference<I const&>::value, "");
	static_assert( has_pre_increment<I&>::value, "");
	static_assert(!has_pre_increment<I const&>::value, "");
	static_assert( has_post_increment<I&>::value, "");
	static_assert(!has_post_increment<I const&>::value, "");
	static_assert(!has_pre_decrement<I&>::value, "");
	static_assert(!has_pre_decrement<I const&>::value, "");
	static_assert(!has_post_decrement<I&>::value, "");
	static_assert(!has_post_decrement<I const&>::value, "");
	static_assert(!has_add_assign<I&>::value, "");
	static_assert(!has_add_assign<I const&>::value, "");
	static_assert(!has_sub_assign<I&>::value, "");
	static_assert(!has_sub_assign<I const&>::value, "");
	static_assert(!has_subscript<I&>::value, "");
	static_assert(!has_subscript<I const&>::value, "");
	static_assert(!has_add<I const&, int>::value, "");
	static_assert(!has_add<int, I const&>::value, "");
	static_assert(!has_sub<I const&, int>::value, "");
	static_assert(!has_sub<int, I const&>::value, "");
	static_assert(!has_sub<I const&, I const&>::value, "");
	static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
	static_assert(!has_equal        <I const&, I const&>::value, "");
	static_assert(!has_not_equal    <I const&, I const&>::value, "");
	static_assert(!has_less         <I const&, I const&>::value, "");
	static_assert(!has_less_equal   <I const&, I const&>::value, "");
	static_assert(!has_greater      <I const&, I const&>::value, "");
	static_assert(!has_greater_equal<I const&, I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_three_way    <I const&, I const&>::value, "");
#endif
	static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
	static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");

	static_assert( has_base<I&>::value, "");
	static_assert( has_base<I const&>::value, "");

	static_assert( has_iter_swap<I&>::value, "");
	static_assert( has_iter_swap<I const&>::value, "");

	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<I&      >().base()), SizedInputIterator<int> const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().base()), SizedInputIterator<int> const&>::value, "");

	static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(hamon::declval<I const&>())), int&&>::value, "");

	int a[] = {0,1,2,3,4,5,6};
	V v(a);
	CV cv(v, 3);
	auto outer_iter = cv.begin();
	{
		auto x = *outer_iter;
		auto inner_iter = x.begin();
		VERIFY(inner_iter.base() == v.begin());
		VERIFY(*inner_iter == 0);
		VERIFY(inner_iter != x.end());
		VERIFY(x.end() != inner_iter);
		VERIFY((inner_iter - x.end()) == -3);
		VERIFY((x.end() - inner_iter) ==  3);
		VERIFY(hamon::ranges::iter_move(inner_iter) == 0);
		auto& t = ++inner_iter;
		VERIFY(&t == &inner_iter);
		VERIFY(inner_iter.base() == hamon::next(v.begin(), 1));
		VERIFY(*inner_iter == 1);
		VERIFY(inner_iter != x.end());
		VERIFY(x.end() != inner_iter);
		VERIFY((inner_iter - x.end()) == -2);
		VERIFY((x.end() - inner_iter) ==  2);
		VERIFY(hamon::ranges::iter_move(inner_iter) == 1);
		inner_iter++;
		VERIFY(inner_iter.base() == hamon::next(v.begin(), 2));
		VERIFY(*inner_iter == 2);
		VERIFY(inner_iter != x.end());
		VERIFY(x.end() != inner_iter);
		VERIFY((inner_iter - x.end()) == -1);
		VERIFY((x.end() - inner_iter) ==  1);
		VERIFY(hamon::ranges::iter_move(inner_iter) == 2);
		inner_iter++;
		VERIFY(inner_iter.base() == hamon::next(v.begin(), 3));
		VERIFY(inner_iter == x.end());
		VERIFY(x.end() == inner_iter);
		VERIFY((inner_iter - x.end()) == 0);
		VERIFY((x.end() - inner_iter) == 0);
	}

	int a2[] = {10,20,30};
	V v2(a2);
	CV cv2(v2, 2);

	auto inner_iter1 = (*cv.begin()).begin();
	auto inner_iter2 = (*cv2.begin()).begin();

	VERIFY(a[0]  ==  0);
	VERIFY(a2[0] == 10);

	hamon::ranges::iter_swap(inner_iter1, inner_iter2);

	VERIFY(a[0]  == 10);
	VERIFY(a2[0] ==  0);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkViewInnerIteratorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace inner_iterator_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
