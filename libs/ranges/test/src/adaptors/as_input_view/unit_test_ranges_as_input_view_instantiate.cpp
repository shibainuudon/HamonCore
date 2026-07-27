/**
 *	@file	unit_test_ranges_as_input_view_instantiate.cpp
 *
 *	@brief	as_input_view のテスト
 *
 *	template<input_range V>
 *		requires view<V>
 *	class as_input_view;
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace instantiate_test
{

template <typename V, typename = void>
struct CanInstantiateAsInputView
	: hamon::false_type {};

template <typename V>
struct CanInstantiateAsInputView<V, hamon::void_t<hamon::ranges::as_input_view<V>>>
	: hamon::true_type {};

static_assert(!CanInstantiateAsInputView<test_output_view<int>>::value, "");
static_assert( CanInstantiateAsInputView<test_input_view<int>>::value, "");
static_assert( CanInstantiateAsInputView<test_forward_view<int>>::value, "");

static_assert(!CanInstantiateAsInputView<test_input_range<int>>::value, "");
static_assert(!CanInstantiateAsInputView<test_forward_range<int>>::value, "");

}	// namespace instantiate_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
