/**
 *	@file	unit_test_ranges_as_input_view_adaptor.cpp
 *
 *	@brief	views::as_input のテスト
 *
 *	views::as_input
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;

	int a[] = {1,2,3};
	V v(a);

	{
		auto clv = hamon::views::as_input(v);
		static_assert(hamon::is_same<decltype(clv), hamon::views::all_t<V>>::value, "");

		const int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(clv, expected));
	}
	{
		auto clv = v  | hamon::views::as_input;
		static_assert(hamon::is_same<decltype(clv), hamon::views::all_t<V>>::value, "");

		const int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(clv, expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_view<int>;

	int a[] = {1,2,3};
	V v(a);

	{
		auto clv = hamon::views::as_input(v);
		static_assert(hamon::is_same<decltype(clv), hamon::ranges::as_input_view<V>>::value, "");

		const int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(clv, expected));
	}
	{
		auto clv = v  | hamon::views::as_input;
		static_assert(hamon::is_same<decltype(clv), hamon::ranges::as_input_view<V>>::value, "");

		const int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(clv, expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V = test_input_common_view<int>;

	int a[] = {1,2,3};
	V v(a);

	{
		auto clv = hamon::views::as_input(v);
		static_assert(hamon::is_same<decltype(clv), hamon::ranges::as_input_view<V>>::value, "");

		const int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(clv, expected));
	}
	{
		auto clv = v  | hamon::views::as_input;
		static_assert(hamon::is_same<decltype(clv), hamon::ranges::as_input_view<V>>::value, "");

		const int expected[] = {1,2,3};
		VERIFY(hamon::ranges::equal(clv, expected));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace adaptor_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
