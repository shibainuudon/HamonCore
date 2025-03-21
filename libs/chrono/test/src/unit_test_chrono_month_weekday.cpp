/**
 *	@file	unit_test_chrono_month_weekday.cpp
 *
 *	@brief	month_weekday のテスト
 */

#include <hamon/chrono/month_weekday.hpp>
#include <hamon/chrono/month.hpp>
#include <hamon/chrono/weekday.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace month_weekday_test
{

GTEST_TEST(ChronoTest, MonthWeekDayTest)
{
	namespace chrono = hamon::chrono;

	// month_weekday
	{
		HAMON_CXX11_CONSTEXPR chrono::month_weekday mwd{chrono::month{3}, chrono::weekday_indexed{chrono::Sunday, 1}};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::March, mwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[1], mwd.weekday_indexed());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(mwd.ok());
	}

	// compare
	{
		HAMON_CXX11_CONSTEXPR chrono::month_weekday mwd1{chrono::month{4}, chrono::Sunday[1]};
		HAMON_CXX11_CONSTEXPR chrono::month_weekday mwd2{chrono::month{4}, chrono::Sunday[1]};
		HAMON_CXX11_CONSTEXPR chrono::month_weekday mwd3{chrono::month{4}, chrono::Sunday[2]};
		HAMON_CXX11_CONSTEXPR chrono::month_weekday mwd4{chrono::month{3}, chrono::Sunday[1]};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (mwd1 == mwd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (mwd1 == mwd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(mwd1 == mwd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(mwd1 == mwd4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(mwd1 != mwd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(mwd1 != mwd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (mwd1 != mwd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (mwd1 != mwd4);
	}

	// month_weekday_last
	{
		HAMON_CXX11_CONSTEXPR chrono::month_weekday_last mwd{chrono::month{3}, chrono::weekday_last{chrono::Sunday}};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::March, mwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[chrono::last], mwd.weekday_last());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(mwd.ok());
	}

	// compare
	{
		HAMON_CXX11_CONSTEXPR chrono::month_weekday_last mwd1{chrono::month{3}, chrono::Sunday[chrono::last]};
		HAMON_CXX11_CONSTEXPR chrono::month_weekday_last mwd2{chrono::month{3}, chrono::Sunday[chrono::last]};
		HAMON_CXX11_CONSTEXPR chrono::month_weekday_last mwd3{chrono::month{3}, chrono::Monday[chrono::last]};
		HAMON_CXX11_CONSTEXPR chrono::month_weekday_last mwd4{chrono::month{4}, chrono::Sunday[chrono::last]};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (mwd1 == mwd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (mwd1 == mwd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(mwd1 == mwd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(mwd1 == mwd4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(mwd1 != mwd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(mwd1 != mwd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (mwd1 != mwd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (mwd1 != mwd4);
	}

	// Conventional syntax operators

	// month / weekday_indexed
	{
		HAMON_CXX11_CONSTEXPR auto mwd = chrono::March/chrono::Sunday[0];
		static_assert(hamon::is_same<decltype(mwd), chrono::month_weekday const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, mwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[0], mwd.weekday_indexed());
	}
	// int / weekday_indexed
	{
		HAMON_CXX11_CONSTEXPR auto mwd = 4/chrono::Sunday[0];
		static_assert(hamon::is_same<decltype(mwd), chrono::month_weekday const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::April, mwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[0], mwd.weekday_indexed());
	}
	// weekday_indexed / month
	{
		HAMON_CXX11_CONSTEXPR auto mwd = chrono::Monday[1]/chrono::May;
		static_assert(hamon::is_same<decltype(mwd), chrono::month_weekday const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{5}, mwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Monday[1], mwd.weekday_indexed());
	}
	// weekday_indexed / int
	{
		HAMON_CXX11_CONSTEXPR auto mwd = chrono::Tuesday[2]/6;
		static_assert(hamon::is_same<decltype(mwd), chrono::month_weekday const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::June, mwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Tuesday[2], mwd.weekday_indexed());
	}
	// month / weekday_last
	{
		HAMON_CXX11_CONSTEXPR auto mwd = chrono::month{3}/chrono::Sunday[chrono::last];
		static_assert(hamon::is_same<decltype(mwd), chrono::month_weekday_last const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::March, mwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[chrono::last], mwd.weekday_last());
	}
	// int / weekday_last
	{
		HAMON_CXX11_CONSTEXPR auto mwd = 1/chrono::Friday[chrono::last];
		static_assert(hamon::is_same<decltype(mwd), chrono::month_weekday_last const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::January, mwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Friday[chrono::last], mwd.weekday_last());
	}
	// weekday_last / month
	{
		HAMON_CXX11_CONSTEXPR auto mwd = chrono::Wednesday[chrono::last]/chrono::February;
		static_assert(hamon::is_same<decltype(mwd), chrono::month_weekday_last const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{2}, mwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Wednesday[chrono::last], mwd.weekday_last());
	}
	// weekday_last / int
	{
		HAMON_CXX11_CONSTEXPR auto mwd = chrono::Wednesday[chrono::last]/12;
		static_assert(hamon::is_same<decltype(mwd), chrono::month_weekday_last const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::December, mwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Wednesday[chrono::last], mwd.weekday_last());
	}
}

}	// namespace month_weekday_test

}	// namespace hamon_chrono_test
