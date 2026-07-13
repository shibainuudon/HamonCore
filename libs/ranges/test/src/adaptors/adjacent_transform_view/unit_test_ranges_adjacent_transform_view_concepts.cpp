/**
 *	@file	unit_test_ranges_adjacent_transform_view_concepts.cpp
 *
 *	@brief	adjacent_transform_view のテスト
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace concepts_test
{

struct F
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

GTEST_TEST(RangesTest, AdjacentTransformViewConceptsTest)
{
	{
		using T = int;
		using V = test_forward_view<T>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<AV>, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<AV>, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<AV>, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range<AV>, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range<AV>, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<AV>, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<AV>, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<AV>, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range<AV>, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range<AV>, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<AV>, "");
		static_assert( hamon::ranges::sized_range_t<AV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<AV>, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<AV>, "");
		static_assert( hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range<AV>, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range<AV>, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<AV>, "");
		static_assert( hamon::ranges::sized_range_t<AV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<AV>, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<AV>, "");
		static_assert( hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range<AV>, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range<AV>, "");
	}

	// constant
	{
		using T = int;
		using V = test_forward_view<T const>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<AV>, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<AV>, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<AV>, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range<AV>, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range<AV>, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_forward_borrowed_view<T>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<AV>, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<AV>, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<AV>, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range<AV>, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range<AV>, "");
	}

	// common
	{
		using T = int;
		using V = test_bidirectional_common_view<T>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<AV>, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<AV>, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<AV>, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert( hamon::ranges::common_range<AV>, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range<AV>, "");
	}
	{
		using T = int;
		using V = test_random_access_common_view<T>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<AV>, "");
		static_assert( hamon::ranges::sized_range_t<AV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<AV>, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<AV>, "");
		static_assert( hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert( hamon::ranges::common_range<AV>, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range<AV>, "");
	}

	// sized
	{
		using T = int;
		using V = test_forward_sized_view<T>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<AV>, "");
		static_assert( hamon::ranges::sized_range_t<AV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<AV>, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<AV>, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range<AV>, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range<AV>, "");
	}

	// approximately_sized
	{
		using T = int;
		using V = test_forward_approximately_sized_view<T>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<AV>, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<AV>, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<AV>, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range<AV>, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range<AV>, "");
	}
}

}	// namespace concepts_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
