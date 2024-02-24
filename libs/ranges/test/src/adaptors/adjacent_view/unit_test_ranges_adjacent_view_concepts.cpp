/**
 *	@file	unit_test_ranges_adjacent_view_concepts.cpp
 *
 *	@brief	adjacent_view のテスト
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace concepts_test
{

GTEST_TEST(RangesTest, AdjacentViewConceptsTest)
{
	{
		using T = int;
		using V = test_forward_view<T>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<AV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<AV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range_t<AV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<AV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<AV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<AV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range_t<AV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<AV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<AV>::value, "");
		static_assert( hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<AV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range_t<AV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<AV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<AV>::value, "");
		static_assert( hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<AV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range_t<AV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<AV>::value, "");
	}

	// constant
	{
		using T = int;
		using V = test_forward_view<T const>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<AV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<AV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range_t<AV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert( hamon::ranges::constant_range_t<AV>::value, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_forward_borrowed_view<T>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert( hamon::ranges::borrowed_range_t<AV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<AV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert(!hamon::ranges::common_range_t<AV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<AV>::value, "");
	}

	// common
	{
		using T = int;
		using V = test_bidirectional_common_view<T>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<AV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<AV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert( hamon::ranges::common_range_t<AV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<AV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_common_view<T>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		static_assert( hamon::ranges::range_t<AV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<AV>::value, "");
		static_assert( hamon::ranges::sized_range_t<AV>::value, "");
		static_assert(!hamon::ranges::output_range_t<AV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<AV>::value, "");
		static_assert( hamon::ranges::forward_range_t<AV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<AV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<AV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<AV>::value, "");
		static_assert( hamon::ranges::common_range_t<AV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<AV>::value, "");
		static_assert( hamon::ranges::view_t<AV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<AV>::value, "");
	}
}

}	// namespace concepts_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
