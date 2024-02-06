/**
 *	@file	unit_test_ranges_common_view_concepts.cpp
 *
 *	@brief	common_view のテスト
 */

#include <hamon/ranges/adaptors/common_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace common_view_test
{
namespace concepts_test
{

GTEST_TEST(RangesTest, CommonViewConceptsTest)
{
	{
		using T = int;
		using V = test_input_view<T>;
		using CV = hamon::ranges::common_view<V>;
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
	}
	{
		using T = int;
		using V = test_forward_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert( hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_input_borrowed_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
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
	}
	{
		using T = int;
		using V = test_forward_borrowed_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_borrowed_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_borrowed_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_borrowed_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert( hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}

	// sized
	{
		using T = int;
		using V = test_input_sized_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert(!hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_forward_sized_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_sized_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_sized_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_sized_view<T>;
		using CV = hamon::ranges::common_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert( hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert( hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
	}
}

}	// namespace concepts_test
}	// namespace common_view_test
}	// namespace hamon_ranges_test
