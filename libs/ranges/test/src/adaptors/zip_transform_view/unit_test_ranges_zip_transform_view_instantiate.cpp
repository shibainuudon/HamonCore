/**
 *	@file	unit_test_ranges_zip_transform_view_instantiate.cpp
 *
 *	@brief	zip_transform_view のテスト
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
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
	F2(F2&&) = delete;
	int operator()(int) const;
};

struct F3
{
	int operator()(int, float) const;
};

struct F4
{
	void operator()(int) const;
};

template <typename F, typename... Ts>
struct CanInstantiateZipTransformViewImpl
{
private:
	template <typename F2, typename... Us,
		typename = hamon::ranges::zip_transform_view<F2, Us...>>
	static auto test(int) -> hamon::true_type;

	template <typename F2, typename... Us>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<F, Ts...>(0));
};

template <typename F, typename... Ts>
using CanInstantiateZipTransformView = 
	typename CanInstantiateZipTransformViewImpl<F, Ts...>::type;

static_assert( CanInstantiateZipTransformView<F1, test_input_view<int>>::value, "");
static_assert( CanInstantiateZipTransformView<F3, test_input_view<int>, test_input_view<float>>::value, "");
#if defined(HAMON_HAS_CXX20_CONCEPTS)
static_assert(!CanInstantiateZipTransformView<F0>::value, "");	// requires (sizeof...(Views) > 0)
static_assert(!CanInstantiateZipTransformView<F1>::value, "");
static_assert(!CanInstantiateZipTransformView<F1, test_output_view<int>>::value, "");	// requires (input_range<Views> && ...)
static_assert(!CanInstantiateZipTransformView<F1, test_input_range<int>>::value, "");	// requires (view<Views> && ...)
static_assert(!CanInstantiateZipTransformView<F1&, test_input_view<int>>::value, "");	// requires is_object_v<F>
static_assert(!CanInstantiateZipTransformView<F2, test_input_view<int>>::value, "");	// requires move_constructible<F>
static_assert(!CanInstantiateZipTransformView<F3, test_input_view<int>>::value, "");	// requires regular_invocable<F&, range_reference_t<Views>...>
static_assert(!CanInstantiateZipTransformView<F3, test_input_view<int>, test_input_view<float>, test_input_view<int>>::value, "");
static_assert(!CanInstantiateZipTransformView<F1, test_input_view<int*>>::value, "");
static_assert(!CanInstantiateZipTransformView<F4, test_input_view<int>>::value, "");	// can_reference<invoke_result_t<F&, range_reference_t<Views>...>>
#endif

}	// namespace instantiate_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
