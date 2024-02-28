/**
 *	@file	unit_test_ranges_chunk_view_iterator.cpp
 *
 *	@brief	chunk_view::iterator のテスト
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/compare.hpp>
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
namespace iterator_test
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

template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V  = test_forward_view<int>;
	using CV = hamon::ranges::chunk_view<V>;
	using I  = decltype(hamon::declval<CV&>().begin());
	//static_assert(hamon::is_same<I, CV::iterator<true>>::value, "");

	static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::iterator_concept,  hamon::forward_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::difference_type,   hamon::ptrdiff_t>::value, "");

	static_assert( hamon::is_default_constructible<I>::value, "");
	static_assert( hamon::is_copy_constructible<I>::value, "");
	static_assert( hamon::is_move_constructible<I>::value, "");
	static_assert( hamon::is_copy_assignable<I>::value, "");
	static_assert( hamon::is_move_assignable<I>::value, "");

	static_assert( has_base<I&>::value, "");
	static_assert( has_base<I const&>::value, "");
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
	static_assert( has_equal        <I const&, I const&>::value, "");
	static_assert( has_not_equal    <I const&, I const&>::value, "");
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

	static_assert(hamon::is_same<decltype(hamon::declval<I&      >().base()), forward_iterator_wrapper<int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().base()), forward_iterator_wrapper<int>>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I&      >()), typename I::value_type>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), typename I::value_type>::value, "");
	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V  = test_bidirectional_view<int>;
	using CV = hamon::ranges::chunk_view<V>;
	using I  = decltype(hamon::declval<CV&>().begin());
	//static_assert(hamon::is_same<I, CV::iterator<true>>::value, "");

	static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::iterator_concept,  hamon::bidirectional_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::difference_type,   hamon::ptrdiff_t>::value, "");

	static_assert( hamon::is_default_constructible<I>::value, "");
	static_assert( hamon::is_copy_constructible<I>::value, "");
	static_assert( hamon::is_move_constructible<I>::value, "");
	static_assert( hamon::is_copy_assignable<I>::value, "");
	static_assert( hamon::is_move_assignable<I>::value, "");

	static_assert( has_base<I&>::value, "");
	static_assert( has_base<I const&>::value, "");
	static_assert( has_dereference<I&>::value, "");
	static_assert( has_dereference<I const&>::value, "");
	static_assert( has_pre_increment<I&>::value, "");
	static_assert(!has_pre_increment<I const&>::value, "");
	static_assert( has_post_increment<I&>::value, "");
	static_assert(!has_post_increment<I const&>::value, "");
	static_assert( has_pre_decrement<I&>::value, "");
	static_assert(!has_pre_decrement<I const&>::value, "");
	static_assert( has_post_decrement<I&>::value, "");
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
	static_assert( has_equal        <I const&, I const&>::value, "");
	static_assert( has_not_equal    <I const&, I const&>::value, "");
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

	static_assert(hamon::is_same<decltype(hamon::declval<I&      >().base()), bidirectional_iterator_wrapper<int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().base()), bidirectional_iterator_wrapper<int>>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I&      >()), typename I::value_type>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), typename I::value_type>::value, "");
	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V  = test_random_access_view<int>;
	using CV = hamon::ranges::chunk_view<V>;
	using I  = decltype(hamon::declval<CV&>().begin());
	//static_assert(hamon::is_same<I, CV::iterator<true>>::value, "");

	static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::iterator_concept,  hamon::random_access_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::difference_type,   hamon::ptrdiff_t>::value, "");

	static_assert( hamon::is_default_constructible<I>::value, "");
	static_assert( hamon::is_copy_constructible<I>::value, "");
	static_assert( hamon::is_move_constructible<I>::value, "");
	static_assert( hamon::is_copy_assignable<I>::value, "");
	static_assert( hamon::is_move_assignable<I>::value, "");

	static_assert( has_base<I&>::value, "");
	static_assert( has_base<I const&>::value, "");
	static_assert( has_dereference<I&>::value, "");
	static_assert( has_dereference<I const&>::value, "");
	static_assert( has_pre_increment<I&>::value, "");
	static_assert(!has_pre_increment<I const&>::value, "");
	static_assert( has_post_increment<I&>::value, "");
	static_assert(!has_post_increment<I const&>::value, "");
	static_assert( has_pre_decrement<I&>::value, "");
	static_assert(!has_pre_decrement<I const&>::value, "");
	static_assert( has_post_decrement<I&>::value, "");
	static_assert(!has_post_decrement<I const&>::value, "");
	static_assert( has_add_assign<I&>::value, "");
	static_assert(!has_add_assign<I const&>::value, "");
	static_assert( has_sub_assign<I&>::value, "");
	static_assert(!has_sub_assign<I const&>::value, "");
	static_assert( has_subscript<I&>::value, "");
	static_assert( has_subscript<I const&>::value, "");
	static_assert( has_add<I const&, int>::value, "");
	static_assert( has_add<int, I const&>::value, "");
	static_assert( has_sub<I const&, int>::value, "");
	static_assert(!has_sub<int, I const&>::value, "");
	static_assert( has_sub<I const&, I const&>::value, "");
	static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
	static_assert( has_equal        <I const&, I const&>::value, "");
	static_assert( has_not_equal    <I const&, I const&>::value, "");
	static_assert( has_less         <I const&, I const&>::value, "");
	static_assert( has_less_equal   <I const&, I const&>::value, "");
	static_assert( has_greater      <I const&, I const&>::value, "");
	static_assert( has_greater_equal<I const&, I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_three_way    <I const&, I const&>::value, "");
#endif
	static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
	static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<I&      >().base()), random_access_iterator_wrapper<int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().base()), random_access_iterator_wrapper<int>>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I&      >()), typename I::value_type>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), typename I::value_type>::value, "");
	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using V  = test_view<int, int*>;
	using CV = hamon::ranges::chunk_view<V>;
	using I  = decltype(hamon::declval<CV&>().begin());
	//static_assert(hamon::is_same<I, CV::iterator<true>>::value, "");

	static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::iterator_concept,  hamon::random_access_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::difference_type,   hamon::ptrdiff_t>::value, "");

	static_assert( hamon::is_default_constructible<I>::value, "");
	static_assert( hamon::is_copy_constructible<I>::value, "");
	static_assert( hamon::is_move_constructible<I>::value, "");
	static_assert( hamon::is_copy_assignable<I>::value, "");
	static_assert( hamon::is_move_assignable<I>::value, "");

	{
		I it{};
		(void)it;
	}

	static_assert( has_base<I&>::value, "");
	static_assert( has_base<I const&>::value, "");
	static_assert( has_dereference<I&>::value, "");
	static_assert( has_dereference<I const&>::value, "");
	static_assert( has_pre_increment<I&>::value, "");
	static_assert(!has_pre_increment<I const&>::value, "");
	static_assert( has_post_increment<I&>::value, "");
	static_assert(!has_post_increment<I const&>::value, "");
	static_assert( has_pre_decrement<I&>::value, "");
	static_assert(!has_pre_decrement<I const&>::value, "");
	static_assert( has_post_decrement<I&>::value, "");
	static_assert(!has_post_decrement<I const&>::value, "");
	static_assert( has_add_assign<I&>::value, "");
	static_assert(!has_add_assign<I const&>::value, "");
	static_assert( has_sub_assign<I&>::value, "");
	static_assert(!has_sub_assign<I const&>::value, "");
	static_assert( has_subscript<I&>::value, "");
	static_assert( has_subscript<I const&>::value, "");
	static_assert( has_add<I const&, int>::value, "");
	static_assert( has_add<int, I const&>::value, "");
	static_assert( has_sub<I const&, int>::value, "");
	static_assert(!has_sub<int, I const&>::value, "");
	static_assert( has_sub<I const&, I const&>::value, "");
	static_assert( has_sub<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_sub<hamon::default_sentinel_t, I const&>::value, "");
	static_assert( has_equal        <I const&, I const&>::value, "");
	static_assert( has_not_equal    <I const&, I const&>::value, "");
	static_assert( has_less         <I const&, I const&>::value, "");
	static_assert( has_less_equal   <I const&, I const&>::value, "");
	static_assert( has_greater      <I const&, I const&>::value, "");
	static_assert( has_greater_equal<I const&, I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert( has_three_way    <I const&, I const&>::value, "");
#endif
	static_assert( has_equal        <I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_not_equal    <I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_equal        <hamon::default_sentinel_t, I const&>::value, "");
	static_assert( has_not_equal    <hamon::default_sentinel_t, I const&>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<I&      >().base()), int*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().base()), int*>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I&      >()), typename I::value_type>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), typename I::value_type>::value, "");
	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	static_assert(hamon::is_same<decltype(--hamon::declval<I&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()--), I>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>() += hamon::declval<int>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()[hamon::declval<int>()]), typename I::value_type>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), hamon::ptrdiff_t>::value, "");

	int a[] = {1,2,3,4,5,6,7,8,9,10};
	int const expected1[] = {1,2,3,4};
	int const expected2[] = {5,6,7,8};
	int const expected3[] = {9,10};
	V v(a);
	CV cv(v, 4);
	auto it = cv.begin();
	VERIFY(it.base() == v.begin());
	VERIFY(hamon::ranges::equal(*it, expected1));
	auto& t1 = ++it;
	VERIFY(it.base() == hamon::next(v.begin(), 4));
	VERIFY(&t1 == &it);
	VERIFY(hamon::ranges::equal(*it, expected2));
	it++;
	VERIFY(it.base() == hamon::next(v.begin(), 8));
	VERIFY(hamon::ranges::equal(*it, expected3));
	VERIFY(!(it == cv.end()));
	VERIFY( (it != cv.end()));
	VERIFY(!(cv.end() == it));
	VERIFY( (cv.end() != it));
	++it;
	VERIFY( (it == cv.end()));
	VERIFY(!(it != cv.end()));
	VERIFY( (cv.end() == it));
	VERIFY(!(cv.end() != it));
	--it;
	VERIFY(!(it == cv.end()));
	VERIFY( (it != cv.end()));
	VERIFY(!(cv.end() == it));
	VERIFY( (cv.end() != it));
	VERIFY(hamon::ranges::equal(*it, expected3));
	auto& t2 = --it;
	VERIFY(&t2 == &it);
	VERIFY(hamon::ranges::equal(*it, expected2));
	it--;
	VERIFY(hamon::ranges::equal(*it, expected1));
	auto& t3 = it += 2;
	VERIFY(&t3 == &it);
	VERIFY(hamon::ranges::equal(*it, expected3));
	auto& t4 = it -= 2;
	VERIFY(&t4 == &it);
	VERIFY(hamon::ranges::equal(*it, expected1));
	VERIFY(hamon::ranges::equal(it[0], expected1));
	VERIFY(hamon::ranges::equal(it[1], expected2));
	VERIFY(hamon::ranges::equal(it[2], expected3));

	auto it1 = cv.begin() + 1;
	auto it2 = 1 + cv.begin();
	auto it3 = cv.begin() + 2;
	auto it4 = 2 + cv.begin();
	auto it0 = it4 - 2;

	VERIFY( (it1 == it1));
	VERIFY( (it1 == it2));
	VERIFY(!(it1 == it3));
	VERIFY(!(it1 == it4));
	VERIFY(!(it3 == it1));
	VERIFY(!(it3 == it2));
	VERIFY( (it3 == it3));
	VERIFY( (it3 == it4));

	VERIFY(!(it1 != it1));
	VERIFY(!(it1 != it2));
	VERIFY( (it1 != it3));
	VERIFY( (it1 != it4));
	VERIFY( (it3 != it1));
	VERIFY( (it3 != it2));
	VERIFY(!(it3 != it3));
	VERIFY(!(it3 != it4));

	VERIFY(!(it1 <  it0));
	VERIFY(!(it1 <  it2));
	VERIFY( (it1 <  it3));

	VERIFY(!(it1 <= it0));
	VERIFY( (it1 <= it2));
	VERIFY( (it1 <= it3));

	VERIFY( (it1 >  it0));
	VERIFY(!(it1 >  it2));
	VERIFY(!(it1 >  it3));

	VERIFY( (it1 >= it0));
	VERIFY( (it1 >= it2));
	VERIFY(!(it1 >= it3));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_gt(it2 <=> it0));
	VERIFY(hamon::is_eq(it2 <=> it1));
	VERIFY(hamon::is_lt(it2 <=> it3));
#endif

	VERIFY(it0 - it0 ==  0);
	VERIFY(it0 - it2 == -1);
	VERIFY(it0 - it3 == -2);
	VERIFY(it1 - it0 ==  1);
	VERIFY(it1 - it2 ==  0);
	VERIFY(it1 - it3 == -1);
	VERIFY(it3 - it0 ==  2);
	VERIFY(it3 - it2 ==  1);
	VERIFY(it3 - it3 ==  0);

	auto last = hamon::default_sentinel_t{};
	VERIFY(it0 - last == -3);
	VERIFY(it1 - last == -2);
	VERIFY(it3 - last == -1);
	VERIFY(last - it0 ==  3);
	VERIFY(last - it1 ==  2);
	VERIFY(last - it3 ==  1);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int const>
		>;
		using CV = hamon::ranges::chunk_view<V>;
		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");
		static_assert(!hamon::is_constructible<I, CI>::value, "");
		static_assert(!hamon::is_constructible<CI, I>::value, "");
	}
	{
		using V = TestView<int,
			ConvertibleForwardIterator<int>,
			ConvertibleForwardIterator<int>,
			ConvertibleForwardIterator<int const>,
			ConvertibleForwardIterator<int const>
		>;
		using CV = hamon::ranges::chunk_view<V>;
		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");
		static_assert(!hamon::is_constructible<I, CI>::value, "");
		static_assert( hamon::is_constructible<CI, I>::value, "");

		int a[] = {1,2,3,4,5,6,7,8,9,10};
		V v(a);
		CV cv(v, 3);
		CI it = cv.begin();
		int const expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(*it, expected));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkViewIteratorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace iterator_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
