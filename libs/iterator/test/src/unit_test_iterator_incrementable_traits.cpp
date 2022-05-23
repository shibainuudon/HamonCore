﻿/**
 *	@file	unit_test_iterator_incrementable_traits.cpp
 *
 *	@brief	incrementable_traits のテスト
 */

#include <hamon/iterator/incrementable_traits.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <vector>
#include <type_traits>

namespace hamon_iterator_test
{

namespace incrementable_traits_test
{

template <typename, typename = hamon::void_t<>>
struct has_difference_type
	: public std::false_type {};
 
template <typename T>
struct has_difference_type<T, hamon::void_t<typename T::difference_type>>
	: public std::true_type {};

template <typename T>
struct X 
{
	using difference_type = T;
};

struct Y
{
	friend auto operator-(Y const&, Y const&) -> char
	{
		return 0;
	}
};

struct Z 
{
};

using T = int;

using vec_iterator = std::vector<T>::iterator;
using vec_const_iterator = std::vector<T>::const_iterator;

static_assert(std::is_same<hamon::incrementable_traits<T                          >::difference_type, std::make_signed<T>::type>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<T      *                   >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<T const*                   >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<T      * const             >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<T const* const             >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<T[3]                       >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<T const[3]                 >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<T[]                        >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<T const[]                  >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<vec_iterator               >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<vec_iterator const         >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<vec_const_iterator         >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<vec_const_iterator const   >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<std::vector<T>           >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<std::vector<T> const     >::difference_type, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<X<T      >      >::difference_type, T>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<X<T const>      >::difference_type, T const>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<X<T      > const>::difference_type, T>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<X<T const> const>::difference_type, T const>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<Y      >::difference_type, signed char>::value, "");
static_assert(std::is_same<hamon::incrementable_traits<Y const>::difference_type, signed char>::value, "");

static_assert( has_difference_type<hamon::incrementable_traits<X<T>>>::value, "");
static_assert( has_difference_type<hamon::incrementable_traits<Y>>::value, "");
static_assert(!has_difference_type<hamon::incrementable_traits<Z>>::value, "");

}	// namespace incrementable_traits_test

}	// namespace hamon_iterator_test