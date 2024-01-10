/**
 *	@file	unit_test_iterator_indirectly_readable_traits.cpp
 *
 *	@brief	indirectly_readable_traits のテスト
 */

#include <hamon/iterator/indirectly_readable_traits.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
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

template <typename T, typename U>
struct have_both
{
	using value_type = T;
	using element_type = U;
};

using T = int;

using vec_iterator = hamon::vector<T>::iterator;
using vec_const_iterator = hamon::vector<T>::const_iterator;

static_assert(hamon::is_same<hamon::indirectly_readable_traits<T      *                   >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<T const*                   >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<T      * const             >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<T const* const             >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<T[3]                       >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<T const[3]                 >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<T[]                        >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<T const[]                  >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<vec_iterator               >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<vec_iterator const         >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<vec_const_iterator         >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<vec_const_iterator const   >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<vec_iterator[2]            >::value_type, vec_iterator>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<vec_iterator*              >::value_type, vec_iterator>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<hamon::vector<T>           >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<hamon::vector<T> const     >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_value<T      >        >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_value<T const>        >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_value<T      > const  >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_value<T const> const  >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_value<T>[3]           >::value_type, have_value<T>>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_value<T>*             >::value_type, have_value<T>>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_element<T      >      >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_element<T const>      >::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_element<T      > const>::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_element<T const> const>::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_element<T>[4]         >::value_type, have_element<T>>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_element<T>*           >::value_type, have_element<T>>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_both<T      , T      >>::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_both<T const, T      >>::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_both<T      , T const>>::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_both<T const, T const>>::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_both<T      , T      > const>::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_both<T const, T      > const>::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_both<T      , T const> const>::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_both<T const, T const> const>::value_type, T>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_both<T, T>[]>::value_type, have_both<T, T>>::value, "");
static_assert(hamon::is_same<hamon::indirectly_readable_traits<have_both<T, T>*>::value_type, have_both<T, T>>::value, "");

template <typename, typename = void>
struct has_value_type
	: public hamon::false_type {};
 
template <typename T>
struct has_value_type<T, hamon::void_t<typename T::value_type>>
	: public hamon::true_type {};

static_assert(!has_value_type<hamon::indirectly_readable_traits<void>>::value, "");
static_assert(!has_value_type<hamon::indirectly_readable_traits<void*>>::value, "");
static_assert(!has_value_type<hamon::indirectly_readable_traits<int>>::value, "");
static_assert(!has_value_type<hamon::indirectly_readable_traits<int&>>::value, "");
static_assert(!has_value_type<hamon::indirectly_readable_traits<int&&>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<int*>>::value, "");
static_assert(!has_value_type<hamon::indirectly_readable_traits<int const>>::value, "");
static_assert(!has_value_type<hamon::indirectly_readable_traits<int const&>>::value, "");
static_assert(!has_value_type<hamon::indirectly_readable_traits<int const&&>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<int const*>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<have_both<int, int>>>::value, "");
static_assert(!has_value_type<hamon::indirectly_readable_traits<have_both<int, long>>>::value, "");
static_assert(!has_value_type<hamon::indirectly_readable_traits<have_both<long, int>>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<have_both<long, long>>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<have_both<int, int>[]>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<have_both<int, long>[]>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<have_both<long, int>[]>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<have_both<long, long>[]>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<have_both<int, int>*>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<have_both<int, long>*>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<have_both<long, int>*>>::value, "");
static_assert( has_value_type<hamon::indirectly_readable_traits<have_both<long, long>*>>::value, "");

}	// namespace indirectly_readable_traits_test

}	// namespace hamon_iterator_test
