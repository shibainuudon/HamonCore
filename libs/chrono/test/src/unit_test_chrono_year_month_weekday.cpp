/**
 *	@file	unit_test_chrono_year_month_weekday.cpp
 *
 *	@brief	year_month_weekday のテスト
 */

#include <hamon/chrono/year_month_weekday.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/compare.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace year_month_weekday_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test1()
{
	namespace chrono = hamon::chrono;
	using namespace hamon::chrono_literals;

	chrono::year_month_weekday date = 2019_y/2/chrono::Sunday[2];
	VERIFY(date.year() == chrono::year{2019});
	VERIFY(date.month() == chrono::month{2});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.index() == 2);
	VERIFY(date.weekday_indexed() == chrono::weekday_indexed{chrono::Sunday, 2});
	VERIFY(date.ok());
	VERIFY(date == chrono::year_month{chrono::year{2019}, chrono::month{2}}/chrono::Sunday[2]);
	VERIFY(date == chrono::year{2019}/chrono::month_weekday{chrono::month{2}, chrono::Sunday[2]});
	VERIFY(date == 2019/chrono::month_weekday{chrono::month{2}, chrono::Sunday[2]});
	VERIFY(date == chrono::month_weekday{chrono::month{2}, chrono::Sunday[2]}/chrono::year{2019});
	VERIFY(date == chrono::month_weekday{chrono::month{2}, chrono::Sunday[2]}/2019);
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2019_y/2/10);
	VERIFY(date == chrono::year_month_weekday{chrono::sys_days{2019_y/2/10}});
	VERIFY(date == chrono::year_month_weekday{chrono::local_days{2019_y/2/10}});

	date += chrono::months{1};
	VERIFY(date.year() == chrono::year{2019});
	VERIFY(date.month() == chrono::month{3});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.index() == 2);
	VERIFY(date.weekday_indexed() == chrono::weekday_indexed{chrono::Sunday, 2});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::local_days{date}} == 2019_y/3/10);

	date += chrono::months{10};
	VERIFY(date.year() == chrono::year{2020});
	VERIFY(date.month() == chrono::month{1});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.index() == 2);
	VERIFY(date.weekday_indexed() == chrono::weekday_indexed{chrono::Sunday, 2});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2020_y/1/12);

	date += chrono::years{2};
	VERIFY(date.year() == chrono::year{2022});
	VERIFY(date.month() == chrono::month{1});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.index() == 2);
	VERIFY(date.weekday_indexed() == chrono::weekday_indexed{chrono::Sunday, 2});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2022_y/1/9);

	date -= chrono::years{3};
	VERIFY(date.year() == chrono::year{2019});
	VERIFY(date.month() == chrono::month{1});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.index() == 2);
	VERIFY(date.weekday_indexed() == chrono::weekday_indexed{chrono::Sunday, 2});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2019_y/1/13);

	date -= chrono::months{3};
	VERIFY(date.year() == chrono::year{2018});
	VERIFY(date.month() == chrono::month{10});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.index() == 2);
	VERIFY(date.weekday_indexed() == chrono::weekday_indexed{chrono::Sunday, 2});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2018_y/10/14);

	// monthsとyearsのどちらにも暗黙変換できるとき
	using decades = chrono::duration<int, hamon::ratio_multiply<chrono::years::period, hamon::ratio<10>>>;

	date += decades{2};
	VERIFY(date.year() == chrono::year{2038});
	VERIFY(date.month() == chrono::month{10});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.index() == 2);
	VERIFY(date.weekday_indexed() == chrono::weekday_indexed{chrono::Sunday, 2});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2038_y/10/10);

	date -= decades{3};
	VERIFY(date.year() == chrono::year{2008});
	VERIFY(date.month() == chrono::month{10});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.index() == 2);
	VERIFY(date.weekday_indexed() == chrono::weekday_indexed{chrono::Sunday, 2});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2008_y/10/12);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	namespace chrono = hamon::chrono;
	using namespace hamon::chrono_literals;

	chrono::year_month_weekday_last date = 2019_y/2/chrono::Sunday[chrono::last];
	VERIFY(date.year() == chrono::year{2019});
	VERIFY(date.month() == chrono::month{2});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.weekday_last() == chrono::weekday_last{chrono::Sunday});
	VERIFY(date.ok());
	VERIFY(date == chrono::year_month{chrono::year{2019}, chrono::month{2}}/chrono::Sunday[chrono::last]);
	VERIFY(date == chrono::year{2019}/chrono::month_weekday_last{chrono::month{2}, chrono::Sunday[chrono::last]});
	VERIFY(date == 2019/chrono::month_weekday_last{chrono::month{2}, chrono::Sunday[chrono::last]});
	VERIFY(date == chrono::month_weekday_last{chrono::month{2}, chrono::Sunday[chrono::last]}/chrono::year{2019});
	VERIFY(date == chrono::month_weekday_last{chrono::month{2}, chrono::Sunday[chrono::last]}/2019);
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2019_y/2/24);
	VERIFY(chrono::year_month_day{chrono::local_days{date}} == 2019_y/2/24);

	date += chrono::months{1};
	VERIFY(date.year() == chrono::year{2019});
	VERIFY(date.month() == chrono::month{3});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.weekday_last() == chrono::weekday_last{chrono::Sunday});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2019_y/3/31);

	date += chrono::months{11};
	VERIFY(date.year() == chrono::year{2020});
	VERIFY(date.month() == chrono::month{2});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.weekday_last() == chrono::weekday_last{chrono::Sunday});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2020_y/2/23);

	date += chrono::years{1};
	VERIFY(date.year() == chrono::year{2021});
	VERIFY(date.month() == chrono::month{2});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.weekday_last() == chrono::weekday_last{chrono::Sunday});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2021_y/2/28);

	date -= chrono::months{3};
	VERIFY(date.year() == chrono::year{2020});
	VERIFY(date.month() == chrono::month{11});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.weekday_last() == chrono::weekday_last{chrono::Sunday});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2020_y/11/29);

	date -= chrono::years{2};
	VERIFY(date.year() == chrono::year{2018});
	VERIFY(date.month() == chrono::month{11});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.weekday_last() == chrono::weekday_last{chrono::Sunday});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2018_y/11/25);

	// monthsとyearsのどちらにも暗黙変換できるとき
	using decades = chrono::duration<int, hamon::ratio_multiply<chrono::years::period, hamon::ratio<10>>>;

	date += decades{2};
	VERIFY(date.year() == chrono::year{2038});
	VERIFY(date.month() == chrono::month{11});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.weekday_last() == chrono::weekday_last{chrono::Sunday});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2038_y/11/28);

	date -= decades{3};
	VERIFY(date.year() == chrono::year{2008});
	VERIFY(date.month() == chrono::month{11});
	VERIFY(date.weekday() == chrono::Sunday);
	VERIFY(date.weekday_last() == chrono::weekday_last{chrono::Sunday});
	VERIFY(date.ok());
	VERIFY(chrono::year_month_day{chrono::sys_days{date}} == 2008_y/11/30);

	return true;
}

