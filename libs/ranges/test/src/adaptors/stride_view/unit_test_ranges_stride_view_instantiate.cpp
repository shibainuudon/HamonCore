/**
 *	@file	unit_test_ranges_stride_view_instantiate.cpp
 *
 *	@brief	stride_view のテスト
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace instantiate_test
{

template <typename V, typename = void>
struct CanInstantiateStrideView
	: hamon::false_type {};

template <typename V>
struct CanInstantiateStrideView<V, hamon::void_t<hamon::ranges::stride_view<V>>>
	: hamon::true_type {};

static_assert( CanInstantiateStrideView<test_input_view<int>>::value, "");
static_assert(!CanInstantiateStrideView<test_output_view<int>>::value, "");		// requires input_range<V>
static_assert(!CanInstantiateStrideView<test_input_range<int>>::value, "");		// requires view<V>

}	// namespace instantiate_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
