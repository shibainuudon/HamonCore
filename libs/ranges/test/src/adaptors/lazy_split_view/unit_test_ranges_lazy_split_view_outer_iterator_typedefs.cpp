/**
 *	@file	unit_test_ranges_lazy_split_view_outer_iterator_typedefs.cpp
 *
 *	@brief	lazy_split_view::outer_iterator のテスト
 *
 *	using iterator_concept = conditional_t<forward_range<Base>, forward_iterator_tag, input_iterator_tag>;
 *	using iterator_category = input_iterator_tag;
 *	using difference_type   = range_difference_t<Base>;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace outer_iterator_typedefs_test
{

template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool iterator_concept_test()
{
	{
		using V = test_input_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using P = test_bidirectional_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool iterator_category_test()
{
	{
		using V = test_input_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using P = test_random_access_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool difference_type_test()
{
	{
		using V = test_input_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewOuterIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(iterator_concept_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(iterator_category_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(difference_type_test());
}

}	// namespace outer_iterator_typedefs_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
