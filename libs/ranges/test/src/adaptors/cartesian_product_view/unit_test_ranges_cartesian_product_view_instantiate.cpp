/**
 *	@file	unit_test_ranges_cartesian_product_view_instantiate.cpp
 *
 *	@brief	cartesian_product_view のテスト
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
{
namespace instantiate_test
{

template <typename... Ts>
struct CanInstantiateCartesianProductViewImpl
{
private:
	template <typename... Us,
		typename = hamon::ranges::cartesian_product_view<Us...>>
	static auto test(int) -> hamon::true_type;

	template <typename... Us>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Ts...>(0));
};

template <typename... Ts>
using CanInstantiateCartesianProductView = 
	typename CanInstantiateCartesianProductViewImpl<Ts...>::type;

static_assert( CanInstantiateCartesianProductView<test_input_view<int>>::value, "");
static_assert( CanInstantiateCartesianProductView<test_input_view<int>, test_forward_view<int>>::value, "");
static_assert( CanInstantiateCartesianProductView<test_input_view<int>, test_forward_view<int>, test_forward_view<int>>::value, "");

#if defined(HAMON_HAS_CXX20_CONCEPTS)
static_assert(!CanInstantiateCartesianProductView<test_output_view<int>>::value, "");	// input_range<First>
static_assert(!CanInstantiateCartesianProductView<test_input_range<int>>::value, "");	// view<First>

static_assert(!CanInstantiateCartesianProductView<test_output_view<int>, test_forward_view<int>>::value, "");	// input_range<First>
static_assert(!CanInstantiateCartesianProductView<test_input_range<int>, test_forward_view<int>>::value, "");	// view<First>
static_assert(!CanInstantiateCartesianProductView<test_input_view<int>,  test_input_view<int>>::value, "");		// forward_range<Vs>
static_assert(!CanInstantiateCartesianProductView<test_input_view<int>,  test_forward_range<int>>::value, "");	// view<Vs>

static_assert(!CanInstantiateCartesianProductView<test_output_view<int>, test_forward_view<int>,  test_forward_view<int>>::value, "");	// input_range<First>
static_assert(!CanInstantiateCartesianProductView<test_input_range<int>, test_forward_view<int>,  test_forward_view<int>>::value, "");	// view<First>
static_assert(!CanInstantiateCartesianProductView<test_input_view<int>,  test_input_view<int>,    test_forward_view<int>>::value, "");	// forward_range<Vs>
static_assert(!CanInstantiateCartesianProductView<test_input_view<int>,  test_forward_view<int>,  test_input_view<int>>::value, "");	// forward_range<Vs>
static_assert(!CanInstantiateCartesianProductView<test_input_view<int>,  test_forward_range<int>, test_forward_view<int>>::value, "");	// view<Vs>
static_assert(!CanInstantiateCartesianProductView<test_input_view<int>,  test_forward_view<int>,  test_forward_range<int>>::value, "");	// view<Vs>
#endif

}	// namespace instantiate_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
