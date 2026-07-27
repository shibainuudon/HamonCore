/**
 *	@file	unit_test_ranges_as_input_view_iterator_typedefs.cpp
 *
 *	@brief	as_input_view::iterator のテスト
 *
 *	using difference_type = range_difference_t<V>;
 *	using value_type = range_value_t<V>;
 *	using iterator_concept = input_iterator_tag;
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace iterator_typedefs_test
{

template <template <typename> class ViewWrapper>
void test()
{
	using T = int;
	using V = ViewWrapper<T>;
	using AIV = hamon::ranges::as_input_view<V>;
	using I  = decltype(hamon::declval<AIV&>().begin());

	static_assert(!has_iterator_category<I>::value, "");
	static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::difference_type, hamon::ranges::range_difference_t<V>>::value, "");
	static_assert(hamon::is_same<typename I::value_type, hamon::ranges::range_value_t<V>>::value, "");
}

GTEST_TEST(RangesTest, AsInputViewIteratorTypedefsTest)
{
	test<test_input_view>();
	test<test_forward_view>();
	test<test_bidirectional_view>();
	test<test_random_access_view>();
	test<test_contiguous_view>();
}

}	// namespace iterator_typedefs_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
