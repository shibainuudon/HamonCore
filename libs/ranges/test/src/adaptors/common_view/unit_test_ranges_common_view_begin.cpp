/**
 *	@file	unit_test_ranges_common_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin();
 *	constexpr auto begin() const requires range<const V>;
 */

#include <hamon/ranges/adaptors/common_view.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace common_view_test
{
namespace begin_test
{

template <typename T, typename Iterator, typename Sentinel>
struct TestView : hamon::ranges::view_base
{
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;
};

template <typename T, typename Iterator, typename Sentinel>
struct TestView2 : hamon::ranges::view_base
{
	Iterator begin() noexcept;
	Sentinel end()   noexcept;
};

template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		// random_access_range<V> && sized_range<V>
		using V = test_random_access_view<int>;
		static_assert(hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(hamon::ranges::sized_range_t<V>::value, "");

		using I = hamon::ranges::iterator_t<V>;
		//using S = hamon::ranges::sentinel_t<V>;

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_begin<CV&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().begin()), I>::value, "");

		int a[] = { 1,2,3 };
		V v(a);
		CV cv{v};
		VERIFY(cv.begin() == v.begin());
	}
	{
		// !random_access_range<V> && sized_range<V>
		using V = test_forward_sized_view<int>;
		static_assert(!hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(hamon::ranges::sized_range_t<V>::value, "");

		using I = hamon::ranges::iterator_t<V>;
		using S = hamon::ranges::sentinel_t<V>;

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_begin<CV&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().begin()), hamon::common_iterator<I, S>>::value, "");

		int a[] = { 1,2,3 };
		V v(a);
		CV cv{v};
		VERIFY(*cv.begin() == 1);
	}
	{
		// random_access_range<V> && !sized_range<V>
		using V = TestView<int, random_access_iterator_wrapper<int>, hamon::unreachable_sentinel_t>;
		static_assert(hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");

		using I = hamon::ranges::iterator_t<V>;
		using S = hamon::ranges::sentinel_t<V>;

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_begin<CV&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().begin()), hamon::common_iterator<I, S>>::value, "");
	}
	{
		// !random_access_range<V> && !sized_range<V>
		using V = test_forward_view<int>;
		static_assert(!hamon::ranges::random_access_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");

		using I = hamon::ranges::iterator_t<V>;
		using S = hamon::ranges::sentinel_t<V>;

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_begin<CV&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().begin()), hamon::common_iterator<I, S>>::value, "");

		int a[] = { 1,2,3 };
		V v(a);
		CV cv{v};
		VERIFY(*cv.begin() == 1);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		// !range<V const>
		using V = TestView2<int, random_access_iterator_wrapper<int>, hamon::unreachable_sentinel_t>;
		static_assert( hamon::ranges::range_t<V>::value, "");
		static_assert(!hamon::ranges::range_t<V const>::value, "");

		using CV = hamon::ranges::common_view<V>;

		static_assert( has_begin<CV&>::value, "");
		static_assert(!has_begin<CV const&>::value, "");
	}
	{
		// random_access_range<V const> && sized_range<V const>
		using V = test_random_access_view<int>;
		static_assert(hamon::ranges::random_access_range_t<V const>::value, "");
		static_assert(hamon::ranges::sized_range_t<V const>::value, "");

		using I = hamon::ranges::iterator_t<V const>;
		//using S = hamon::ranges::sentinel_t<V const>;

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_begin<CV const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().begin()), I>::value, "");

		int a[] = { 1,2,3 };
		V v(a);
		CV const cv{v};
		VERIFY(cv.begin() == v.begin());
	}
	{
		// !random_access_range<V const> && sized_range<V const>
		using V = test_forward_sized_view<int>;
		static_assert(!hamon::ranges::random_access_range_t<V const>::value, "");
		static_assert(hamon::ranges::sized_range_t<V const>::value, "");

		using I = hamon::ranges::iterator_t<V const>;
		using S = hamon::ranges::sentinel_t<V const>;

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_begin<CV const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().begin()), hamon::common_iterator<I, S>>::value, "");

		int a[] = { 1,2,3 };
		V v(a);
		CV const cv{v};
		VERIFY(*cv.begin() == 1);
	}
	{
		// random_access_range<V const> && !sized_range<V const>
		using V = TestView<int, random_access_iterator_wrapper<int>, hamon::unreachable_sentinel_t>;
		static_assert(hamon::ranges::random_access_range_t<V const>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using I = hamon::ranges::iterator_t<V const>;
		using S = hamon::ranges::sentinel_t<V const>;

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_begin<CV const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().begin()), hamon::common_iterator<I, S>>::value, "");
	}
	{
		// !random_access_range<V const> && !sized_range<V const>
		using V = test_forward_view<int>;
		static_assert(!hamon::ranges::random_access_range_t<V const>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using I = hamon::ranges::iterator_t<V const>;
		using S = hamon::ranges::sentinel_t<V const>;

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_begin<CV const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().begin()), hamon::common_iterator<I, S>>::value, "");

		int a[] = { 1,2,3 };
		V v(a);
		CV const cv{v};
		VERIFY(*cv.begin() == 1);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CommonViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace begin_test
}	// namespace common_view_test
}	// namespace hamon_ranges_test
