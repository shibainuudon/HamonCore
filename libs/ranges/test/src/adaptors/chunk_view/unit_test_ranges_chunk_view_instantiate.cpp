/**
 *	@file	unit_test_ranges_chunk_view_instantiate.cpp
 *
 *	@brief	chunk_view のテスト
 *
 *	template<view V>
 *	  requires input_range<V>
 *	class chunk_view;
 *
 *	template<view V>
 *	  requires forward_range<V>
 *	class chunk_view<V>;
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_view_test
{
namespace instantiate_test
{

template <typename V, typename = void>
struct CanInstantiateChunkView
	: hamon::false_type {};

template <typename V>
struct CanInstantiateChunkView<V, hamon::void_t<hamon::ranges::chunk_view<V>>>
	: hamon::true_type {};

static_assert( CanInstantiateChunkView<test_input_view<int>>::value, "");
static_assert( CanInstantiateChunkView<test_forward_view<int>>::value, "");
static_assert(!CanInstantiateChunkView<test_output_view<int>>::value, "");		// requires input_range<V>
static_assert(!CanInstantiateChunkView<test_input_range<int>>::value, "");		// requires view<V>
static_assert(!CanInstantiateChunkView<test_forward_range<int>>::value, "");	// requires view<V>

}	// namespace instantiate_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
