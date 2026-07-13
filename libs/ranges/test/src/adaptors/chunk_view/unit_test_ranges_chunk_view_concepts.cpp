/**
 *	@file	unit_test_ranges_chunk_view_concepts.cpp
 *
 *	@brief	chunk_view のテスト
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_view_test
{
namespace concepts_test
{

GTEST_TEST(RangesTest, ChunkViewConceptsTest)
{
	{
		using T = int;
		using V = test_input_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
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

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert(!hamon::ranges::borrowed_range<IV>, "");
		static_assert(!hamon::ranges::sized_range<IV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<IV>, "");
		static_assert(!hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert(!hamon::ranges::forward_range<IV>, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}
	{
		using T = int;
		using V = test_forward_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert(!hamon::ranges::sized_range<IV>, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert( hamon::ranges::forward_range<IV>, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert(!hamon::ranges::sized_range<IV>, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert( hamon::ranges::forward_range<IV>, "");
		static_assert( hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert( hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert( hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range<IV>, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert( hamon::ranges::forward_range<IV>, "");
		static_assert( hamon::ranges::bidirectional_range<IV>, "");
		static_assert( hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert( hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert( hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert( hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range<IV>, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert( hamon::ranges::forward_range<IV>, "");
		static_assert( hamon::ranges::bidirectional_range<IV>, "");
		static_assert( hamon::ranges::random_access_range<IV>, "");
		static_assert( hamon::ranges::contiguous_range<IV>, "");
		static_assert( hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}

	// constant
	{
		using T = int;
		using V = test_forward_view<T const>;
		using CV = hamon::ranges::chunk_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert(!hamon::ranges::sized_range<IV>, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert(!hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert( hamon::ranges::forward_range<IV>, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert( hamon::ranges::constant_range<IV>, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_input_borrowed_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
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

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert(!hamon::ranges::borrowed_range<IV>, "");
		static_assert(!hamon::ranges::sized_range<IV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<IV>, "");
		static_assert(!hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert(!hamon::ranges::forward_range<IV>, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}
	{
		using T = int;
		using V = test_forward_borrowed_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert( hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert(!hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert(!hamon::ranges::sized_range<IV>, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert( hamon::ranges::forward_range<IV>, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}

	// common
	{
		using T = int;
		using V = test_input_common_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
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

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert(!hamon::ranges::borrowed_range<IV>, "");
		static_assert(!hamon::ranges::sized_range<IV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<IV>, "");
		static_assert(!hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert(!hamon::ranges::forward_range<IV>, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}
	{
		using T = int;
		using V = test_forward_common_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert(!hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert(!hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range<CV>, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert(!hamon::ranges::sized_range<IV>, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert( hamon::ranges::forward_range<IV>, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}

	// sized
	{
		using T = int;
		using V = test_input_sized_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
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

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert(!hamon::ranges::borrowed_range<IV>, "");
		static_assert(!hamon::ranges::sized_range<IV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<IV>, "");
		static_assert(!hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert(!hamon::ranges::forward_range<IV>, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}

	// approximately_sized
	{
		using T = int;
		using V = test_input_approximately_sized_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
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

		using IV = hamon::ranges::range_reference_t<CV>;
		static_assert( hamon::ranges::range<IV>, "");
		static_assert(!hamon::ranges::borrowed_range<IV>, "");
		static_assert(!hamon::ranges::sized_range<IV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<IV>, "");
		static_assert(!hamon::ranges::output_range<IV, T>, "");
		static_assert( hamon::ranges::input_range<IV>, "");
		static_assert(!hamon::ranges::forward_range<IV>, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range<IV>, "");
		static_assert(!hamon::ranges::contiguous_range<IV>, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range<IV>, "");
		static_assert( hamon::ranges::view<IV>, "");
		static_assert(!hamon::ranges::constant_range<IV>, "");
	}
}

}	// namespace concepts_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
