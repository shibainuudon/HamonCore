/**
 *	@file	unit_test_ranges_slide_view_adaptor.cpp
 *
 *	@brief	views::slide のテスト
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace slide_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
#if defined(HAMON_HAS_CXX17_RANGE_BASED_FOR)
	using V = test_forward_view<int>;
	using SV = hamon::ranges::slide_view<V>;

	int a[] = {1,2,3,4,5};
	test_forward_view<int> v(a);

	// views::slide(v, n)
	{
		auto sv = hamon::views::slide(v, 2);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");
		int expected[][2] =
		{
			{1,2},
			{2,3},
			{3,4},
			{4,5},
		};
		int i = 0;
		for (auto t : sv)
		{
			VERIFY(hamon::ranges::equal(t, expected[i]));
			++i;
		}
	}

	// v | views::slide(n)
	{
		auto sv = v | hamon::views::slide(3);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");
		int expected[][3] =
		{
			{1,2,3},
			{2,3,4},
			{3,4,5},
		};
		int i = 0;
		for (auto t : sv)
		{
			VERIFY(hamon::ranges::equal(t, expected[i]));
			++i;
		}
	}

	// views::slide(n)(v)
	{
		auto sv = hamon::views::slide(4)(v);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");
		int expected[][4] =
		{
			{1,2,3,4},
			{2,3,4,5},
		};
		int i = 0;
		for (auto t : sv)
		{
			VERIFY(hamon::ranges::equal(t, expected[i]));
			++i;
		}
	}
#endif

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using SV = hamon::ranges::slide_view<hamon::views::all_t<int(&)[5]>>;

	int a[] = {1,2,3,4,5};

	// views::slide(v, n)
	{
		auto sv = hamon::views::slide(a, 2);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");
		int expected[][2] =
		{
			{1,2},
			{2,3},
			{3,4},
			{4,5},
		};
		int i = 0;
		for (auto t : sv)
		{
			VERIFY(hamon::ranges::equal(t, expected[i]));
			++i;
		}
	}

	// v | views::slide(n)
	{
		auto sv = a | hamon::views::slide(3);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");
		int expected[][3] =
		{
			{1,2,3},
			{2,3,4},
			{3,4,5},
		};
		int i = 0;
		for (auto t : sv)
		{
			VERIFY(hamon::ranges::equal(t, expected[i]));
			++i;
		}
	}

	// views::slide(n)(v)
	{
		auto sv = hamon::views::slide(4)(a);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");
		int expected[][4] =
		{
			{1,2,3,4},
			{2,3,4,5},
		};
		int i = 0;
		for (auto t : sv)
		{
			VERIFY(hamon::ranges::equal(t, expected[i]));
			++i;
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace adaptor_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
