/**
 *	@file	unit_test_ranges_as_const_view_concepts.cpp
 *
 *	@brief	as_const_view のテスト
 */

#include <hamon/ranges/adaptors/as_const_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_const_view_test
{
namespace concepts_test
{

GTEST_TEST(RangesTest, AsConstViewConceptsTest)
{
	{
		using T = int;
		using V = test_input_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_forward_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert( hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}

	// constant
	{
		using T = int const;
		using V = test_input_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert( hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int const;
		using V = test_forward_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert( hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int const;
		using V = test_bidirectional_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert( hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int const;
		using V = test_random_access_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert( hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int const;
		using V = test_contiguous_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert( hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert( hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}

	// borrowed
	{
		using T = int;
		using V = test_input_borrowed_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
		static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
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
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_forward_borrowed_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_borrowed_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
		static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
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
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_borrowed_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
		static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
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
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_borrowed_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
		static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert( hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert(!hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}

	// common
	{
		using T = int;
		using V = test_input_common_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_forward_common_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
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
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_bidirectional_common_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert(!hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_random_access_common_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
	{
		using T = int;
		using V = test_contiguous_common_view<T>;
		using CV = hamon::ranges::as_const_view<V>;
		static_assert(!hamon::ranges::borrowed_range_t<CV>::value, "");
		static_assert( hamon::ranges::sized_range_t<CV>::value, "");
		static_assert(!hamon::ranges::output_range_t<CV, T>::value, "");
		static_assert( hamon::ranges::input_range_t<CV>::value, "");
		static_assert( hamon::ranges::forward_range_t<CV>::value, "");
		static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
		static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
		static_assert( hamon::ranges::contiguous_range_t<CV>::value, "");
		static_assert( hamon::ranges::common_range_t<CV>::value, "");
		static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
		static_assert( hamon::ranges::view_t<CV>::value, "");
		static_assert(!hamon::ranges::constant_range_t<V>::value, "");
		static_assert( hamon::ranges::constant_range_t<CV>::value, "");
	}
}

}	// namespace concepts_test
}	// namespace as_const_view_test
}	// namespace hamon_ranges_test
