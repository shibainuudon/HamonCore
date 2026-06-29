/**
 *	@file	unit_test_ranges_concat_view_concepts.cpp
 *
 *	@brief	concat_view のテスト
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace concepts_test
{

GTEST_TEST(RangesTest, ConcatViewConceptsTest)
{
	{
		using T = int;
		using V = test_input_view<T>;
		using CV = hamon::ranges::concat_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert(!hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_forward_view<T>;
		using CV = hamon::ranges::concat_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using CV = hamon::ranges::concat_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using CV = hamon::ranges::concat_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert( hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert( hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using CV = hamon::ranges::concat_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert( hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert( hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}

	{
		using T = int;
		using V1 = test_input_view<T>;
		using V2 = test_random_access_view<T>;
		using V3 = test_random_access_view<T>;
		using CV = hamon::ranges::concat_view<V1, V2, V3>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert(!hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_forward_view<T>;
		using V3 = test_random_access_view<T>;
		using CV = hamon::ranges::concat_view<V1, V2, V3>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_random_access_view<T>;
		using V3 = test_bidirectional_view<T>;
		using CV = hamon::ranges::concat_view<V1, V2, V3>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V1 = test_random_access_view<T>;
		using V2 = test_random_access_view<T>;
		using V3 = test_random_access_view<T>;
		using CV = hamon::ranges::concat_view<V1, V2, V3>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert( hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}

	// random_access_range
	{
		using T = int;
		using V1 = test_random_access_common_view<T>;
		using V2 = test_random_access_common_view<T>;
		using V3 = test_random_access_view<T>;
		using CV = hamon::ranges::concat_view<V1, V2, V3>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert( hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert( hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}

	// common_range
	{
		using T = int;
		using V1 = test_input_view<T>;
		using V2 = test_input_view<T>;
		using V3 = test_input_common_view<T>;
		using CV = hamon::ranges::concat_view<V1, V2, V3>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert(!hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V1 = test_forward_view<T>;
		using V2 = test_forward_view<T>;
		using V3 = test_forward_common_view<T>;
		using CV = hamon::ranges::concat_view<V1, V2, V3>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}

	// sized_range
	{
		using T = int;
		using V1 = test_input_sized_view<T>;
		using V2 = test_input_sized_view<T>;
		using V3 = test_input_sized_view<T>;
		using CV = hamon::ranges::concat_view<V1, V2, V3>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert( hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert(!hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}

	// approximately_sized_range
	{
		using T = int;
		using V1 = test_input_approximately_sized_view<T>;
		using V2 = test_input_approximately_sized_view<T>;
		using V3 = test_input_approximately_sized_view<T>;
		using CV = hamon::ranges::concat_view<V1, V2, V3>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert(!hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
}

}	// namespace concepts_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
