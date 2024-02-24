/**
 *	@file	unit_test_ranges_adjacent_view_iterator_typedefs.cpp
 *
 *	@brief	adjacent_view::iterator のテスト
 *
 *	using iterator_category = input_iterator_tag;
 *	using iterator_concept  = see below;
 *	using value_type = tuple<REPEAT(range_value_t<Base>, N)...>;
 *	using difference_type = range_difference_t<Base>;
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace iterator_typedefs_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using V = test_forward_view<int>;
		using EV = hamon::ranges::adjacent_view<V, 2>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using EV = hamon::ranges::adjacent_view<V, 2>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using EV = hamon::ranges::adjacent_view<V, 2>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using EV = hamon::ranges::adjacent_view<V, 2>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using V = test_forward_view<int>;
		using EV = hamon::ranges::adjacent_view<V, 2>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using EV = hamon::ranges::adjacent_view<V, 2>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using EV = hamon::ranges::adjacent_view<V, 2>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using EV = hamon::ranges::adjacent_view<V, 2>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using V = test_random_access_view<char>;
		using EV = hamon::ranges::adjacent_view<V, 1>;
		using I = hamon::ranges::iterator_t<EV>;
		using Tuple = hamon::tuple<char>;
		static_assert(hamon::is_same<typename I::value_type, Tuple>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using EV = hamon::ranges::adjacent_view<V, 2>;
		using I = hamon::ranges::iterator_t<EV>;
		using Tuple = hamon::tuple<int, int>;
		static_assert(hamon::is_same<typename I::value_type, Tuple>::value, "");
	}
	{
		using V = test_forward_view<float>;
		using EV = hamon::ranges::adjacent_view<V, 3>;
		using I = hamon::ranges::iterator_t<EV>;
		using Tuple = hamon::tuple<float, float, float>;
		static_assert(hamon::is_same<typename I::value_type, Tuple>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using V = test_forward_view<char>;
		using EV = hamon::ranges::adjacent_view<V, 1>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using EV = hamon::ranges::adjacent_view<V, 2>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_random_access_view<float>;
		using EV = hamon::ranges::adjacent_view<V, 3>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
}

}	// namespace iterator_typedefs_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
