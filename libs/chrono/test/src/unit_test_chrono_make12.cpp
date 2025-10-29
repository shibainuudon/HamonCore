/**
 *	@file	unit_test_chrono_make12.cpp
 *
 *	@brief	make12 のテスト
 */

#include <hamon/chrono/make12.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, Make12Test)
{
	using namespace hamon::chrono;

	static_assert(hamon::is_same<hours, decltype(make12(hamon::declval<hours>()))>::value, "");
	static_assert(noexcept(make12(hamon::declval<hours>())), "");

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours( 0)) == hours(12));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours( 1)) == hours( 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours( 2)) == hours( 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours( 3)) == hours( 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours( 4)) == hours( 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours( 5)) == hours( 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours( 6)) == hours( 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours( 7)) == hours( 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours( 8)) == hours( 8));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours( 9)) == hours( 9));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(10)) == hours(10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(11)) == hours(11));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(12)) == hours(12));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(13)) == hours( 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(14)) == hours( 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(15)) == hours( 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(16)) == hours( 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(17)) == hours( 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(18)) == hours( 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(19)) == hours( 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(20)) == hours( 8));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(21)) == hours( 9));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(22)) == hours(10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(make12(hours(23)) == hours(11));
}

}	// namespace hamon_chrono_test
