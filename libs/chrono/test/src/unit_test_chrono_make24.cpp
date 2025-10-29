/**
 *	@file	unit_test_chrono_make24.cpp
 *
 *	@brief	make24 のテスト
 */

#include <hamon/chrono/make24.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, Make24Test)
{
	using namespace hamon::chrono;

	static_assert(hamon::is_same<hours, decltype(make24(hamon::declval<hours>(), hamon::declval<bool>()))>::value, "");
	static_assert(noexcept(make24(hamon::declval<hours>(), hamon::declval<bool>())), "");

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 1), false) == hours( 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 2), false) == hours( 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 3), false) == hours( 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 4), false) == hours( 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 5), false) == hours( 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 6), false) == hours( 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 7), false) == hours( 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 8), false) == hours( 8));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 9), false) == hours( 9));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours(10), false) == hours(10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours(11), false) == hours(11));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours(12), false) == hours( 0));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 1), true) == hours(13));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 2), true) == hours(14));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 3), true) == hours(15));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 4), true) == hours(16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 5), true) == hours(17));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 6), true) == hours(18));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 7), true) == hours(19));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 8), true) == hours(20));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours( 9), true) == hours(21));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours(10), true) == hours(22));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours(11), true) == hours(23));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make24(hours(12), true) == hours(12));
}

}	// namespace hamon_chrono_test
