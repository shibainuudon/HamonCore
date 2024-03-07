/**
 *	@file	unit_test_ranges_cartesian_product_view_concepts.cpp
 *
 *	@brief	cartesian_product_view のテスト
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
{
namespace concepts_test
{

GTEST_TEST(RangesTest, CartesianProductViewConceptsTest)
{
	{
		using T = int;
		using V = test_input_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert(!hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_forward_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_input_view<T>;
		using V2 = test_forward_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert(!hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_forward_view<T>;
		using V2 = test_forward_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_bidirectional_view<T>;
		using V2 = test_forward_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_forward_view<T>;
		using V2 = test_bidirectional_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_bidirectional_view<T>;
		using V2 = test_bidirectional_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_bidirectional_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_bidirectional_view<T>;
		using V2 = test_random_access_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_random_access_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_contiguous_view<T>;
		using V2 = test_contiguous_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}

	// constant
	{
		using T = int;
		using V = test_input_view<T const>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert(!hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_forward_view<T const>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T const>;
		using V2 = test_random_access_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_random_access_view<T const>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T const>;
		using V2 = test_random_access_view<T const>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_input_borrowed_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert(!hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_forward_borrowed_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_forward_borrowed_view<T>;
		using V2 = test_forward_borrowed_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}

	// common
	{
		using T = int;
		using V = test_input_common_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert(!hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_forward_common_view<T>;
		using V2 = test_forward_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_forward_view<T>;
		using V2 = test_forward_common_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_forward_common_view<T>;
		using V2 = test_forward_common_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}

	// sized
	{
		using T = int;
		using V = test_input_sized_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert(!hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_forward_sized_view<T>;
		using V2 = test_forward_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_forward_view<T>;
		using V2 = test_forward_sized_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V1 = test_forward_sized_view<T>;
		using V2 = test_forward_sized_view<T>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
}

}	// namespace concepts_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
