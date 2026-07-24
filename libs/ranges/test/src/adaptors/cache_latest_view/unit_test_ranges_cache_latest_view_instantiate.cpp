/**
 *	@file	unit_test_ranges_cache_latest_view_instantiate.cpp
 *
 *	@brief	cache_latest_view のテスト
 *
 *	template <input_range V>
 *		requires view<V>
 *	class cache_latest_view;
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace instantiate_test
{

template <typename V, typename = void>
struct CanInstantiateCacheLatestView
	: hamon::false_type {};

template <typename V>
struct CanInstantiateCacheLatestView<V, hamon::void_t<hamon::ranges::cache_latest_view<V>>>
	: hamon::true_type {};

static_assert(!CanInstantiateCacheLatestView<test_output_view<int>>::value, "");
static_assert( CanInstantiateCacheLatestView<test_input_view<int>>::value, "");
static_assert( CanInstantiateCacheLatestView<test_forward_view<int>>::value, "");

static_assert(!CanInstantiateCacheLatestView<test_input_range<int>>::value, "");
static_assert(!CanInstantiateCacheLatestView<test_forward_range<int>>::value, "");

}	// namespace instantiate_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
