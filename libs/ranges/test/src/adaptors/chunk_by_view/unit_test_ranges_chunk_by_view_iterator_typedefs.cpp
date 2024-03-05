/**
 *	@file	unit_test_ranges_chunk_by_view_iterator_typedefs.cpp
 *
 *	@brief	chunk_by_view::iterator のテスト
 *
 *	using value_type = subrange<iterator_t<V>>;
 *	using difference_type  = range_difference_t<V>;
 *	using iterator_category = input_iterator_tag;
 *	using iterator_concept = see below;
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace iterator_typedefs_test
{

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using V = test_forward_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using V = test_forward_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using V = test_forward_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, hamon::ranges::subrange<hamon::ranges::iterator_t<V>>>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, hamon::ranges::subrange<hamon::ranges::iterator_t<V>>>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, hamon::ranges::subrange<hamon::ranges::iterator_t<V>>>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, hamon::ranges::subrange<hamon::ranges::iterator_t<V>>>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using V = test_forward_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ranges::range_difference_t<V>>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ranges::range_difference_t<V>>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ranges::range_difference_t<V>>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ranges::range_difference_t<V>>::value, "");
	}
	return true;
}

GTEST_TEST(RangesTest, ChunkByViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
}

}	// namespace iterator_typedefs_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
