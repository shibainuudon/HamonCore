/**
 *	@file	unit_test_iterator_iter_difference_t.cpp
 *
 *	@brief	iter_difference_t のテスト
 */

#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/incrementable_traits.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>

namespace hamon_iterator_test {
namespace iter_difference_t_test {

template <typename T>
struct have_difference 
{
	using difference_type = T;
};

struct can_difference
{
	friend auto operator-(can_difference const&, can_difference const&) -> unsigned char
	{
		return 0;
	}
};

struct my_iterator_1
{
};

struct my_iterator_2
{
};

}	// namespace iter_difference_t_test
}	// namespace hamon_iterator_test

// incrementable_traits<my_iterator_1> の特殊化
template <>
struct HAMON_INCREMENTABLE_TRAITS_NAMESPACE::incrementable_traits<
	hamon_iterator_test::iter_difference_t_test::my_iterator_1>
{
	using difference_type = unsigned int;
};

// iterator_traits<my_iterator_2> の特殊化
template <>
struct HAMON_ITERATOR_TRAITS_NAMESPACE::iterator_traits<
	hamon_iterator_test::iter_difference_t_test::my_iterator_2>
{
	using difference_type = signed short;
};

namespace hamon_iterator_test {
namespace iter_difference_t_test {

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
static_assert(hamon::is_same<hamon::iter_difference_t<my_iterator_1>, unsigned int>::value, "");
static_assert(hamon::is_same<hamon::iter_difference_t<my_iterator_2>, signed short>::value, "");

}	// namespace iter_difference_t_test
}	// namespace hamon_iterator_test
