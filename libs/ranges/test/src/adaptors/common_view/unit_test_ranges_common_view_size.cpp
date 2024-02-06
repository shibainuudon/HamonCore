/**
 *	@file	unit_test_ranges_common_view_size.cpp
 *
 *	@brief	size() のテスト
 *
 *	constexpr auto size() requires sized_range<V>;
 *	constexpr auto size() const requires sized_range<const V>;
 */

#include <hamon/ranges/adaptors/common_view.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace common_view_test
{
namespace size_test
{

template <typename D1, typename D2>
struct TestSizedView : hamon::ranges::view_base
{
	using Iterator = forward_iterator_wrapper<int>;
	using Sentinel = test_sentinel<Iterator>;
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;

	D1 size() noexcept;
	D2 size() const noexcept;
};

template <typename T, typename = void>
struct has_size
	: public hamon::false_type {};

template <typename T>
struct has_size<T, hamon::void_t<decltype(hamon::declval<T>().size())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_random_access_view<int>;
		static_assert(hamon::ranges::sized_range_t<V>::value, "");
		static_assert(hamon::ranges::sized_range_t<V const>::value, "");

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_size<CV&>::value, "");
		static_assert(has_size<CV const&>::value, "");

		static_assert(hamon::is_same<
			decltype(hamon::declval<CV&>().size()),
			decltype(hamon::ranges::size(hamon::declval<V&>()))>::value, "");
		static_assert(hamon::is_same<
			decltype(hamon::declval<CV const&>().size()),
			decltype(hamon::ranges::size(hamon::declval<V const&>()))>::value, "");

		int a[] = { 1,2,3 };
		V v(a);
		{
			CV cv{v};
			VERIFY(cv.size() == 3);
		}
		{
			CV const cv{v};
			VERIFY(cv.size() == 3);
		}
	}
	{
		// sized_range<V> && sized_range<V const>
		using V = TestSizedView<int, short>;
		static_assert(hamon::ranges::sized_range_t<V>::value, "");
		static_assert(hamon::ranges::sized_range_t<V const>::value, "");

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_size<CV&>::value, "");
		static_assert(has_size<CV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().size()), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().size()), short>::value, "");
	}
	{
		// !sized_range<V> && sized_range<V const>
		using V = TestSizedView<void, unsigned int>;
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V const>::value, "");

		using CV = hamon::ranges::common_view<V>;
		static_assert(has_size<CV&>::value, "");
		static_assert(has_size<CV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().size()), unsigned int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().size()), unsigned int>::value, "");
	}
	{
		// sized_range<V> && !sized_range<V const>
		using V = TestSizedView<char, void>;
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using CV = hamon::ranges::common_view<V>;
		static_assert( has_size<CV&>::value, "");
		static_assert(!has_size<CV const&>::value, "");
	}
	{
		// !sized_range<V> && !sized_range<V const>
		using V = test_forward_view<int>;
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using CV = hamon::ranges::common_view<V>;
		static_assert(!has_size<CV&>::value, "");
		static_assert(!has_size<CV const&>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CommonViewSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace size_test
}	// namespace common_view_test
}	// namespace hamon_ranges_test
