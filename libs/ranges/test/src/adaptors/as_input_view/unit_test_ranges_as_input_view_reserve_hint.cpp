/**
 *	@file	unit_test_ranges_as_input_view_reserve_hint.cpp
 *
 *	@brief	reserve_hint() のテスト
 *
 *	constexpr auto reserve_hint() requires approximately_sized_range<V>;
 *	constexpr auto reserve_hint() const requires approximately_sized_range<const V>;
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/ranges/concepts/approximately_sized_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace reserve_hint_test
{

template <typename D1, typename D2>
struct TestApproximatelySizedView : hamon::ranges::view_base
{
	using Iterator = bidirectional_iterator_wrapper<int>;
	using Sentinel = test_sentinel<Iterator>;
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;

	D1 reserve_hint() noexcept;
	D2 reserve_hint() const noexcept;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	//  approximately_sized_range<V> && approximately_sized_range<const V>
	{
		using V = TestApproximatelySizedView<int, short>;
		static_assert( hamon::ranges::approximately_sized_range<V>, "");
		static_assert( hamon::ranges::approximately_sized_range<V const>, "");

		using AIV = hamon::ranges::as_input_view<V>;
		static_assert( has_reserve_hint<AIV&>::value, "");
		static_assert( has_reserve_hint<AIV const&>::value, "");

		using D  = decltype(hamon::declval<AIV&>().reserve_hint());
		static_assert(hamon::is_same<D, int>::value, "");

		using CD = decltype(hamon::declval<AIV const&>().reserve_hint());
		static_assert(hamon::is_same<CD, short>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	//  approximately_sized_range<V> && !approximately_sized_range<const V>
	{
		using V = TestApproximatelySizedView<char, void>;
		static_assert( hamon::ranges::approximately_sized_range<V>, "");
		static_assert(!hamon::ranges::approximately_sized_range<V const>, "");

		using AIV = hamon::ranges::as_input_view<V>;
		static_assert( has_reserve_hint<AIV&>::value, "");
		static_assert(!has_reserve_hint<AIV const&>::value, "");

		using D  = decltype(hamon::declval<AIV&>().reserve_hint());
		static_assert(hamon::is_same<D, char>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	//  !approximately_sized_range<V> && approximately_sized_range<const V>
	{
		using V = TestApproximatelySizedView<void, long>;
		static_assert(!hamon::ranges::approximately_sized_range<V>, "");
		static_assert( hamon::ranges::approximately_sized_range<V const>, "");

		using AIV = hamon::ranges::as_input_view<V>;
		static_assert( has_reserve_hint<AIV&>::value, "");
		static_assert( has_reserve_hint<AIV const&>::value, "");

		using D  = decltype(hamon::declval<AIV&>().reserve_hint());
		static_assert(hamon::is_same<D, long>::value, "");

		using CD = decltype(hamon::declval<AIV const&>().reserve_hint());
		static_assert(hamon::is_same<CD, long>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	//  !approximately_sized_range<V> && !approximately_sized_range<const V>
	{
		using V = TestApproximatelySizedView<void, void>;
		static_assert(!hamon::ranges::approximately_sized_range<V>, "");
		static_assert(!hamon::ranges::approximately_sized_range<V const>, "");

		using AIV = hamon::ranges::as_input_view<V>;
		static_assert(!has_reserve_hint<AIV&>::value, "");
		static_assert(!has_reserve_hint<AIV const&>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	using V = test_random_access_view<int>;
	using AIV = hamon::ranges::as_input_view<V>;

	{
		int a[] = {1, 2};
		V v(a);
		{
			AIV aiv {v};
			VERIFY(aiv.reserve_hint() == 2);
		}
		{
			AIV const aiv {v};
			VERIFY(aiv.reserve_hint() == 2);
		}
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	using V = test_input_approximately_sized_view<int>;
	using AIV = hamon::ranges::as_input_view<V>;

	{
		int a[] = {3, 1, 4, 1, 5};
		V v(a);
		{
			AIV aiv {v};
			VERIFY(aiv.reserve_hint() == 5);
		}
		{
			AIV const aiv {v};
			VERIFY(aiv.reserve_hint() == 5);
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewReserveHintTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace reserve_hint_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
