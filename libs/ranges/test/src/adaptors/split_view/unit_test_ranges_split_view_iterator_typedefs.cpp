/**
 *	@file	unit_test_ranges_split_view_iterator_typedefs.cpp
 *
 *	@brief	split_view::iterator  のテスト
 *
 *	using iterator_concept = forward_iterator_tag;
 *	using iterator_category = input_iterator_tag;
 *	using value_type = subrange<iterator_t<V>>;
 *	using difference_type = range_difference_t<V>;
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace iterator_typedefs_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::value_type, hamon::ranges::subrange<hamon::ranges::iterator_t<V>>>::value, "");
		static_assert(hamon::is_same<typename I::difference_type, hamon::ranges::range_difference_t<V>>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::value_type, hamon::ranges::subrange<hamon::ranges::iterator_t<V>>>::value, "");
		static_assert(hamon::is_same<typename I::difference_type, hamon::ranges::range_difference_t<V>>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using P = test_random_access_view<int>;
		using RV = hamon::ranges::split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::value_type, hamon::ranges::subrange<hamon::ranges::iterator_t<V>>>::value, "");
		static_assert(hamon::is_same<typename I::difference_type, hamon::ranges::range_difference_t<V>>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_typedefs_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
