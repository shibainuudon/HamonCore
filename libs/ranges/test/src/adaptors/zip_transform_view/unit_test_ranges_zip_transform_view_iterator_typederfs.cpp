/**
 *	@file	unit_test_ranges_zip_transform_view_iterator_typedefs.cpp
 *
 *	@brief	zip_transform_view::iterator のテスト
 *
 *	using iterator_category = see below;                        // not always present
 *  using iterator_concept  = typename ziperator<Const>::iterator_concept;
 *  using value_type =
 *    remove_cvref_t<invoke_result_t<maybe-const<Const, F>&,
 *                                   range_reference_t<maybe-const<Const, Views>>...>>;
 *  using difference_type = range_difference_t<Base>;
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace iterator_typedefs_test
{

struct F1
{
	int& operator()(int&) const;
};

struct F2
{
	int operator()(int&) const;
};

struct F3
{
	template <typename... Args>
	float operator()(Args...) const;
};

struct F4
{
	template <typename... Args>
	char operator()(Args...);

	template <typename... Args>
	long operator()(Args...) const;
};

template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using F = F1;
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using F = F1;
		using V = test_forward_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using F = F1;
		using V = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using F = F1;
		using V = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using F = F2;
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using F = F2;
		using V = test_forward_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using F = F2;
		using V = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using F = F2;
		using V = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using F = F3;
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using F = F3;
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using F = F3;
		using V1 = test_bidirectional_view<int>;
		using V2 = test_forward_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using F = F3;
		using V1 = test_random_access_view<int>;
		using V2 = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using F = F1;
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	{
		using F = F2;
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	{
		using F = F3;
		using V1 = test_random_access_view<int>;
		using V2 = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, float>::value, "");
	}
	{
		using F = F4;
		using V1 = test_random_access_view<int>;
		using V2 = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
		using CI = decltype(hamon::declval<ZV const&>().begin());
		static_assert(hamon::is_same<typename I::value_type, char>::value, "");
		static_assert(hamon::is_same<typename CI::value_type, long>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using F = F1;
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using F = F2;
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using F = F3;
		using V1 = test_random_access_view<int>;
		using V2 = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	return true;
}

GTEST_TEST(RangesTest, ZipTransformViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
}

}	// namespace iterator_typedefs_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
