/**
 *	@file	unit_test_ranges_adjacent_view_instantiate.cpp
 *
 *	@brief	adjacent_view のテスト
 *
 *	template<forward_range V, size_t N>
 *	  requires view<V> && (N > 0)
 *	class adjacent_view;
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace instantiate_test
{

template <typename V, hamon::size_t N, typename = void>
struct CanInstantiateAdjacentView
	: hamon::false_type {};

template <typename V, hamon::size_t N>
struct CanInstantiateAdjacentView<V, N, hamon::void_t<hamon::ranges::adjacent_view<V, N>>>
	: hamon::true_type {};

static_assert(!CanInstantiateAdjacentView<test_forward_view<int>, 0>::value, "");	// requires (N > 0)
static_assert( CanInstantiateAdjacentView<test_forward_view<int>, 1>::value, "");
static_assert( CanInstantiateAdjacentView<test_forward_view<int>, 2>::value, "");
static_assert(!CanInstantiateAdjacentView<test_input_view<int>, 2>::value, "");		// requires forward_range<V>
static_assert(!CanInstantiateAdjacentView<test_forward_range<int>, 2>::value, "");	// requires view<V>

}	// namespace instantiate_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
