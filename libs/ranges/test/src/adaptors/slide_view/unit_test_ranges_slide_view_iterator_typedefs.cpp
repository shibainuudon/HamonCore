/**
 *	@file	unit_test_ranges_slide_view_iterator_typedefs.cpp
 *
 *	@brief	slide_view::iterator のテスト
 *
 *	using iterator_category = input_iterator_tag;
 *	using iterator_concept = see below;
 *	using value_type = decltype(views::counted(current_, n_));
 *	using difference_type = range_difference_t<Base>;
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/ranges/adaptors/counted_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace slide_view_test
{
namespace iterator_typedefs_test
{

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::value_type,
			decltype(hamon::views::counted(
				hamon::declval<hamon::ranges::iterator_t<V>>(),
				hamon::declval<hamon::ranges::range_difference_t<V>>()))
		>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::value_type,
			decltype(hamon::views::counted(
				hamon::declval<hamon::ranges::iterator_t<V>>(),
				hamon::declval<hamon::ranges::range_difference_t<V>>()))
		>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::value_type,
			decltype(hamon::views::counted(
				hamon::declval<hamon::ranges::iterator_t<V>>(),
				hamon::declval<hamon::ranges::range_difference_t<V>>()))
		>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::value_type,
			decltype(hamon::views::counted(
				hamon::declval<hamon::ranges::iterator_t<V>>(),
				hamon::declval<hamon::ranges::range_difference_t<V>>()))
		>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	return true;
}

GTEST_TEST(RangesTest, SlideViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
}

}	// namespace iterator_typedefs_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
