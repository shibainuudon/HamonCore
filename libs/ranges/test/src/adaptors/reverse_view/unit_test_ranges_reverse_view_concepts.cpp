/**
 *	@file	unit_test_ranges_reverse_view_concepts.cpp
 *
 *	@brief	reverse_view のテスト
 */

#include <hamon/ranges/adaptors/reverse_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace reverse_view_test
{
namespace concepts_test
{

GTEST_TEST(RangesTest, ReverseViewConceptsTest)
{
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
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
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
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
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
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
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_bidirectional_borrowed_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert( hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert(!hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_random_access_borrowed_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert( hamon::ranges::borrowed_range<CV>, "");
		static_assert( hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert( hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_contiguous_borrowed_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert( hamon::ranges::borrowed_range<CV>, "");
		static_assert( hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert( hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}

	// sized
	{
		using T = int;
		using V = test_bidirectional_sized_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert( hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_random_access_sized_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
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
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_contiguous_sized_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
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
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}

	// approximately_sized
	{
		using T = int;
		using V = test_bidirectional_approximately_sized_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
		static_assert( hamon::ranges::range<CV>, "");
		static_assert(!hamon::ranges::borrowed_range<CV>, "");
		static_assert(!hamon::ranges::sized_range<CV>, "");
		static_assert( hamon::ranges::approximately_sized_range<CV>, "");
		static_assert( hamon::ranges::output_range<CV, T>, "");
		static_assert( hamon::ranges::input_range<CV>, "");
		static_assert( hamon::ranges::forward_range<CV>, "");
		static_assert( hamon::ranges::bidirectional_range<CV>, "");
		static_assert(!hamon::ranges::random_access_range<CV>, "");
		static_assert(!hamon::ranges::contiguous_range<CV>, "");
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_random_access_approximately_sized_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
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
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
	{
		using T = int;
		using V = test_contiguous_approximately_sized_view<T>;
		using CV = hamon::ranges::reverse_view<V>;
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
		static_assert( hamon::ranges::common_range<CV>, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view<CV>, "");
		static_assert(!hamon::ranges::constant_range<CV>, "");
	}
}

}	// namespace concepts_test
}	// namespace reverse_view_test
}	// namespace hamon_ranges_test
