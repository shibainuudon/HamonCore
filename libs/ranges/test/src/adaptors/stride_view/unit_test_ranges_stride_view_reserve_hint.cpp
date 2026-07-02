/**
 *	@file	unit_test_ranges_stride_view_reserve_hint.cpp
 *
 *	@brief	reserve_hint() のテスト
 *
 *	constexpr auto reserve_hint() requires approximately_sized_range<V>;
 *	constexpr auto reserve_hint() const requires approximately_sized_range<const V>;
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/concepts/approximately_sized_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstdint/uintptr_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace reserve_hint_test
{

template <typename D1, typename D2, typename Iterator>
struct TestApproximatelySizedView : hamon::ranges::view_base
{
	using Sentinel = test_sentinel<Iterator>;
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;

	D1 reserve_hint() noexcept;
	D2 reserve_hint() const noexcept;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Iterator>
HAMON_CXX14_CONSTEXPR bool test00()
{
	// approximately_sized_range<V> && approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<int, short, Iterator>;
		static_assert( hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert( hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using SV = hamon::ranges::stride_view<V>;
		static_assert( has_reserve_hint<SV&>::value, "");
		static_assert( has_reserve_hint<SV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<SV&>().reserve_hint()), hamon::uintptr_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<SV const&>().reserve_hint()), hamon::uintptr_t>::value, "");
	}

	// !approximately_sized_range<V> && approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<void, unsigned int, Iterator>;
		static_assert(!hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert( hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using SV = hamon::ranges::stride_view<V>;
		static_assert( has_reserve_hint<SV&>::value, "");
		static_assert( has_reserve_hint<SV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<SV&>().reserve_hint()), hamon::uintptr_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<SV const&>().reserve_hint()), hamon::uintptr_t>::value, "");
	}

	// approximately_sized_range<V> && !approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<long, void, Iterator>;
		static_assert( hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using SV = hamon::ranges::stride_view<V>;
		static_assert( has_reserve_hint<SV&>::value, "");
		static_assert(!has_reserve_hint<SV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<SV&>().reserve_hint()), hamon::uintptr_t>::value, "");
	}

	// !approximately_sized_range<V> && !approximately_sized_range<V const>
	{
		using V = TestApproximatelySizedView<void, void, Iterator>;
		static_assert(!hamon::ranges::approximately_sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::approximately_sized_range_t<V const>::value, "");

		using SV = hamon::ranges::stride_view<V>;
		static_assert(!has_reserve_hint<SV&>::value, "");
		static_assert(!has_reserve_hint<SV const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_random_access_view<int>;
	using SV = hamon::ranges::stride_view<V>;

	int a[] = {0,1,2,3,4};
	V v(a);

	{
		SV sv(v, 1);
		SV const& csv = sv;
		VERIFY(sv.reserve_hint()  == 5);
		VERIFY(csv.reserve_hint() == 5);
	}
	{
		SV sv(v, 2);
		SV const& csv = sv;
		VERIFY(sv.reserve_hint()  == 3);
		VERIFY(csv.reserve_hint() == 3);
	}
	{
		SV sv(v, 3);
		SV const& csv = sv;
		VERIFY(sv.reserve_hint()  == 2);
		VERIFY(csv.reserve_hint() == 2);
	}
	{
		SV sv(v, 4);
		SV const& csv = sv;
		VERIFY(sv.reserve_hint()  == 2);
		VERIFY(csv.reserve_hint() == 2);
	}
	{
		SV sv(v, 5);
		SV const& csv = sv;
		VERIFY(sv.reserve_hint()  == 1);
		VERIFY(csv.reserve_hint() == 1);
	}
	{
		SV sv(v, 6);
		SV const& csv = sv;
		VERIFY(sv.reserve_hint()  == 1);
		VERIFY(csv.reserve_hint() == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewReserveHintTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<input_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<forward_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace reserve_hint_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
