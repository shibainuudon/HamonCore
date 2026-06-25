/**
 *	@file	unit_test_ranges_elements_view_reserve_hint.cpp
 *
 *	@brief	reserve_hint() のテスト
 *
 *	constexpr auto reserve_hint() requires approximately_sized_range<V>;
 *	constexpr auto reserve_hint() const requires approximately_sized_range<const V>;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/concepts/approximately_sized_range.hpp>
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
namespace reserve_hint_test
{

template <typename D1, typename D2>
struct TestApproximatelySizedView : hamon::ranges::view_base
{
	using Tuple = hamon::tuple<int, long>;
	using Iterator = bidirectional_iterator_wrapper<Tuple>;
	using Sentinel = test_sentinel<Iterator>;
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;

	D1 reserve_hint() noexcept;
	D2 reserve_hint() const noexcept;
};

template <typename T, typename = void>
struct has_reserve_hint
	: public hamon::false_type {};

template <typename T>
struct has_reserve_hint<T, hamon::void_t<decltype(hamon::declval<T>().reserve_hint())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// approximately_sized_range<V> && approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<int, short>;
		static_assert( hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert( hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_reserve_hint<EV&>::value, "");
		static_assert( has_reserve_hint<EV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<EV&>().reserve_hint()), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<EV const&>().reserve_hint()), short>::value, "");
	}

	// !approximately_sized_range<V> && approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<void, unsigned int>;
		static_assert(!hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert( hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_reserve_hint<EV&>::value, "");
		static_assert( has_reserve_hint<EV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<EV&>().reserve_hint()), unsigned int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<EV const&>().reserve_hint()), unsigned int>::value, "");
	}

	// approximately_sized_range<V> && !approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<long, void>;
		static_assert( hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_reserve_hint<EV&>::value, "");
		static_assert(!has_reserve_hint<EV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<EV&>().reserve_hint()), long>::value, "");
	}

	// !approximately_sized_range<V> && !approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<void, void>;
		static_assert(!hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert(!has_reserve_hint<EV&>::value, "");
		static_assert(!has_reserve_hint<EV const&>::value, "");
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
		VERIFY(ev.reserve_hint() == 3);
	}
	{
		EV const ev {v};
		VERIFY(ev.reserve_hint() == 3);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewReserveHintTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace reserve_hint_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
