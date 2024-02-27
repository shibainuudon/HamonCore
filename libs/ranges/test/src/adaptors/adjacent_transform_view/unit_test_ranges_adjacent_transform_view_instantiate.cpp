/**
 *	@file	unit_test_ranges_adjacent_transform_view_instantiate.cpp
 *
 *	@brief	adjacent_transform_view のテスト
 *
 *	template<forward_range V, move_constructible F, size_t N>
 *	  requires view<V> && (N > 0) && is_object_v<F> &&
 *	    regular_invocable<F&, REPEAT(range_reference_t<V>, N)...> &&
 *	    can-reference<invoke_result_t<F&, REPEAT(range_reference_t<V>, N)...>>
 *  class adjacent_transform_view;
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace instantiate_test
{

struct F0
{
	int operator()() const;
};

struct F1
{
	int operator()(int) const;
};

struct F2
{
	int operator()(int, int) const;
};

struct F3
{
	void operator()(int, int) const;
};

struct F4
{
	F4(F4&&) = delete;
	int operator()(int, int) const;
};

template <typename V, typename F, hamon::size_t N, typename = void>
struct CanInstantiateAdjacentTransformView
	: hamon::false_type {};

template <typename V, typename F, hamon::size_t N>
struct CanInstantiateAdjacentTransformView<V, F, N, hamon::void_t<hamon::ranges::adjacent_transform_view<V, F, N>>>
	: hamon::true_type {};

static_assert(!CanInstantiateAdjacentTransformView<test_forward_view<int>, F0, 0>::value, "");	// requires N > 0
static_assert( CanInstantiateAdjacentTransformView<test_forward_view<int>, F1, 1>::value, "");
static_assert(!CanInstantiateAdjacentTransformView<test_forward_view<int>, F1, 2>::value, "");	// requires regular_invocable<F&, REPEAT(range_reference_t<V>, N)...>
static_assert(!CanInstantiateAdjacentTransformView<test_forward_view<int>, F2, 1>::value, "");	// requires regular_invocable<F&, REPEAT(range_reference_t<V>, N)...>
static_assert( CanInstantiateAdjacentTransformView<test_forward_view<int>, F2, 2>::value, "");
static_assert(!CanInstantiateAdjacentTransformView<test_forward_view<int>, F3, 2>::value, "");	// requires can-reference<invoke_result_t<F&, REPEAT(range_reference_t<V>, N)...>>
static_assert(!CanInstantiateAdjacentTransformView<test_forward_view<int>, F4, 2>::value, "");	// requires move_constructible<F>
static_assert(!CanInstantiateAdjacentTransformView<test_input_view<int>, F2, 2>::value, "");	// requires forward_range<V>
static_assert(!CanInstantiateAdjacentTransformView<test_forward_range<int>, F2, 2>::value, "");	// requires view<V>
static_assert(!CanInstantiateAdjacentTransformView<test_forward_view<int>, F2&, 2>::value, "");	// requires is_object_v<F>

}	// namespace instantiate_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
