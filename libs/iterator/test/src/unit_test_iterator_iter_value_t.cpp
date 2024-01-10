/**
 *	@file	unit_test_iterator_iter_value_t.cpp
 *
 *	@brief	iter_value_t のテスト
 */

#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/indirectly_readable_traits.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>
#include "constexpr_test.hpp"

namespace hamon_iterator_test {
namespace iter_value_t_test {

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

struct my_iterator_1
{
};

struct my_iterator_2
{
};

}	// namespace iter_value_t_test
}	// namespace hamon_iterator_test

// indirectly_readable_traits<my_iterator_1> の特殊化
template <>
struct HAMON_INDIRECTLY_READABLE_TRAITS_NAMESPACE::indirectly_readable_traits<
	hamon_iterator_test::iter_value_t_test::my_iterator_1>
{
	using value_type = long const;
};

// iterator_traits<my_iterator_2> の特殊化
template <>
struct HAMON_ITERATOR_TRAITS_NAMESPACE::iterator_traits<
	hamon_iterator_test::iter_value_t_test::my_iterator_2>
{
	using value_type = char const;
};

namespace hamon_iterator_test {
namespace iter_value_t_test {

using T = int;

using vec_iterator = hamon::vector<T>::iterator;
using vec_const_iterator = hamon::vector<T>::const_iterator;

static_assert(hamon::is_same<hamon::iter_value_t<T               *          >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T const         *          >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T       volatile*          >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T const volatile*          >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T               * const    >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T const         * const    >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T       volatile* const    >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T const volatile* const    >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T               * volatile >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T const         * volatile >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T       volatile* volatile >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T const volatile* volatile >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T[3]                       >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T const[3]                 >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T[]                        >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<T const[]                  >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<vec_iterator               >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<vec_iterator const         >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<vec_const_iterator         >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<vec_const_iterator const   >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<hamon::vector<T>           >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<hamon::vector<T> const     >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<have_value<T      >        >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<have_value<T const>        >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<have_value<T      > const  >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<have_value<T const> const  >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<have_element<T      >      >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<have_element<T const>      >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<have_element<T      > const>, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<have_element<T const> const>, T>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<my_iterator_1>, long const>::value, "");
static_assert(hamon::is_same<hamon::iter_value_t<my_iterator_2>, char const>::value, "");

}	// namespace iter_value_t_test
}	// namespace hamon_iterator_test
