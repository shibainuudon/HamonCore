/**
 *	@file	unit_test_ranges_split_view_concepts.cpp
 *
 *	@brief	split_view のテスト
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace concepts_test
{

template <template <typename> class V, template <typename> class P>
void test0()
{
	using T = int;
	using View = V<T>;
	using Pattern = P<T>;
	using SV = hamon::ranges::split_view<View, Pattern>;

	static_assert(hamon::ranges::range_t<SV>::value                     == true, "");
	static_assert(hamon::ranges::borrowed_range_t<SV>::value            == false, "");
	static_assert(hamon::ranges::sized_range_t<SV>::value               == false, "");
	static_assert(hamon::ranges::approximately_sized_range_t<SV>::value == false, "");
	static_assert(hamon::ranges::output_range_t<SV, T>::value           == false, "");
	static_assert(hamon::ranges::input_range_t<SV>::value               == true, "");
	static_assert(hamon::ranges::forward_range_t<SV>::value             == true, "");
	static_assert(hamon::ranges::bidirectional_range_t<SV>::value       == false, "");
	static_assert(hamon::ranges::random_access_range_t<SV>::value       == false, "");
	static_assert(hamon::ranges::contiguous_range_t<SV>::value          == false, "");
	static_assert(hamon::ranges::common_range_t<SV>::value              == hamon::ranges::common_range_t<View>::value, "");
	static_assert(hamon::ranges::viewable_range_t<SV>::value            == true, "");
	static_assert(hamon::ranges::view_t<SV>::value                      == true, "");
	static_assert(hamon::ranges::constant_range_t<SV>::value            == false, "");

	using IV = hamon::ranges::range_reference_t<SV>;
	using Iter = hamon::ranges::iterator_t<View>;

	static_assert(hamon::ranges::range_t<IV>::value                     == true, "");
	static_assert(hamon::ranges::borrowed_range_t<IV>::value            == true, "");
	static_assert(hamon::ranges::sized_range_t<IV>::value               == hamon::sized_sentinel_for<Iter, Iter>, "");
	static_assert(hamon::ranges::approximately_sized_range_t<IV>::value == hamon::sized_sentinel_for<Iter, Iter>, "");
	static_assert(hamon::ranges::output_range_t<IV, T>::value           == hamon::ranges::output_range_t<View, T>::value, "");
	static_assert(hamon::ranges::input_range_t<IV>::value               == true, "");
	static_assert(hamon::ranges::forward_range_t<IV>::value             == hamon::ranges::forward_range_t<View>::value, "");
	static_assert(hamon::ranges::bidirectional_range_t<IV>::value       == hamon::ranges::bidirectional_range_t<View>::value, "");
	static_assert(hamon::ranges::random_access_range_t<IV>::value       == hamon::ranges::random_access_range_t<View>::value, "");
	static_assert(hamon::ranges::contiguous_range_t<IV>::value          == hamon::ranges::contiguous_range_t<View>::value, "");
	static_assert(hamon::ranges::common_range_t<IV>::value              == true, "");
	static_assert(hamon::ranges::viewable_range_t<IV>::value            == true, "");
	static_assert(hamon::ranges::view_t<IV>::value                      == true, "");
	static_assert(hamon::ranges::constant_range_t<IV>::value            == false, "");
}

template <template <typename> class V>
void test()
{
	test0<V, test_forward_view>();
	test0<V, test_bidirectional_view>();
	test0<V, test_random_access_view>();
	test0<V, test_contiguous_view>();

	test0<V, test_forward_common_view>();
	test0<V, test_bidirectional_common_view>();
	test0<V, test_random_access_common_view>();
	test0<V, test_contiguous_common_view>();

	test0<V, test_forward_borrowed_view>();
	test0<V, test_bidirectional_borrowed_view>();
	test0<V, test_random_access_borrowed_view>();
	test0<V, test_contiguous_borrowed_view>();

	test0<V, test_forward_sized_view>();
	test0<V, test_bidirectional_sized_view>();
	test0<V, test_random_access_sized_view>();
	test0<V, test_contiguous_sized_view>();

	test0<V, test_forward_approximately_sized_view>();
	test0<V, test_bidirectional_approximately_sized_view>();
	test0<V, test_random_access_approximately_sized_view>();
	test0<V, test_contiguous_approximately_sized_view>();
}

GTEST_TEST(RangesTest, SplitViewConceptsTest)
{
	test<test_forward_view>();
	test<test_bidirectional_view>();
	test<test_random_access_view>();
	test<test_contiguous_view>();

	test<test_forward_common_view>();
	test<test_bidirectional_common_view>();
	test<test_random_access_common_view>();
	test<test_contiguous_common_view>();

	test<test_forward_borrowed_view>();
	test<test_bidirectional_borrowed_view>();
	test<test_random_access_borrowed_view>();
	test<test_contiguous_borrowed_view>();

	test<test_forward_sized_view>();
	test<test_bidirectional_sized_view>();
	test<test_random_access_sized_view>();
	test<test_contiguous_sized_view>();

	test<test_forward_approximately_sized_view>();
	test<test_bidirectional_approximately_sized_view>();
	test<test_random_access_approximately_sized_view>();
	test<test_contiguous_approximately_sized_view>();
}

}	// namespace concepts_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
