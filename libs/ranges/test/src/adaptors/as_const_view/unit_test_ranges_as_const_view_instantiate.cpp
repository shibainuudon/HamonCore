/**
 *	@file	unit_test_ranges_as_const_view_instantiate.cpp
 *
 *	@brief	ranges::as_const_view のテスト
 *
 *	template<view V>
 *	  requires input_range<V>
 *	class as_const_view;
 */

#include <hamon/ranges/adaptors/as_const_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_const_view_test
{
namespace instantiate_test
{

template <typename T, typename = void>
struct CanInstantiateAsConstView
	: hamon::false_type {};

template <typename T>
struct CanInstantiateAsConstView<T, hamon::void_t<hamon::ranges::as_const_view<T>>>
	: hamon::true_type {};

static_assert( CanInstantiateAsConstView<test_input_view<int>>::value, "");
static_assert(!CanInstantiateAsConstView<test_input_range<int>>::value, "");	// requires view<V>
static_assert(!CanInstantiateAsConstView<test_output_view<int>>::value, "");	// requires input_range<V>

}	// namespace instantiate_test
}	// namespace as_const_view_test
}	// namespace hamon_ranges_test
