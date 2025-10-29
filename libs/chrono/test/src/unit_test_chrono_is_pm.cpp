/**
 *	@file	unit_test_chrono_is_pm.cpp
 *
 *	@brief	is_pm のテスト
 */

#include <hamon/chrono/is_pm.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, IsPmTest)
{
	using namespace hamon::chrono;

	static_assert(hamon::is_same<bool, decltype(is_pm(hamon::declval<hours>()))>::value, "");
	static_assert(noexcept(is_pm(hamon::declval<hours>())), "");

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours( 6)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_pm(hours(11)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(12)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(13)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(14)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(18)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(19)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(21)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(22)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_pm(hours(23)));
}

}	// namespace hamon_chrono_test
