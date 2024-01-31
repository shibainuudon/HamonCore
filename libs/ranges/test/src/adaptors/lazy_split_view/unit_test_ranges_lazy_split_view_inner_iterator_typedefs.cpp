/**
 *	@file	unit_test_ranges_lazy_split_view_inner_iterator_typedefs.cpp
 *
 *	@brief	lazy_split_view::inner_iterator のテスト
 *
 *	using iterator_concept  = typename outer-iterator<Const>::iterator_concept;
 *	using iterator_category = see below;
 *	using value_type        = range_value_t<Base>;
 *	using difference_type   = range_difference_t<Base>;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace inner_iterator_typedefs_test
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
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using P = test_bidirectional_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
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
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using P = test_random_access_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool value_type_test()
{
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	{
		using V = test_forward_view<char>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::value_type, char>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<char>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool difference_type_test()
{
	{
		using V = test_input_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using OuterIter = hamon::ranges::iterator_t<RV>;
		using InnerRng = decltype(*hamon::declval<OuterIter&>());
		using I = decltype(hamon::declval<InnerRng&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewInnerIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(iterator_concept_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(iterator_category_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(value_type_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(difference_type_test());
}

}	// namespace inner_iterator_typedefs_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
