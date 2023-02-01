/**
 *	@file	unit_test_ranges_subrange_tuple_element.cpp
 *
 *	@brief	tuple_element<subrange> のテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace tuple_element_test
{

using SR1 = hamon::ranges::subrange<int*>;
using SR2 = hamon::ranges::subrange<long*, void*>;
using SR3 = hamon::ranges::subrange<forward_iterator_wrapper<int>, test_sentinel<forward_iterator_wrapper<int>>>;

static_assert(std::is_same<hamon::tuple_element_t<0, SR1>, int*>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<1, SR1>, int*>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<0, SR2>, long*>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<1, SR2>, void*>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<0, SR3>, forward_iterator_wrapper<int>>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<1, SR3>, test_sentinel<forward_iterator_wrapper<int>>>::value, "");

static_assert(std::is_same<hamon::tuple_element_t<0, SR1 const>, int*>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<1, SR1 const>, int*>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<0, SR2 const>, long*>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<1, SR2 const>, void*>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<0, SR3 const>, forward_iterator_wrapper<int>>::value, "");
static_assert(std::is_same<hamon::tuple_element_t<1, SR3 const>, test_sentinel<forward_iterator_wrapper<int>>>::value, "");

}	// namespace tuple_element_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
