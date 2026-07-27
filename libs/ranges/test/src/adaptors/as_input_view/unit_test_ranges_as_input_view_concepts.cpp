/**
 *	@file	unit_test_ranges_as_input_view_concepts.cpp
 *
 *	@brief	as_input_view のテスト
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace concepts_test
{

template <template <typename> class ViewWrapper>
void test()
{
	using T = int;
	using V = ViewWrapper<T>;
	using AIV = hamon::ranges::as_input_view<V>;

	static_assert( hamon::ranges::range<AIV>, "");
	static_assert( hamon::ranges::borrowed_range<AIV> == hamon::ranges::borrowed_range<V>, "");
	static_assert( hamon::ranges::sized_range<AIV> == hamon::ranges::sized_range<V>, "");
	static_assert( hamon::ranges::approximately_sized_range<AIV> == hamon::ranges::approximately_sized_range<V>, "");
	static_assert(!hamon::ranges::output_range<AIV, T>, "");
	static_assert( hamon::ranges::input_range<AIV>, "");
	static_assert(!hamon::ranges::forward_range<AIV>, "");
	static_assert(!hamon::ranges::bidirectional_range<AIV>, "");
	static_assert(!hamon::ranges::random_access_range<AIV>, "");
	static_assert(!hamon::ranges::contiguous_range<AIV>, "");
	static_assert(!hamon::ranges::common_range<AIV>, "");
	static_assert( hamon::ranges::viewable_range<AIV>, "");
	static_assert( hamon::ranges::view<AIV>, "");
	static_assert(!hamon::ranges::constant_range<AIV>, "");
}

GTEST_TEST(RangesTest, AsInputViewConceptsTest)
{
	test<test_input_view>();
	test<test_forward_view>();
	test<test_bidirectional_view>();
	test<test_random_access_view>();
	test<test_contiguous_view>();

	test<test_input_common_view>();
	test<test_input_borrowed_view>();
	test<test_input_sized_view>();
	test<test_input_approximately_sized_view>();
}

}	// namespace concepts_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
