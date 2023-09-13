/**
 *	@file	unit_test_iterator_iter_difference_t.cpp
 *
 *	@brief	iter_difference_t のテスト
 */

#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>

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

using vec_iterator = hamon::vector<T>::iterator;
using vec_const_iterator = hamon::vector<T>::const_iterator;

static_assert(hamon::is_same<hamon::iter_difference_t<T      *                   >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<T const*                   >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<T      * const             >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<T const* const             >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<T[3]                       >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<T const[3]                 >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<T[]                        >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<T const[]                  >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<vec_iterator               >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<vec_iterator const         >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<vec_const_iterator         >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<vec_const_iterator const   >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<hamon::vector<T>           >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<hamon::vector<T> const     >, hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<have_difference <T      >      >, T>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<have_difference <T const>      >, T const>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<have_difference <T      > const>, T>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<have_difference <T const> const>, T const>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<can_difference      >, signed char>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<can_difference const>, signed char>::value, "");

}	// namespace iter_difference_t_test

}	// namespace hamon_iterator_test
