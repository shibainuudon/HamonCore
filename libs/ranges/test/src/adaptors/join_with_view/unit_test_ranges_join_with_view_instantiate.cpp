/**
 *	@file	unit_test_ranges_join_with_view_instantiate.cpp
 *
 *	@brief	ranges::join_with_view のテスト
 * 
 *	template<input_range V, forward_range Pattern>
 *		requires view<V> && input_range<range_reference_t<V>> &&
 *			view<Pattern> && compatible-joinable-ranges<range_reference_t<V>, Pattern>
 *	class join_with_view;
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace instantiate_test
{

template <typename T, typename U, typename = void>
struct CanInstantiateJoinWithView
	: hamon::false_type {};

template <typename T, typename U>
struct CanInstantiateJoinWithView<T, U, hamon::void_t<hamon::ranges::join_with_view<T, U>>>
	: hamon::true_type {};

static_assert( CanInstantiateJoinWithView<test_input_view<test_input_range<int>>, test_forward_view<int>>::value, "");
static_assert(!CanInstantiateJoinWithView<test_output_view<test_input_range<int>>, test_forward_view<int>>::value, "");	// requires ranges::input_range<V>
static_assert(!CanInstantiateJoinWithView<test_input_view<test_input_range<int>>, test_input_view<int>>::value, "");	// requires forward_range<Pattern>
static_assert(!CanInstantiateJoinWithView<test_input_range<test_input_range<int>>, test_forward_view<int>>::value, "");	// requires view<V>
static_assert(!CanInstantiateJoinWithView<test_input_view<test_output_range<int>>, test_forward_view<int>>::value, "");	// requires input_range<range_reference_t<V>>
static_assert(!CanInstantiateJoinWithView<test_input_view<test_input_range<int>>, test_forward_range<int>>::value, "");	// requires view<Pattern>
static_assert( CanInstantiateJoinWithView<test_input_view<test_input_range<int*>>, test_forward_view<int*>>::value, "");
static_assert(!CanInstantiateJoinWithView<test_input_view<test_input_range<int >>, test_forward_view<int*>>::value, "");
static_assert(!CanInstantiateJoinWithView<test_input_view<test_input_range<int*>>, test_forward_view<int >>::value, "");

}	// namespace instantiate_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
