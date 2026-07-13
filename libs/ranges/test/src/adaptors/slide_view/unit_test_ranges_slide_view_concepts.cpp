/**
 *	@file	unit_test_ranges_slide_view_concepts.cpp
 *
 *	@brief	slide_view のテスト
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace slide_view_test
{
namespace concepts_test
{

GTEST_TEST(RangesTest, SlideViewConceptsTest)
{
	{
		using T = int;
		using V = test_forward_view<T>;
		using SV = hamon::ranges::slide_view<V>;
		static_assert( hamon::ranges::range_t<SV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range_t<SV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range_t<SV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<SV>::value, "");
		static_assert( hamon::ranges::forward_range_t<SV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range_t<SV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<SV>::value, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<SV>::value, "");

		using IV = hamon::ranges::range_reference_t<SV>;
		static_assert( hamon::ranges::range_t<IV>::value, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range_t<IV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range_t<IV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<IV>::value, "");
		static_assert( hamon::ranges::forward_range_t<IV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range_t<IV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<IV>::value, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range_t<IV>::value, "");
		static_assert( hamon::ranges::view_t<IV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<IV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using SV = hamon::ranges::slide_view<V>;
		static_assert( hamon::ranges::range_t<SV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range_t<SV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range_t<SV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<SV>::value, "");
		static_assert( hamon::ranges::forward_range_t<SV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range_t<SV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<SV>::value, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<SV>::value, "");

		using IV = hamon::ranges::range_reference_t<SV>;
		static_assert( hamon::ranges::range_t<IV>::value, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range_t<IV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range_t<IV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<IV>::value, "");
		static_assert( hamon::ranges::forward_range_t<IV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range_t<IV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<IV>::value, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range_t<IV>::value, "");
		static_assert( hamon::ranges::view_t<IV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<IV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using SV = hamon::ranges::slide_view<V>;
		static_assert( hamon::ranges::range_t<SV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert( hamon::ranges::sized_range_t<SV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range_t<SV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<SV>::value, "");
		static_assert( hamon::ranges::forward_range_t<SV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<SV>, "");
		static_assert( hamon::ranges::random_access_range_t<SV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<SV>::value, "");
		static_assert( hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<SV>::value, "");

		using IV = hamon::ranges::range_reference_t<SV>;
		static_assert( hamon::ranges::range_t<IV>::value, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range_t<IV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range_t<IV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<IV>::value, "");
		static_assert( hamon::ranges::forward_range_t<IV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<IV>, "");
		static_assert( hamon::ranges::random_access_range_t<IV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<IV>::value, "");
		static_assert( hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range_t<IV>::value, "");
		static_assert( hamon::ranges::view_t<IV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<IV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using SV = hamon::ranges::slide_view<V>;
		static_assert( hamon::ranges::range_t<SV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert( hamon::ranges::sized_range_t<SV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range_t<SV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<SV>::value, "");
		static_assert( hamon::ranges::forward_range_t<SV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<SV>, "");
		static_assert( hamon::ranges::random_access_range_t<SV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<SV>::value, "");
		static_assert( hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<SV>::value, "");

		using IV = hamon::ranges::range_reference_t<SV>;
		static_assert( hamon::ranges::range_t<IV>::value, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range_t<IV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range_t<IV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<IV>::value, "");
		static_assert( hamon::ranges::forward_range_t<IV>::value, "");
		static_assert( hamon::ranges::bidirectional_range<IV>, "");
		static_assert( hamon::ranges::random_access_range_t<IV>::value, "");
		static_assert( hamon::ranges::contiguous_range_t<IV>::value, "");
		static_assert( hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range_t<IV>::value, "");
		static_assert( hamon::ranges::view_t<IV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<IV>::value, "");
	}

	// constant
	{
		using T = int;
		using V = test_forward_view<T const>;
		using SV = hamon::ranges::slide_view<V>;
		static_assert( hamon::ranges::range_t<SV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range_t<SV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range_t<SV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<SV>::value, "");
		static_assert( hamon::ranges::forward_range_t<SV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range_t<SV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<SV>::value, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<SV>::value, "");

		using IV = hamon::ranges::range_reference_t<SV>;
		static_assert( hamon::ranges::range_t<IV>::value, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range_t<IV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert(!hamon::ranges::output_range_t<IV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<IV>::value, "");
		static_assert( hamon::ranges::forward_range_t<IV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range_t<IV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<IV>::value, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range_t<IV>::value, "");
		static_assert( hamon::ranges::view_t<IV>::value, "");
		static_assert( hamon::ranges::constant_range_t<IV>::value, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_forward_borrowed_view<T>;
		using SV = hamon::ranges::slide_view<V>;
		static_assert( hamon::ranges::range_t<SV>::value, "");
		static_assert( hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range_t<SV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range_t<SV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<SV>::value, "");
		static_assert( hamon::ranges::forward_range_t<SV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range_t<SV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<SV>::value, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<SV>::value, "");

		using IV = hamon::ranges::range_reference_t<SV>;
		static_assert( hamon::ranges::range_t<IV>::value, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range_t<IV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range_t<IV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<IV>::value, "");
		static_assert( hamon::ranges::forward_range_t<IV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range_t<IV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<IV>::value, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range_t<IV>::value, "");
		static_assert( hamon::ranges::view_t<IV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<IV>::value, "");
	}

	// common
	{
		using T = int;
		using V = test_forward_common_view<T>;
		using SV = hamon::ranges::slide_view<V>;
		static_assert( hamon::ranges::range_t<SV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range_t<SV>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range_t<SV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<SV>::value, "");
		static_assert( hamon::ranges::forward_range_t<SV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range_t<SV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<SV>::value, "");
		static_assert( hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<SV>::value, "");

		using IV = hamon::ranges::range_reference_t<SV>;
		static_assert( hamon::ranges::range_t<IV>::value, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range_t<IV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range_t<IV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<IV>::value, "");
		static_assert( hamon::ranges::forward_range_t<IV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range_t<IV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<IV>::value, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range_t<IV>::value, "");
		static_assert( hamon::ranges::view_t<IV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<IV>::value, "");
	}

	// sized
	{
		using T = int;
		using V = test_forward_sized_view<T>;
		using SV = hamon::ranges::slide_view<V>;
		static_assert( hamon::ranges::range_t<SV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert( hamon::ranges::sized_range_t<SV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range_t<SV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<SV>::value, "");
		static_assert( hamon::ranges::forward_range_t<SV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range_t<SV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<SV>::value, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<SV>::value, "");

		using IV = hamon::ranges::range_reference_t<SV>;
		static_assert( hamon::ranges::range_t<IV>::value, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range_t<IV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range_t<IV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<IV>::value, "");
		static_assert( hamon::ranges::forward_range_t<IV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range_t<IV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<IV>::value, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range_t<IV>::value, "");
		static_assert( hamon::ranges::view_t<IV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<IV>::value, "");
	}

	// approximately_sized
	{
		using T = int;
		using V = test_forward_approximately_sized_view<T>;
		using SV = hamon::ranges::slide_view<V>;
		static_assert( hamon::ranges::range_t<SV>::value, "");
		static_assert(!hamon::ranges::borrowed_range<SV>, "");
		static_assert(!hamon::ranges::sized_range_t<SV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<SV>, "");
		static_assert(!hamon::ranges::output_range_t<SV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<SV>::value, "");
		static_assert( hamon::ranges::forward_range_t<SV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<SV>, "");
		static_assert(!hamon::ranges::random_access_range_t<SV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<SV>::value, "");
		static_assert(!hamon::ranges::common_range<SV>, "");
		static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
		static_assert( hamon::ranges::view_t<SV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<SV>::value, "");

		using IV = hamon::ranges::range_reference_t<SV>;
		static_assert( hamon::ranges::range_t<IV>::value, "");
		static_assert( hamon::ranges::borrowed_range<IV>, "");
		static_assert( hamon::ranges::sized_range_t<IV>::value, "");
		static_assert( hamon::ranges::approximately_sized_range<IV>, "");
		static_assert( hamon::ranges::output_range_t<IV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<IV>::value, "");
		static_assert( hamon::ranges::forward_range_t<IV>::value, "");
		static_assert(!hamon::ranges::bidirectional_range<IV>, "");
		static_assert(!hamon::ranges::random_access_range_t<IV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<IV>::value, "");
		static_assert(!hamon::ranges::common_range<IV>, "");
		static_assert( hamon::ranges::viewable_range_t<IV>::value, "");
		static_assert( hamon::ranges::view_t<IV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<IV>::value, "");
	}
}

}	// namespace concepts_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
