/**
 *	@file	unit_test_ranges_cache_latest_view_concepts.cpp
 *
 *	@brief	cache_latest_view のテスト
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace concepts_test
{

template <template <typename> class ViewWrapper>
void test()
{
	using T = int;
	using V = ViewWrapper<T>;
	using CLV = hamon::ranges::cache_latest_view<V>;

	static_assert( hamon::ranges::range<CLV>, "");
	static_assert(!hamon::ranges::borrowed_range<CLV>, "");
	static_assert( hamon::ranges::sized_range<CLV> == hamon::ranges::sized_range<V>, "");
	static_assert( hamon::ranges::approximately_sized_range<CLV> == hamon::ranges::approximately_sized_range<V>, "");
	static_assert(!hamon::ranges::output_range<CLV, T>, "");
	static_assert( hamon::ranges::input_range<CLV>, "");
	static_assert(!hamon::ranges::forward_range<CLV>, "");
	static_assert(!hamon::ranges::bidirectional_range<CLV>, "");
	static_assert(!hamon::ranges::random_access_range<CLV>, "");
	static_assert(!hamon::ranges::contiguous_range<CLV>, "");
	static_assert(!hamon::ranges::common_range<CLV>, "");
	static_assert( hamon::ranges::viewable_range<CLV>, "");
	static_assert( hamon::ranges::view<CLV>, "");
	static_assert(!hamon::ranges::constant_range<CLV>, "");
}

GTEST_TEST(RangesTest, CacheLatestViewConceptsTest)
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
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
