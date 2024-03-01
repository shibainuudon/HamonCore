/**
 *	@file	unit_test_ranges_slide_view_instantiate.cpp
 *
 *	@brief	slide_view のテスト
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace slide_view_test
{
namespace instantiate_test
{

template <typename V, typename = void>
struct CanInstantiateSlideView
	: hamon::false_type {};

template <typename V>
struct CanInstantiateSlideView<V, hamon::void_t<hamon::ranges::slide_view<V>>>
	: hamon::true_type {};

static_assert( CanInstantiateSlideView<test_forward_view<int>>::value, "");
static_assert(!CanInstantiateSlideView<test_input_view<int>>::value, "");		// requires forward_range<V>
static_assert(!CanInstantiateSlideView<test_forward_range<int>>::value, "");	// requires view<V>

}	// namespace instantiate_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
