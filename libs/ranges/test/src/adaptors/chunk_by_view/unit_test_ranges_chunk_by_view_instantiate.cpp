/**
 *	@file	unit_test_ranges_chunk_by_view_instantiate.cpp
 *
 *	@brief	chunk_by_view のテスト
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace instantiate_test
{

struct F1
{
	bool operator()(int, int) const;
};

struct F2
{
	bool operator()(int) const;
};

template <typename V, typename Pred, typename = void>
struct CanInstantiateChunkByView
	: hamon::false_type {};

template <typename V, typename Pred>
struct CanInstantiateChunkByView<V, Pred, hamon::void_t<hamon::ranges::chunk_by_view<V, Pred>>>
	: hamon::true_type {};

static_assert( CanInstantiateChunkByView<test_forward_view<int>, F1>::value, "");
static_assert(!CanInstantiateChunkByView<test_input_view<int>, F1>::value, "");		// requires forward_range<V>
static_assert(!CanInstantiateChunkByView<test_forward_view<int>, F2>::value, "");	// requires indirect_binary_predicate
static_assert(!CanInstantiateChunkByView<test_forward_range<int>, F1>::value, "");	// requires view<V>
static_assert(!CanInstantiateChunkByView<test_forward_view<int>, F1&>::value, "");	// requires is_object_v<Pred>

}	// namespace instantiate_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
