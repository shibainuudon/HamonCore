/**
 *	@file	unit_test_ranges_slide_view_reserve_hint.cpp
 *
 *	@brief	reserve_hint() のテスト
 *
 *	constexpr auto reserve_hint() requires approximately_sized_range<V>;
 *	constexpr auto reserve_hint() const requires approximately_sized_range<const V>;
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/ranges/concepts/approximately_sized_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace slide_view_test
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
		using V = TestApproximatelySizedView<char, short>;
		static_assert( hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert( hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using SV = hamon::ranges::slide_view<V>;
		static_assert( has_reserve_hint<SV&>::value, "");
		static_assert( has_reserve_hint<SV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<SV&>().reserve_hint()), hamon::uintptr_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<SV const&>().reserve_hint()), hamon::uintptr_t>::value, "");
	}

	// !approximately_sized_range<V> && approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<void, int>;
		static_assert(!hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert( hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using SV = hamon::ranges::slide_view<V>;
		static_assert( has_reserve_hint<SV&>::value, "");
		static_assert( has_reserve_hint<SV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<SV&>().reserve_hint()), hamon::uintptr_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<SV const&>().reserve_hint()), hamon::uintptr_t>::value, "");
	}

	// approximately_sized_range<V> && !approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<char, void>;
		static_assert( hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using SV = hamon::ranges::slide_view<V>;
		static_assert( has_reserve_hint<SV&>::value, "");
		static_assert(!has_reserve_hint<SV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<SV&>().reserve_hint()), hamon::uintptr_t>::value, "");
	}

	// !approximately_sized_range<V> && !approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<void, void>;
		static_assert(!hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using SV = hamon::ranges::slide_view<V>;
		static_assert(!has_reserve_hint<SV&>::value, "");
		static_assert(!has_reserve_hint<SV const&>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_random_access_view<int>;
	using SV = hamon::ranges::slide_view<V>;

	int a[] = {1,2,3,4,5};
	V v(a);
	{
		SV sv(v, 2);
		VERIFY(sv.reserve_hint() == 4);
	}
	{
		SV sv(v, 3);
		VERIFY(sv.reserve_hint() == 3);
	}
	{
		SV sv(v, 4);
		VERIFY(sv.reserve_hint() == 2);
	}
	{
		SV sv(v, 5);
		VERIFY(sv.reserve_hint() == 1);
	}
	{
		SV sv(v, 6);
		VERIFY(sv.reserve_hint() == 0);
	}
	{
		SV sv(v, 7);
		VERIFY(sv.reserve_hint() == 0);
	}

	{
		SV const sv(v, 2);
		VERIFY(sv.reserve_hint() == 4);
	}
	{
		SV const sv(v, 3);
		VERIFY(sv.reserve_hint() == 3);
	}
	{
		SV const sv(v, 4);
		VERIFY(sv.reserve_hint() == 2);
	}
	{
		SV const sv(v, 5);
		VERIFY(sv.reserve_hint() == 1);
	}
	{
		SV const sv(v, 6);
		VERIFY(sv.reserve_hint() == 0);
	}
	{
		SV const sv(v, 7);
		VERIFY(sv.reserve_hint() == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewReserveHintTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace reserve_hint_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
