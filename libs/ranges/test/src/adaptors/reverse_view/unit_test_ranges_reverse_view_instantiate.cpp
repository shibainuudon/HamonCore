/**
 *	@file	unit_test_ranges_reverse_view_instantiate.cpp
 *
 *	@brief	ranges::reverse_view のテスト
 *
 *	template<view V>
 *	  requires bidirectional_range<V>
 *	class reverse_view;
 */

#include <hamon/ranges/adaptors/reverse_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace reverse_view_test
{
namespace instantiate_test
{

template <typename T, typename = void>
struct CanInstantiateReverseView
	: hamon::false_type {};

template <typename T>
struct CanInstantiateReverseView<T, hamon::void_t<hamon::ranges::reverse_view<T>>>
	: hamon::true_type {};

static_assert( CanInstantiateReverseView<test_bidirectional_view<int>>::value, "");
static_assert(!CanInstantiateReverseView<test_bidirectional_range<int>>::value, "");	// requires view<V>
static_assert(!CanInstantiateReverseView<test_forward_view<int>>::value, "");			// requires bidirectional_range<V>

}	// namespace instantiate_test
}	// namespace reverse_view_test
}	// namespace hamon_ranges_test
