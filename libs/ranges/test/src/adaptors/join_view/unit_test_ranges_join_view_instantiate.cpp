/**
 *	@file	unit_test_ranges_join_view_instantiate.cpp
 *
 *	@brief	ranges::join_view のテスト
 * 
 *	template<input_range V>
 *	  requires view<V> && input_range<range_reference_t<V>>
 *	class join_view;
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace instantiate_test
{

template <typename T, typename = void>
struct CanInstantiateJoinView
	: hamon::false_type {};

template <typename T>
struct CanInstantiateJoinView<T, hamon::void_t<hamon::ranges::join_view<T>>>
	: hamon::true_type {};

static_assert( CanInstantiateJoinView<test_input_view<test_input_view<int>>>::value, "");
static_assert( CanInstantiateJoinView<test_input_view<test_input_range<int>>>::value, "");
static_assert(!CanInstantiateJoinView<test_input_range<test_input_view<int>>>::value, "");
static_assert(!CanInstantiateJoinView<test_output_view<test_input_view<int>>>::value, "");
static_assert(!CanInstantiateJoinView<test_input_view<test_output_range<int>>>::value, "");
static_assert(!CanInstantiateJoinView<test_input_view<int>>::value, "");
static_assert(!CanInstantiateJoinView<int>::value, "");

}	// namespace instantiate_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
