/**
 *	@file	unit_test_ranges_reverse_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr reverse_iterator<iterator_t<V>> end();
 *	constexpr auto end() const requires common_range<const V>;
 */

#include <hamon/ranges/adaptors/reverse_view.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace reverse_view_test
{
namespace end_test
{

template <typename Iterator, typename Sentinel, typename ConstIterator, typename ConstSentinel>
struct TestView : hamon::ranges::view_base
{
	Iterator      begin()       noexcept;
	ConstIterator begin() const noexcept;
	Sentinel      end()         noexcept;
	ConstSentinel end()   const noexcept;
};

template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		// common_range<V> && common_range<V const>
		using V = TestView<
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>
		>;

		static_assert(hamon::ranges::common_range_t<V>::value, "");
		static_assert(hamon::ranges::common_range_t<V const>::value, "");

		using RV = hamon::ranges::reverse_view<V>;
		static_assert(has_end<RV&>::value, "");
		static_assert(has_end<RV const&>::value, "");

		using ReverseIterator = hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>;
		static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), ReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), ReverseIterator>::value, "");
	}
	{
		// !common_range<V> && common_range<V const>
		using V = TestView<
			bidirectional_iterator_wrapper<int>,
			test_sentinel<bidirectional_iterator_wrapper<int>>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>
		>;

		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert( hamon::ranges::common_range_t<V const>::value, "");

		using RV = hamon::ranges::reverse_view<V>;
		static_assert(has_end<RV&>::value, "");
		static_assert(has_end<RV const&>::value, "");

		using ReverseIterator = hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>;
		static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), ReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), ReverseIterator>::value, "");
	}
	{
		// common_range<V> && !common_range<V const>
		using V = TestView<
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			test_sentinel<bidirectional_iterator_wrapper<int>>
		>;

		static_assert( hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V const>::value, "");

		using RV = hamon::ranges::reverse_view<V>;
		static_assert( has_end<RV&>::value, "");
		static_assert(!has_end<RV const&>::value, "");

		using ReverseIterator = hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>;
		static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), ReverseIterator>::value, "");
	}
	{
		// !common_range<V> && !common_range<V const>
		using V = TestView<
			bidirectional_iterator_wrapper<int>,
			test_sentinel<bidirectional_iterator_wrapper<int>>,
			bidirectional_iterator_wrapper<int>,
			test_sentinel<bidirectional_iterator_wrapper<int>>
		>;

		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V const>::value, "");

		using RV = hamon::ranges::reverse_view<V>;
		static_assert( has_end<RV&>::value, "");
		static_assert(!has_end<RV const&>::value, "");

		using ReverseIterator = hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>;
		static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), ReverseIterator>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ReverseViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace end_test
}	// namespace reverse_view_test
}	// namespace hamon_ranges_test
