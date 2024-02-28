/**
 *	@file	unit_test_ranges_chunk_view_concepts.cpp
 *
 *	@brief	chunk_view のテスト
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/ranges/concepts.hpp>
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
		using CV = hamon::ranges::chunk_view<V>;
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
		using CV = hamon::ranges::chunk_view<V>;
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
		using CV = hamon::ranges::chunk_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<CV>::value, "");
	}

	// constant
	{
		using T = int;
		using V = test_forward_view<T const>;
		using CV = hamon::ranges::chunk_view<V>;
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

	// borrowed
	{
		using T = int;
		using V = test_input_borrowed_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
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
		using CV = hamon::ranges::chunk_view<V>;
		static_assert( hamon::ranges::range_t<CV>::value, "");
		static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
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
		using CV = hamon::ranges::chunk_view<V>;
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
		using V = test_forward_common_view<T>;
		using CV = hamon::ranges::chunk_view<V>;
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
}

}	// namespace concepts_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
