/**
 *	@file	unit_test_utility_to_underlying.cpp
 *
 *	@brief	to_underlying のテスト
 */

#include <hamon/utility/to_underlying.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace to_underlying_test
{

enum class E1 : char { e = 1 };
enum struct E2 : long { e = 2 };
enum E3 : unsigned { e = 3 };

static_assert(hamon::is_same<char, decltype(hamon::to_underlying(E1::e))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::to_underlying(E2::e))>::value, "");
static_assert(hamon::is_same<unsigned, decltype(hamon::to_underlying(e))>::value, "");

GTEST_TEST(UtilityTest, ToUnderlyingTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::to_underlying(E1::e));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::to_underlying(E2::e));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, hamon::to_underlying(e));
}

}	// namespace to_underlying_test

}	// namespace hamon_utility_test
