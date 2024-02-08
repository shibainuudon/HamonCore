/**
 *	@file	unit_test_ranges_elements_view_size.cpp
 *
 *	@brief	size() のテスト
 *
 *	constexpr auto size() requires sized_range<V>;
 *	constexpr auto size() const requires sized_range<const V>;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace size_test
{

template <typename D1, typename D2>
struct TestSizedView : hamon::ranges::view_base
{
	using Tuple = hamon::tuple<int, long>;
	using Iterator = bidirectional_iterator_wrapper<Tuple>;
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
	// sized_range<V> && sized_range<V const>
	{
		using V = TestSizedView<int, short>;
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_size<EV&>::value, "");
		static_assert( has_size<EV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<EV&>().size()), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<EV const&>().size()), short>::value, "");
	}

	// !sized_range<V> && sized_range<V const>
	{
		using V = TestSizedView<void, unsigned int>;
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_size<EV&>::value, "");
		static_assert( has_size<EV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<EV&>().size()), unsigned int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<EV const&>().size()), unsigned int>::value, "");
	}

	// sized_range<V> && !sized_range<V const>
	{
		using V = TestSizedView<long, void>;
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_size<EV&>::value, "");
		static_assert(!has_size<EV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<EV&>().size()), long>::value, "");
	}

	// !sized_range<V> && !sized_range<V const>
	{
		using V = TestSizedView<void, void>;
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert(!has_size<EV&>::value, "");
		static_assert(!has_size<EV const&>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Tuple = hamon::tuple<int, long>;
	using V = test_random_access_view<Tuple>;
	using EV = hamon::ranges::elements_view<V, 0>;

	Tuple a[] =
	{
		Tuple{1,2},
		Tuple{3,4},
		Tuple{5,6},
	};
	V v(a);
	{
		EV ev {v};
		VERIFY(ev.size() == 3);
	}
	{
		EV const ev {v};
		VERIFY(ev.size() == 3);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace size_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
