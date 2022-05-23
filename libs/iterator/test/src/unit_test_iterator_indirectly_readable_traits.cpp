﻿/**
 *	@file	unit_test_iterator_indirectly_readable_traits.cpp
 *
 *	@brief	indirectly_readable_traits のテスト
 */

#include <hamon/iterator/indirectly_readable_traits.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_iterator_test
{

namespace indirectly_readable_traits_test
{

template <typename T>
struct have_value
{
	using value_type = T;
};

template <typename T>
struct have_element
{
	using element_type = T;
};

using T = int;

using vec_iterator = std::vector<T>::iterator;
using vec_const_iterator = std::vector<T>::const_iterator;

static_assert(std::is_same<hamon::indirectly_readable_traits<T      *                   >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<T const*                   >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<T      * const             >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<T const* const             >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<T[3]                       >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<T const[3]                 >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<T[]                        >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<T const[]                  >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<vec_iterator               >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<vec_iterator const         >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<vec_const_iterator         >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<vec_const_iterator const   >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<std::vector<T>             >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<std::vector<T> const       >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<have_value<T      >        >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<have_value<T const>        >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<have_value<T      > const  >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<have_value<T const> const  >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<have_element<T      >      >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<have_element<T const>      >::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<have_element<T      > const>::value_type, T>::value, "");
static_assert(std::is_same<hamon::indirectly_readable_traits<have_element<T const> const>::value_type, T>::value, "");

}	// namespace indirectly_readable_traits_test

}	// namespace hamon_iterator_test
