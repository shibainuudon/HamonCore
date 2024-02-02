/**
 *	@file	unit_test_ranges_split_view_instantiate.cpp
 *
 *	@brief	ranges::split_view のテスト
 * 
 *	template<forward_range V, forward_range Pattern>
 *	  requires view<V> && view<Pattern> &&
 *	    indirectly_comparable<iterator_t<V>, iterator_t<Pattern>, ranges::equal_to>
 *	class split_view;
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace instantiate_test
{

template <typename T, typename U, typename = void>
struct CanInstantiateSplitView
	: hamon::false_type {};

template <typename T, typename U>
struct CanInstantiateSplitView<T, U, hamon::void_t<hamon::ranges::split_view<T, U>>>
	: hamon::true_type {};

static_assert( CanInstantiateSplitView<test_forward_view<int>,  test_forward_view<int>>::value, "");
static_assert(!CanInstantiateSplitView<test_input_view<int>,    test_forward_view<int>>::value, "");	// forward_range<V>
static_assert(!CanInstantiateSplitView<test_forward_view<int>,  test_input_view<int>>::value, "");		// forward_range<Pattern>
static_assert(!CanInstantiateSplitView<test_forward_range<int>, test_forward_view<int>>::value, "");	// view<V>
static_assert(!CanInstantiateSplitView<test_forward_view<int>,  test_forward_range<int>>::value, "");	// view<Pattern>
static_assert( CanInstantiateSplitView<test_forward_view<int*>,  test_forward_view<int*>>::value, "");
static_assert(!CanInstantiateSplitView<test_forward_view<int>,  test_forward_view<int*>>::value, "");	// indirectly_comparable<iterator_t<V>, iterator_t<Pattern>, ranges::equal_to>

}	// namespace instantiate_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