#undef VERIFY

GTEST_TEST(ChronoTest, YearMonthWeekdayTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2());

	namespace chrono = hamon::chrono;

	// year_month_weekday
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday ymwd{
			chrono::year{1999}, chrono::month{12}, chrono::Monday[1]};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{1999}, ymwd.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{12}, ymwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Monday, ymwd.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, ymwd.index());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ymwd.ok());
	}
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd = chrono::year{2020}/3/23;
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday ymwd{chrono::sys_days{ymd}};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, ymwd.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, ymwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Monday, ymwd.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, ymwd.index());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ymwd.ok());
	}
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd = chrono::year{2021}/12/25;
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday ymwd{chrono::local_days{ymd}};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2021}, ymwd.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{12}, ymwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Saturday, ymwd.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, ymwd.index());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ymwd.ok());
	}

	// sys_days
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR chrono::sys_days date1 = 2020_y/3/chrono::Sunday[1];
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year_month_day{date1}, 2020_y/3/1);

		HAMON_CXX11_CONSTEXPR chrono::sys_days date2 = 2020_y/3/chrono::Sunday[2];
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year_month_day{date2}, 2020_y/3/8);

		HAMON_CXX11_CONSTEXPR chrono::sys_days date3 = 2020_y/3/chrono::Sunday[0];
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year_month_day{date3}, 2020_y/2/23);

		HAMON_CXX11_CONSTEXPR chrono::sys_days date4 = 2020_y/3/chrono::Sunday[10];
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year_month_day{date4}, 2020_y/5/3);
	}

	// local_days
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR chrono::local_days date1{2020_y/3/chrono::Sunday[1]};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year_month_day{date1}, 2020_y/3/1);

		HAMON_CXX11_CONSTEXPR chrono::local_days date2{2020_y/3/chrono::Sunday[2]};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year_month_day{date2}, 2020_y/3/8);

		HAMON_CXX11_CONSTEXPR chrono::local_days date3{2020_y/3/chrono::Sunday[0]};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year_month_day{date3}, 2020_y/2/23);

		HAMON_CXX11_CONSTEXPR chrono::local_days date4{2020_y/3/chrono::Sunday[10]};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year_month_day{date4}, 2020_y/5/3);
	}

	// ok
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/1/chrono::Sunday[1]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/3/chrono::Sunday[1]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/3/chrono::Sunday[5]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/12/chrono::Sunday[1]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((9999_y/3/chrono::Sunday[1]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/3/chrono::Sunday[0]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/3/chrono::Sunday[6]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/0/chrono::Sunday[1]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/13/chrono::Sunday[1]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((-32768_y/3/chrono::Sunday[1]).ok());

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2021_y/1/chrono::Sunday[5]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2021_y/1/chrono::Monday[5]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2021_y/1/chrono::Tuesday[5]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2021_y/1/chrono::Wednesday[5]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2021_y/1/chrono::Thursday[5]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2021_y/1/chrono::Friday[5]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2021_y/1/chrono::Saturday[5]).ok());
	}

	// compare
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday ymwd1 = 2020_y/1/chrono::Sunday[1];
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday ymwd2 = 2020_y/1/chrono::Sunday[1];
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday ymwd3 = 2020_y/1/chrono::Sunday[2];
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday ymwd4 = 2020_y/1/chrono::Saturday[1];
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday ymwd5 = 2020_y/2/chrono::Sunday[1];
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday ymwd6 = 2019_y/1/chrono::Sunday[1];

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 == ymwd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 == ymwd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 == ymwd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 == ymwd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 == ymwd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 == ymwd6);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 != ymwd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 != ymwd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 != ymwd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 != ymwd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 != ymwd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 != ymwd6);
	}

	{
		using namespace hamon::chrono_literals;

		// year_month_weekday + months
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/1/chrono::Sunday[1] + chrono::months{1} == 2020_y/2/chrono::Sunday[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2021_y/9/chrono::Monday[2] + chrono::months{4} == 2022_y/1/chrono::Monday[2]);

		// months + year_month_weekday
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(chrono::months{1} + 2020_y/1/chrono::Sunday[1] == 2020_y/2/chrono::Sunday[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(chrono::months{14} + 2020_y/1/chrono::Sunday[1] == 2021_y/3/chrono::Sunday[1]);

		// year_month_weekday - months
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/1/chrono::Sunday[1] - chrono::months{1} == 2019_y/12/chrono::Sunday[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(1999_y/11/chrono::Friday[4] - chrono::months{4} == 1999_y/7/chrono::Friday[4]);

		// year_month_weekday + years
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/1/chrono::Sunday[1] + chrono::years{1} == 2021_y/1/chrono::Sunday[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2025_y/2/chrono::Sunday[2] + chrono::years{5} == 2030_y/2/chrono::Sunday[2]);

		// years + year_month_weekday
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(chrono::years{1} + 2020_y/1/chrono::Sunday[1] == 2021_y/1/chrono::Sunday[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(chrono::years{3} + 2020_y/3/chrono::Monday[1] == 2023_y/3/chrono::Monday[1]);

		// year_month_weekday - years
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/1/chrono::Sunday[1] - chrono::years{1} == 2019_y/1/chrono::Sunday[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2030_y/12/chrono::Tuesday[2] - chrono::years{4} == 2026_y/12/chrono::Tuesday[2]);

		// monthsとyearsのどちらにも暗黙変換できるとき
		{
			using decades = chrono::duration<int, hamon::ratio_multiply<chrono::years::period, hamon::ratio<10>>>;
			HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/1/chrono::Sunday[1] + decades{1} == 2030_y/1/chrono::Sunday[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(decades{2} + 2020_y/1/chrono::Sunday[1] == 2040_y/1/chrono::Sunday[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/1/chrono::Sunday[1] - decades{3} == 1990_y/1/chrono::Sunday[1]);
		}
	}

	// Conventional syntax operators
	{
		// year_month / weekday_indexed
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::year_month{chrono::year{2020}, chrono::month{1}}/chrono::Sunday[1];
			static_assert(hamon::is_same<decltype(date), chrono::year_month_weekday const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[1], date.weekday_indexed());
		}

		// year / month_weekday
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::year{2020}/chrono::month_weekday{chrono::month{1}, chrono::Sunday[2]};
			static_assert(hamon::is_same<decltype(date), chrono::year_month_weekday const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[2], date.weekday_indexed());
		}

		// int / month_weekday
		{
			HAMON_CXX11_CONSTEXPR auto date = 2021/chrono::month_weekday{chrono::month{1}, chrono::Sunday[2]};
			static_assert(hamon::is_same<decltype(date), chrono::year_month_weekday const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2021}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[2], date.weekday_indexed());
		}

		// month_weekday / year
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::month_weekday{chrono::month{5}, chrono::Sunday[2]}/chrono::year{2020};
			static_assert(hamon::is_same<decltype(date), chrono::year_month_weekday const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{5}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[2], date.weekday_indexed());
		}

		// month_weekday / int
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::month_weekday{chrono::month{5}, chrono::Monday[2]}/2020;
			static_assert(hamon::is_same<decltype(date), chrono::year_month_weekday const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{5}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Monday[2], date.weekday_indexed());
		}
	}

	// year_month_weekday_last
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday_last ymwd{
			chrono::year{2020}, chrono::month{3}, chrono::Sunday[chrono::last]};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, ymwd.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, ymwd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday, ymwd.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[chrono::last], ymwd.weekday_last());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ymwd.ok());
	}

	// sys_days
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR chrono::sys_days date = 2020_y/3/chrono::Sunday[chrono::last];
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year_month_day{date}, 2020_y/3/29);
	}

	// local_days
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR chrono::local_days date {2020_y/3/chrono::Sunday[chrono::last]};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year_month_day{date}, 2020_y/3/29);
	}

	// ok
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/1/chrono::Sunday[chrono::last]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/3/chrono::Monday[chrono::last]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/12/chrono::Tuesday[chrono::last]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((9999_y/3/chrono::Wednesday[chrono::last]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/0/chrono::Sunday[chrono::last]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/13/chrono::Sunday[chrono::last]).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((-32768_y/3/chrono::Sunday[chrono::last]).ok());
	}

	// compare
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday_last ymwd1 = 2020_y/1/chrono::Sunday[chrono::last];
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday_last ymwd2 = 2020_y/1/chrono::Sunday[chrono::last];
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday_last ymwd3 = 2020_y/1/chrono::Saturday[chrono::last];
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday_last ymwd4 = 2020_y/2/chrono::Sunday[chrono::last];
		HAMON_CXX11_CONSTEXPR chrono::year_month_weekday_last ymwd5 = 2019_y/1/chrono::Sunday[chrono::last];

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 == ymwd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 == ymwd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 == ymwd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 == ymwd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 == ymwd5);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 != ymwd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymwd1 != ymwd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 != ymwd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 != ymwd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymwd1 != ymwd5);
	}

	{
		using namespace hamon::chrono_literals;

		// year_month_weekday_last + months
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/2/chrono::Sunday[chrono::last] + chrono::months{1} == 2020_y/3/chrono::Sunday[chrono::last]);

		// months + year_month_weekday_last
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(chrono::months{1} + 2020_y/2/chrono::Sunday[chrono::last] == 2020_y/3/chrono::Sunday[chrono::last]);

		// year_month_weekday_last - months
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/2/chrono::Sunday[chrono::last] - chrono::months{1} == 2020_y/1/chrono::Sunday[chrono::last]);

		// year_month_weekday_last + years
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2019_y/3/chrono::Sunday[chrono::last] + chrono::years{1} == 2020_y/3/chrono::Sunday[chrono::last]);

		// years + year_month_weekday_last
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(chrono::years{1} + 2019_y/3/chrono::Sunday[chrono::last] == 2020_y/3/chrono::Sunday[chrono::last]);

		// year_month_weekday_last - years
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2019_y/3/chrono::Sunday[chrono::last] - chrono::years{1} == 2018_y/3/chrono::Sunday[chrono::last]);

		// monthsとyearsのどちらにも暗黙変換できるとき
		{
			using decades = chrono::duration<int, hamon::ratio_multiply<chrono::years::period, hamon::ratio<10>>>;
			HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/1/chrono::Sunday[chrono::last] + decades{1} == 2030_y/1/chrono::Sunday[chrono::last]);
			HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(decades{2} + 2020_y/1/chrono::Sunday[chrono::last] == 2040_y/1/chrono::Sunday[chrono::last]);
			HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/1/chrono::Sunday[chrono::last] - decades{3} == 1990_y/1/chrono::Sunday[chrono::last]);
		}
	}

	// Conventional syntax operators
	{
		// year_month / weekday_last
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::year_month{chrono::year{2020}, chrono::month{1}}/chrono::Sunday[chrono::last];
			static_assert(hamon::is_same<decltype(date), chrono::year_month_weekday_last const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[chrono::last], date.weekday_last());
		}

		// year / month_weekday_last
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::year{2020}/chrono::month_weekday_last{chrono::month{1}, chrono::Sunday[chrono::last]};
			static_assert(hamon::is_same<decltype(date), chrono::year_month_weekday_last const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[chrono::last], date.weekday_last());
		}

		// int / month_weekday_last
		{
			HAMON_CXX11_CONSTEXPR auto date = 2021/chrono::month_weekday_last{chrono::month{1}, chrono::Sunday[chrono::last]};
			static_assert(hamon::is_same<decltype(date), chrono::year_month_weekday_last const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2021}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[chrono::last], date.weekday_last());
		}

		// month_weekday_last / year
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::month_weekday_last{chrono::month{5}, chrono::Sunday[chrono::last]}/chrono::year{2020};
			static_assert(hamon::is_same<decltype(date), chrono::year_month_weekday_last const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{5}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Sunday[chrono::last], date.weekday_last());
		}

		// month_weekday_last / int
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::month_weekday_last{chrono::month{5}, chrono::Monday[chrono::last]}/2020;
			static_assert(hamon::is_same<decltype(date), chrono::year_month_weekday_last const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{5}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::Monday[chrono::last], date.weekday_last());
		}
	}
}

}	// namespace year_month_weekday_test

}	// namespace hamon_chrono_test
