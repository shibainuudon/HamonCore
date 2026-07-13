/**
 *	@file	unit_test_ranges_stride_view_concepts.cpp
 *
 *	@brief	stride_view のテスト
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace concepts_test
{

GTEST_TEST(RangesTest, StrideViewConceptsTest)
{
	{
		using T = int;
		using V = test_input_view<T>;
		using SV = hamon::ranges::stride_view<V>;
		static_assert( hamon::ranges::range<SV>, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range<SV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range<SV, T>, "");
		static_assert( hamon::ranges::input_range<SV>, "");
		static_assert(!hamon::ranges::forward_range<SV>, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range<SV>, "");
		static_assert(!hamon::ranges::contiguous_range<SV>, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range<SV>, "");
	}
	{
		using T = int;
		using V = test_forward_view<T>;
		using SV = hamon::ranges::stride_view<V>;
		static_assert( hamon::ranges::range<SV>, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range<SV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert( hamon::ranges::output_range<SV, T>, "");
		static_assert( hamon::ranges::input_range<SV>, "");
		static_assert( hamon::ranges::forward_range<SV>, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range<SV>, "");
		static_assert(!hamon::ranges::contiguous_range<SV>, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range<SV>, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using SV = hamon::ranges::stride_view<V>;
		static_assert( hamon::ranges::range<SV>, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range<SV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert( hamon::ranges::output_range<SV, T>, "");
		static_assert( hamon::ranges::input_range<SV>, "");
		static_assert( hamon::ranges::forward_range<SV>, "");
		static_assert( hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range<SV>, "");
		static_assert(!hamon::ranges::contiguous_range<SV>, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range<SV>, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using SV = hamon::ranges::stride_view<V>;
		static_assert( hamon::ranges::range<SV>, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert( hamon::ranges::sized_range<SV>, "");
		static_assert( hamon::ranges::approximately_sized_range<SV>, "");
		static_assert( hamon::ranges::output_range<SV, T>, "");
		static_assert( hamon::ranges::input_range<SV>, "");
		static_assert( hamon::ranges::forward_range<SV>, "");
		static_assert( hamon::ranges::bidirectional_range<SV>, "");
		static_assert( hamon::ranges::random_access_range<SV>, "");
		static_assert(!hamon::ranges::contiguous_range<SV>, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range<SV>, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using SV = hamon::ranges::stride_view<V>;
		static_assert( hamon::ranges::range<SV>, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert( hamon::ranges::sized_range<SV>, "");
		static_assert( hamon::ranges::approximately_sized_range<SV>, "");
		static_assert( hamon::ranges::output_range<SV, T>, "");
		static_assert( hamon::ranges::input_range<SV>, "");
		static_assert( hamon::ranges::forward_range<SV>, "");
		static_assert( hamon::ranges::bidirectional_range<SV>, "");
		static_assert( hamon::ranges::random_access_range<SV>, "");
		static_assert(!hamon::ranges::contiguous_range<SV>, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range<SV>, "");
	}

	// constant
	{
		using T = int;
		using V = test_input_view<T const>;
		using SV = hamon::ranges::stride_view<V>;
		static_assert( hamon::ranges::range<SV>, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range<SV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range<SV, T>, "");
		static_assert( hamon::ranges::input_range<SV>, "");
		static_assert(!hamon::ranges::forward_range<SV>, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range<SV>, "");
		static_assert(!hamon::ranges::contiguous_range<SV>, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert( hamon::ranges::constant_range<SV>, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_input_borrowed_view<T>;
		using SV = hamon::ranges::stride_view<V>;
		static_assert( hamon::ranges::range<SV>, "");
		static_assert( hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range<SV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range<SV, T>, "");
		static_assert( hamon::ranges::input_range<SV>, "");
		static_assert(!hamon::ranges::forward_range<SV>, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range<SV>, "");
		static_assert(!hamon::ranges::contiguous_range<SV>, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range<SV>, "");
	}

	// common
	{
		using T = int;
		using V = test_input_common_view<T>;
		using SV = hamon::ranges::stride_view<V>;
		static_assert( hamon::ranges::range<SV>, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range<SV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range<SV, T>, "");
		static_assert( hamon::ranges::input_range<SV>, "");
		static_assert(!hamon::ranges::forward_range<SV>, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range<SV>, "");
		static_assert(!hamon::ranges::contiguous_range<SV>, "");
		static_assert( hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range<SV>, "");
	}

	// sized
	{
		using T = int;
		using V = test_input_sized_view<T>;
		using SV = hamon::ranges::stride_view<V>;
		static_assert( hamon::ranges::range<SV>, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert( hamon::ranges::sized_range<SV>, "");
		static_assert( hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range<SV, T>, "");
		static_assert( hamon::ranges::input_range<SV>, "");
		static_assert(!hamon::ranges::forward_range<SV>, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range<SV>, "");
		static_assert(!hamon::ranges::contiguous_range<SV>, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range<SV>, "");
	}

	// approximately_sized
	{
		using T = int;
		using V = test_input_approximately_sized_view<T>;
		using SV = hamon::ranges::stride_view<V>;
		static_assert( hamon::ranges::range<SV>, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range<SV>, "");
		static_assert( hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range<SV, T>, "");
		static_assert( hamon::ranges::input_range<SV>, "");
		static_assert(!hamon::ranges::forward_range<SV>, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range<SV>, "");
		static_assert(!hamon::ranges::contiguous_range<SV>, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range<SV>, "");
	}
}

}	// namespace concepts_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
