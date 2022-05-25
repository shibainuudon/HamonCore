﻿/**
 *	@file	unit_test_iterator_iter_difference_t.cpp
 *
 *	@brief	iter_difference_t のテスト
 */

#include <hamon/iterator/iter_difference_t.hpp>
#include <type_traits>
#include <cstddef>
#include <vector>

namespace hamon_iterator_test
{

namespace iter_difference_t_test
{

template <typename T>
struct have_difference 
{
	using difference_type = T;
};

struct can_difference
{
	friend auto operator-(can_difference const&, can_difference const&) -> char
	{
		return 0;
	}
};

using T = int;

using vec_iterator = std::vector<T>::iterator;
using vec_const_iterator = std::vector<T>::const_iterator;

static_assert(std::is_same<hamon::iter_difference_t<T      *                   >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<T const*                   >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<T      * const             >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<T const* const             >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<T[3]                       >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<T const[3]                 >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<T[]                        >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<T const[]                  >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<vec_iterator               >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<vec_iterator const         >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<vec_const_iterator         >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<vec_const_iterator const   >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<std::vector<T>             >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<std::vector<T> const       >, std::ptrdiff_t>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<have_difference <T      >      >, T>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<have_difference <T const>      >, T const>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<have_difference <T      > const>, T>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<have_difference <T const> const>, T const>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<can_difference      >, signed char>::value, "");
static_assert(std::is_same<hamon::iter_difference_t<can_difference const>, signed char>::value, "");

}	// namespace iter_difference_t_test

}	// namespace hamon_iterator_test
