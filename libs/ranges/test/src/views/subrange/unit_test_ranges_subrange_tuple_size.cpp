/**
 *	@file	unit_test_ranges_subrange_tuple_size.cpp
 *
 *	@brief	tuple_size<subrange> のテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace tuple_size_test
{

using SR1 = hamon::ranges::subrange<int*>;
using SR2 = hamon::ranges::subrange<long*, void*>;
using SR3 = hamon::ranges::subrange<forward_iterator_wrapper<int>, test_sentinel<forward_iterator_wrapper<int>>>;

static_assert(std::tuple_size<SR1>::value == 2, "");
static_assert(std::tuple_size<SR2>::value == 2, "");
static_assert(std::tuple_size<SR3>::value == 2, "");

static_assert(std::tuple_size<SR1 const>::value == 2, "");
static_assert(std::tuple_size<SR2 const>::value == 2, "");
static_assert(std::tuple_size<SR3 const>::value == 2, "");

}	// namespace tuple_size_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
