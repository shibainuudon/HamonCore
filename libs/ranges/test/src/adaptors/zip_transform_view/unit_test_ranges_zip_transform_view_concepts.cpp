/**
 *	@file	unit_test_ranges_zip_transform_view_concepts.cpp
 *
 *	@brief	zip_transform_view のテスト
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace concepts_test
{

struct Add
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

struct F
{
	constexpr int operator()(int x) const { return x; }
};

GTEST_TEST(RangesTest, ZipTransformViewConceptsTest)
{
	{
		using T = int;
		using V = test_input_view<T>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}
	{
		using T = int;
		using V = test_forward_view<T>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert( hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert( hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_random_access_view<T>;
		using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert( hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_contiguous_view<T>;
		using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert( hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_bidirectional_view<T>;
		using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_forward_view<T>;
		using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}

	// constant
	{
		using T = int;
		using V = test_input_view<T const>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_forward_borrowed_view<T>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}

	// common
	{
		using T = int;
		using V = test_bidirectional_common_view<T>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert( hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_common_view<T>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( hamon::ranges::range_t<ZV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<ZV>::value, "");
		static_assert( hamon::ranges::sized_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::output_range_t<ZV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<ZV>::value, "");
		static_assert( hamon::ranges::forward_range_t<ZV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<ZV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<ZV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<ZV>::value, "");
		static_assert( hamon::ranges::common_range_t<ZV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<ZV>::value, "");
		static_assert( hamon::ranges::view_t<ZV>::value, "");
		static_assert( hamon::ranges::constant_range_t<ZV>::value, "");
	}
}

}	// namespace concepts_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
