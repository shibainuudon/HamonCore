/**
 *	@file	range_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_RANGE_TEST_HELPER_HPP
#define HAMON_RANGE_TEST_HELPER_HPP

#include <hamon/ranges/range_difference_t.hpp>
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
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T&>().begin())>>
	: public hamon::true_type {};

// end()
template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T&>().end())>>
	: public hamon::true_type {};

// empty()
template <typename T, typename = void>
struct has_empty
	: public hamon::false_type {};

template <typename T>
struct has_empty<T, hamon::void_t<decltype(hamon::declval<T&>().empty())>>
	: public hamon::true_type {};

// cbegin()
template <typename T, typename = void>
struct has_cbegin
	: public hamon::false_type {};

template <typename T>
struct has_cbegin<T, hamon::void_t<decltype(hamon::declval<T&>().cbegin())>>
	: public hamon::true_type {};

// cend()
template <typename T, typename = void>
struct has_cend
	: public hamon::false_type {};

template <typename T>
struct has_cend<T, hamon::void_t<decltype(hamon::declval<T&>().cend())>>
	: public hamon::true_type {};

// operator bool()
template <typename T, typename = void>
struct has_operator_bool
	: public hamon::false_type {};

template <typename T>
struct has_operator_bool<T, hamon::void_t<decltype(hamon::declval<T&>().operator bool())>>
	: public hamon::true_type {};

// data()
template <typename T, typename = void>
struct has_data
	: public hamon::false_type {};

template <typename T>
struct has_data<T, hamon::void_t<decltype(hamon::declval<T&>().data())>>
	: public hamon::true_type {};

// size()
template <typename T, typename = void>
struct has_size
	: public hamon::false_type {};

template <typename T>
struct has_size<T, hamon::void_t<decltype(hamon::declval<T&>().size())>>
	: public hamon::true_type {};

// front()
template <typename T, typename = void>
struct has_front
	: public hamon::false_type {};

template <typename T>
struct has_front<T, hamon::void_t<decltype(hamon::declval<T&>().front())>>
	: public hamon::true_type {};

// back()
template <typename T, typename = void>
struct has_back
	: public hamon::false_type {};

template <typename T>
struct has_back<T, hamon::void_t<decltype(hamon::declval<T&>().back())>>
	: public hamon::true_type {};

// operator[]
template <typename T, typename = void>
struct has_subscript
	: public hamon::false_type {};

template <typename T>
struct has_subscript<T, hamon::void_t<decltype(hamon::declval<T&>()[hamon::declval<hamon::ranges::range_difference_t<T>>()])>>
	: public hamon::true_type {};


}	// namespace hamon_ranges_test

#endif // HAMON_RANGE_TEST_HELPER_HPP
