/**
 *	@file	unit_test_ranges_stride_view_adaptor.cpp
 *
 *	@brief	views::stride のテスト
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using SV = hamon::ranges::stride_view<V>;

	int a[] = {1,2,3,4,5};
	V v(a);

	// views::stride(v, stride)
	{
		auto sv = hamon::views::stride(v, 1);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");

		int expected[] = {1,2,3,4,5};
		VERIFY(hamon::ranges::equal(sv, expected));
	}

	// v | views::stride(stride)
	{
		auto sv = v | hamon::views::stride(2);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");

		int expected[] = {1,3,5};
		VERIFY(hamon::ranges::equal(sv, expected));
	}

	// views::stride(stride)(v)
	{
		auto sv = hamon::views::stride(3)(v);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");

		int expected[] = {1,4};
		VERIFY(hamon::ranges::equal(sv, expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using SV = hamon::ranges::stride_view<hamon::views::all_t<int(&)[10]>>;

	int a[] = {0,1,2,3,4,5,6,7,8,9};

	// views::stride(v, stride)
	{
		auto sv = hamon::views::stride(a, 2);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");

		int expected[] = {0,2,4,6,8};
		VERIFY(hamon::ranges::equal(sv, expected));
	}

	// v | views::stride(stride)
	{
		auto sv = a | hamon::views::stride(3);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");

		int expected[] = {0,3,6,9};
		VERIFY(hamon::ranges::equal(sv, expected));
	}

	// views::stride(stride)(v)
	{
		auto sv = hamon::views::stride(4)(a);
		static_assert(hamon::is_same<decltype(sv), SV>::value, "");

		int expected[] = {0,4,8};
		VERIFY(hamon::ranges::equal(sv, expected));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace adaptor_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
