/**
 *	@file	range_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_RANGE_TEST_HELPER_HPP
#define HAMON_RANGE_TEST_HELPER_HPP

#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon_ranges_test
{

// begin()
template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

// end()
template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

// empty()
template <typename T, typename = void>
struct has_empty
	: public hamon::false_type {};

template <typename T>
struct has_empty<T, hamon::void_t<decltype(hamon::declval<T>().empty())>>
	: public hamon::true_type {};

// cbegin()
template <typename T, typename = void>
struct has_cbegin
	: public hamon::false_type {};

template <typename T>
struct has_cbegin<T, hamon::void_t<decltype(hamon::declval<T>().cbegin())>>
	: public hamon::true_type {};

// cend()
template <typename T, typename = void>
struct has_cend
	: public hamon::false_type {};

template <typename T>
struct has_cend<T, hamon::void_t<decltype(hamon::declval<T>().cend())>>
	: public hamon::true_type {};

// operator bool()
template <typename T, typename = void>
struct has_operator_bool
	: public hamon::false_type {};

template <typename T>
struct has_operator_bool<T, hamon::void_t<decltype(hamon::declval<T>().operator bool())>>
	: public hamon::true_type {};

// data()
template <typename T, typename = void>
struct has_data
	: public hamon::false_type {};

template <typename T>
struct has_data<T, hamon::void_t<decltype(hamon::declval<T>().data())>>
	: public hamon::true_type {};

// size()
template <typename T, typename = void>
struct has_size
	: public hamon::false_type {};

template <typename T>
struct has_size<T, hamon::void_t<decltype(hamon::declval<T>().size())>>
	: public hamon::true_type {};

// reserve_hint()
template <typename T, typename = void>
struct has_reserve_hint
	: public hamon::false_type {};

template <typename T>
struct has_reserve_hint<T, hamon::void_t<decltype(hamon::declval<T>().reserve_hint())>>
	: public hamon::true_type {};

// front()
template <typename T, typename = void>
struct has_front
	: public hamon::false_type {};

template <typename T>
struct has_front<T, hamon::void_t<decltype(hamon::declval<T>().front())>>
	: public hamon::true_type {};

// back()
template <typename T, typename = void>
struct has_back
	: public hamon::false_type {};

template <typename T>
struct has_back<T, hamon::void_t<decltype(hamon::declval<T>().back())>>
	: public hamon::true_type {};

// operator[]
template <typename T, typename = void>
struct has_subscript
	: public hamon::false_type {};

template <typename T>
struct has_subscript<T, hamon::void_t<decltype(hamon::declval<T>()[hamon::declval<hamon::ptrdiff_t>()])>>
	: public hamon::true_type {};

// base()
template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
	: public hamon::true_type {};

// T::iterator_category
template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

// operator->()
template <typename T, typename = void>
struct has_arrow
	: public hamon::false_type {};

template <typename T>
struct has_arrow<T, hamon::void_t<decltype(hamon::declval<T>().operator->())>>
	: public hamon::true_type {};

// operator++()
template <typename T, typename = void>
struct has_pre_increment
	: public hamon::false_type {};

template <typename T>
struct has_pre_increment<T, hamon::void_t<decltype(++hamon::declval<T>())>>
	: public hamon::true_type {};

// operator++(int)
template <typename T, typename = void>
struct has_post_increment
	: public hamon::false_type {};

template <typename T>
struct has_post_increment<T, hamon::void_t<decltype(hamon::declval<T>()++)>>
	: public hamon::true_type {};

// operator--()
template <typename T, typename = void>
struct has_pre_decrement
	: public hamon::false_type {};

template <typename T>
struct has_pre_decrement<T, hamon::void_t<decltype(--hamon::declval<T>())>>
	: public hamon::true_type {};

// operator--(int)
template <typename T, typename = void>
struct has_post_decrement
	: public hamon::false_type {};

template <typename T>
struct has_post_decrement<T, hamon::void_t<decltype(hamon::declval<T>()--)>>
	: public hamon::true_type {};

// operator+=
template <typename T, typename U, typename = void>
struct has_plus_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_plus_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() += hamon::declval<U>())>>
	: public hamon::true_type {};

// operator-=
template <typename T, typename U, typename = void>
struct has_minus_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_minus_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() -= hamon::declval<U>())>>
	: public hamon::true_type {};

// operator+
template <typename T, typename U, typename = void>
struct has_plus
	: public hamon::false_type {};

template <typename T, typename U>
struct has_plus<T, U, hamon::void_t<decltype(hamon::declval<T>() + hamon::declval<U>())>>
	: public hamon::true_type {};

// operator-
template <typename T, typename U, typename = void>
struct has_minus
	: public hamon::false_type {};

template <typename T, typename U>
struct has_minus<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

// operator==
template <typename T, typename U = T, typename = void>
struct has_eq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_eq<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

// operator!=
template <typename T, typename U = T, typename = void>
struct has_neq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_neq<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
	: public hamon::true_type {};

// operator<
template <typename T, typename U = T, typename = void>
struct has_lt
	: public hamon::false_type {};

template <typename T, typename U>
struct has_lt<T, U, hamon::void_t<decltype(hamon::declval<T>() < hamon::declval<U>())>>
	: public hamon::true_type {};

// operator<=
template <typename T, typename U = T, typename = void>
struct has_lteq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_lteq<T, U, hamon::void_t<decltype(hamon::declval<T>() <= hamon::declval<U>())>>
	: public hamon::true_type {};

// operator>
template <typename T, typename U = T, typename = void>
struct has_gt
	: public hamon::false_type {};

template <typename T, typename U>
struct has_gt<T, U, hamon::void_t<decltype(hamon::declval<T>() > hamon::declval<U>())>>
	: public hamon::true_type {};

// operator>=
template <typename T, typename U = T, typename = void>
struct has_gteq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_gteq<T, U, hamon::void_t<decltype(hamon::declval<T>() >= hamon::declval<U>())>>
	: public hamon::true_type {};

// operator<=>
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename U = T, typename = void>
struct has_compare_three_way
	: public hamon::false_type {};

template <typename T, typename U>
struct has_compare_three_way<T, U, hamon::void_t<decltype(hamon::declval<T>() <=> hamon::declval<U>())>>
	: public hamon::true_type {};
#endif

// iter_swap
template <typename T, typename = void>
struct has_iter_swap
	: public hamon::false_type {};

template <typename T>
struct has_iter_swap<T, hamon::void_t<decltype(hamon::ranges::iter_swap(hamon::declval<T>(), hamon::declval<T>()))>>
	: public hamon::true_type {};

}	// namespace hamon_ranges_test

#endif // HAMON_RANGE_TEST_HELPER_HPP
