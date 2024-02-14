/**
 *	@file	unit_test_ranges_zip_view_instantiate.cpp
 *
 *	@brief	zip_view のテスト
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace instantiate_test
{

template <typename... Ts>
struct CanInstantiateZipViewImpl
{
private:
	template <typename... Us,
		typename = hamon::ranges::zip_view<Us...>>
	static auto test(int) -> hamon::true_type;

	template <typename... Us>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Ts...>(0));
};

template <typename... Ts>
using CanInstantiateZipView = 
	typename CanInstantiateZipViewImpl<Ts...>::type;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
static_assert(!CanInstantiateZipView<>::value, "");	// requires (sizeof...(Views) > 0)
#endif
static_assert( CanInstantiateZipView<test_input_view<int>>::value, "");
static_assert( CanInstantiateZipView<test_input_view<int>,  test_input_view<int>>::value, "");
#if defined(HAMON_HAS_CXX20_CONCEPTS)
static_assert(!CanInstantiateZipView<test_input_range<int>, test_input_view<int>>::value, "");	// requires view<Views> && ...
static_assert(!CanInstantiateZipView<test_input_view<int>,  test_input_range<int>>::value, "");	// requires view<Views> && ...
static_assert(!CanInstantiateZipView<test_output_view<int>, test_input_view<int>>::value, "");	// input_range input_range<Views> && ...
static_assert(!CanInstantiateZipView<test_input_view<int>,  test_output_view<int>>::value, "");	// input_range input_range<Views> && ...
#endif
static_assert( CanInstantiateZipView<test_input_view<int>, test_forward_view<float>, test_random_access_view<char>>::value, "");

}	// namespace instantiate_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
