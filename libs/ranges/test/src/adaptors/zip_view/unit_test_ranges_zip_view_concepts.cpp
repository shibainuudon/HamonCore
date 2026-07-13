/**
 *	@file	unit_test_ranges_zip_view_concepts.cpp
 *
 *	@brief	zip_view のテスト
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace concepts_test
{

GTEST_TEST(RangesTest, ZipViewConceptsTest)
{
	{
		using T = int;
		using V = test_input_view<T>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert(!hamon::ranges::forward_range<ZV>, "");
		static_assert(!hamon::ranges::bidirectional_range<ZV>, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert(!hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}
	{
		using T = int;
		using V = test_forward_view<T>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert(!hamon::ranges::bidirectional_range<ZV>, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert(!hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert( hamon::ranges::bidirectional_range<ZV>, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert(!hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert( hamon::ranges::bidirectional_range<ZV>, "");
		static_assert( hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert( hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert( hamon::ranges::bidirectional_range<ZV>, "");
		static_assert( hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert( hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_random_access_view<T>;
		using ZV = hamon::ranges::zip_view<V1, V2>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert( hamon::ranges::bidirectional_range<ZV>, "");
		static_assert( hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert( hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_contiguous_view<T>;
		using ZV = hamon::ranges::zip_view<V1, V2>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert( hamon::ranges::bidirectional_range<ZV>, "");
		static_assert( hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert( hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_bidirectional_view<T>;
		using ZV = hamon::ranges::zip_view<V1, V2>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert( hamon::ranges::bidirectional_range<ZV>, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert(!hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_forward_view<T>;
		using ZV = hamon::ranges::zip_view<V1, V2>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert(!hamon::ranges::bidirectional_range<ZV>, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert(!hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}

	// constant
	{
		using T = int;
		using V = test_input_view<T const>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert(!hamon::ranges::forward_range<ZV>, "");
		static_assert(!hamon::ranges::bidirectional_range<ZV>, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert(!hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range<ZV>, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_forward_borrowed_view<T>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert( hamon::ranges::borrowed_range<ZV>, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert(!hamon::ranges::bidirectional_range<ZV>, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert(!hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}

	// common
	{
		using T = int;
		using V = test_bidirectional_common_view<T>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert( hamon::ranges::bidirectional_range<ZV>, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert( hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}
	{
		using T = int;
		using V = test_random_access_common_view<T>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert( hamon::ranges::forward_range<ZV>, "");
		static_assert( hamon::ranges::bidirectional_range<ZV>, "");
		static_assert( hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert( hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}

	// sized
	{
		using T = int;
		using V = test_input_sized_view<T>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert(!hamon::ranges::forward_range<ZV>, "");
		static_assert(!hamon::ranges::bidirectional_range<ZV>, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert(!hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}

	// approximately_sized
	{
		using T = int;
		using V = test_input_approximately_sized_view<T>;
		using ZV = hamon::ranges::zip_view<V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<ZV>, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<ZV>, "");
		static_assert(!hamon::ranges::output_range<ZV, T>, "");
		static_assert( hamon::ranges::input_range<ZV>, "");
		static_assert(!hamon::ranges::forward_range<ZV>, "");
		static_assert(!hamon::ranges::bidirectional_range<ZV>, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range<ZV>, "");
		static_assert(!hamon::ranges::common_range<ZV>, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert(!hamon::ranges::constant_range<ZV>, "");
	}
}

}	// namespace concepts_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
