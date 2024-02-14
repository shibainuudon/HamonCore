/**
 *	@file	unit_test_ranges_zip_view_iterator_typedefs.cpp
 *
 *	@brief	zip_view::iterator のテスト
 *
 *	using iterator_category = input_iterator_tag;                           // not always present
 *	using iterator_concept  = see below;
 *	using value_type = tuple<range_value_t<maybe-const<Const, Views>>...>;
 *	using difference_type = common_type_t<range_difference_t<maybe-const<Const, Views>>...>;
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace iterator_typedefs_test
{

template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert( has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert( has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V1 = test_forward_view<int>;
		using V2 = test_forward_view<int>;
		using V3 = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert( has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V1 = test_contiguous_view<int>;
		using V2 = test_bidirectional_view<int>;
		using V3 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert( has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V1 = test_input_view<int>;
		using V2 = test_forward_view<int>;
		using V3 = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using V1 = test_forward_view<int>;
		using V2 = test_input_view<int>;
		using V3 = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using V1 = test_forward_view<int>;
		using V2 = test_forward_view<int>;
		using V3 = test_input_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(!has_iterator_category<I>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using V3 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<int>;
		using V3 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_bidirectional_view<int>;
		using V3 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using V3 = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_bidirectional_view<int>;
		using V3 = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V1 = test_forward_view<int>;
		using V2 = test_bidirectional_view<int>;
		using V3 = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_forward_view<int>;
		using V3 = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_bidirectional_view<int>;
		using V3 = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V1 = test_forward_view<int>;
		using V2 = test_forward_view<int>;
		using V3 = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V1 = test_input_view<int>;
		using V2 = test_forward_view<int>;
		using V3 = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using V1 = test_forward_view<int>;
		using V2 = test_input_view<int>;
		using V3 = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using V1 = test_forward_view<int>;
		using V2 = test_forward_view<int>;
		using V3 = test_input_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using V1 = test_input_view<int>;
		using ZV = hamon::ranges::zip_view<V1>;
		using I = hamon::ranges::iterator_t<ZV>;
		using Tuple = hamon::tuple<int>;
		static_assert(hamon::is_same<typename I::value_type, Tuple>::value, "");
	}
	{
		using V1 = test_input_view<float>;
		using ZV = hamon::ranges::zip_view<V1>;
		using I = hamon::ranges::iterator_t<ZV>;
		using Tuple = hamon::tuple<float>;
		static_assert(hamon::is_same<typename I::value_type, Tuple>::value, "");
	}
	{
		using V1 = test_input_view<int>;
		using V2 = test_input_view<int>;
		using V3 = test_input_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		using Tuple = hamon::tuple<int, int, int>;
		static_assert(hamon::is_same<typename I::value_type, Tuple>::value, "");
	}
	{
		using V1 = test_input_view<char>;
		using V2 = test_input_view<long>;
		using V3 = test_input_view<float>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		using Tuple = hamon::tuple<char, long, float>;
		static_assert(hamon::is_same<typename I::value_type, Tuple>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using V1 = test_input_view<int>;
		using ZV = hamon::ranges::zip_view<V1>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using V1 = test_input_view<char>;
		using V2 = test_input_view<long>;
		using V3 = test_input_view<float>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = hamon::ranges::iterator_t<ZV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	return true;
}

GTEST_TEST(RangesTest, ZipViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
}

}	// namespace iterator_typedefs_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
