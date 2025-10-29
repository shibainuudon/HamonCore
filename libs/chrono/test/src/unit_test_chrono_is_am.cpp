/**
 *	@file	unit_test_chrono_is_am.cpp
 *
 *	@brief	is_am のテスト
 */

#include <hamon/chrono/is_am.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, IsAmTest)
{
	using namespace hamon::chrono;

	static_assert(hamon::is_same<bool, decltype(is_am(hamon::declval<hours>()))>::value, "");
	static_assert(noexcept(is_am(hamon::declval<hours>())), "");

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours( 6)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( is_am(hours(11)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(12)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(13)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(14)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(18)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(19)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(21)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(22)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!is_am(hours(23)));
}

}	// namespace hamon_chrono_test
