/**
 *	@file	unit_test_ranges_stride_view_iterator_typedefs.cpp
 *
 *	@brief	stride_view::iterator のテスト
 *
 *	using difference_type = range_difference_t<Base>;
 *	using value_type = range_value_t<Base>;
 *	using iterator_concept = see below;
 *	using iterator_category = see below;    // not always present
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace iterator_typedefs_test
{

template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

GTEST_TEST(RangesTest, StrideViewIteratorTypedefsTest)
{
	{
		using V  = test_input_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I  = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::value_type,       int>::value, "");
		static_assert(hamon::is_same<typename I::difference_type,  hamon::ptrdiff_t>::value, "");
	}
	{
		using V  = test_forward_view<int const>;
		using SV = hamon::ranges::stride_view<V>;
		using I  = decltype(hamon::declval<SV&>().begin());
		static_assert( has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::iterator_concept,  hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::value_type,        int>::value, "");
		static_assert(hamon::is_same<typename I::difference_type,   hamon::ptrdiff_t>::value, "");
	}
	{
		using V  = test_bidirectional_view<char>;
		using SV = hamon::ranges::stride_view<V>;
		using I  = decltype(hamon::declval<SV&>().begin());
		static_assert( has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::iterator_concept,  hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::value_type,        char>::value, "");
		static_assert(hamon::is_same<typename I::difference_type,   hamon::ptrdiff_t>::value, "");
	}
	{
		using V  = test_random_access_view<float>;
		using SV = hamon::ranges::stride_view<V>;
		using I  = decltype(hamon::declval<SV&>().begin());
		static_assert( has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::iterator_concept,  hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::value_type,        float>::value, "");
		static_assert(hamon::is_same<typename I::difference_type,   hamon::ptrdiff_t>::value, "");
	}
	{
		using V  = test_contiguous_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I  = decltype(hamon::declval<SV&>().begin());
		static_assert( has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::iterator_concept,  hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename I::value_type,        int>::value, "");
		static_assert(hamon::is_same<typename I::difference_type,   hamon::ptrdiff_t>::value, "");
	}
}

}	// namespace iterator_typedefs_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
