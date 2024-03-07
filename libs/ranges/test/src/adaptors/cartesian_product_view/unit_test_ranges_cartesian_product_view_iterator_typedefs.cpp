/**
 *	@file	unit_test_ranges_cartesian_product_view_iterator_typedefs.cpp
 *
 *	@brief	cartesian_product_view::iterator のテスト
 *
 *	using iterator_category = input_iterator_tag;
 *	using iterator_concept  = see below;
 *	using value_type = tuple<range_value_t<maybe-const<Const, First>>,
 *	  range_value_t<maybe-const<Const, Vs>>...>;
 *	using reference = tuple<range_reference_t<maybe-const<Const, First>>,
 *	  range_reference_t<maybe-const<Const, Vs>>...>;
 *	using difference_type = see below;
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/iterator/detail/is_signed_integer_like.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
{
namespace iterator_typedefs_test
{

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using V3 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2, V3>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V1 = test_input_view<int>;
		using V2 = test_forward_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using V1 = test_forward_view<int>;
		using V2 = test_forward_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_bidirectional_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_bidirectional_common_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, hamon::tuple<int>>::value, "");
	}
	{
		using V1 = test_input_view<char>;
		using V2 = test_forward_view<long const>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, hamon::tuple<char, long>>::value, "");
	}
	{
		using V1 = test_input_view<float const>;
		using V2 = test_forward_view<long>;
		using V3 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2, V3>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, hamon::tuple<float, long, int>>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_reference()
{
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::reference, hamon::tuple<int&>>::value, "");
	}
	{
		using V1 = test_input_view<char>;
		using V2 = test_forward_view<long const>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::reference, hamon::tuple<char&, long const&>>::value, "");
	}
	{
		using V1 = test_input_view<float const>;
		using V2 = test_forward_view<long>;
		using V3 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2, V3>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::reference, hamon::tuple<float const&, long&, int&>>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		using D = typename I::difference_type;
		static_assert(hamon::detail::is_signed_integer_like_t<D>::value, "");
	}
	{
		using V1 = test_input_view<char>;
		using V2 = test_forward_view<long const>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		using D = typename I::difference_type;
		static_assert(hamon::detail::is_signed_integer_like_t<D>::value, "");
	}
	{
		using V1 = test_random_access_view<float const>;
		using V2 = test_random_access_view<long>;
		using V3 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2, V3>;
		using I = decltype(hamon::declval<CV&>().begin());
		using D = typename I::difference_type;
		static_assert(hamon::detail::is_signed_integer_like_t<D>::value, "");
	}
	return true;
}

GTEST_TEST(RangesTest, CartesianProductViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_reference());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
}

}	// namespace iterator_typedefs_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
