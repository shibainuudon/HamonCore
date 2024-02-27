/**
 *	@file	unit_test_ranges_adjacent_transform_view_iterator_typedefs.cpp
 *
 *	@brief	adjacent_transform_view::iterator のテスト
 *
 *	using iterator_category = see below;
 *	using iterator_concept  = typename inner-iterator<Const>::iterator_concept;
 *	using value_type =
 *	  remove_cvref_t<invoke_result_t<maybe-const<Const, F>&,
 *	                                 REPEAT(range_reference_t<Base>, N)...>>;
 *	using difference_type = range_difference_t<Base>;
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace iterator_typedefs_test
{

struct F1
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

struct F2
{
	template <typename T>
	constexpr T& operator()(T& x) const { return x; }
};

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	{
		using V = test_forward_view<float const>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::value_type, float>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = hamon::ranges::iterator_t<AV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	return true;
}

GTEST_TEST(RangesTest, AdjacentTransformViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
}

}	// namespace iterator_typedefs_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
