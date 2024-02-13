/**
 *	@file	unit_test_ranges_enumerate_view_adaptor.cpp
 *
 *	@brief	views::enumerate のテスト
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {3,1,4,1};
	using EV = hamon::ranges::enumerate_view<hamon::views::all_t<int(&)[4]>>;

	hamon::tuple<hamon::ptrdiff_t, int> expected[] =
	{
		{0, 3},
		{1, 1},
		{2, 4},
		{3, 1},
	};

	// views::enumerate(v)
	{
		auto ev = hamon::views::enumerate(a);
		static_assert(hamon::is_same<decltype(ev), EV>::value, "");
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	
	// v | views::enumerate
	{
		auto ev = a | hamon::views::enumerate;
		static_assert(hamon::is_same<decltype(ev), EV>::value, "");
		VERIFY(hamon::ranges::equal(ev, expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;

	int a[] = {10,20,30};
	V v(a);

	hamon::tuple<hamon::ptrdiff_t, int> expected[] =
	{
		{0, 10},
		{1, 20},
		{2, 30},
	};

	// views::enumerate(v)
	{
		auto ev = hamon::views::enumerate(v);
		static_assert(hamon::is_same<decltype(ev), EV>::value, "");
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	
	// v | views::enumerate
	{
		auto ev = v | hamon::views::enumerate;
		static_assert(hamon::is_same<decltype(ev), EV>::value, "");
		VERIFY(hamon::ranges::equal(ev, expected));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace adaptor_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
