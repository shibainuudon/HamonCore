/**
 *	@file	unit_test_chrono_year_month_day.cpp
 *
 *	@brief	year_month_day のテスト
 */

#include <hamon/chrono/year_month_day.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace year_month_day_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test1()
{
	namespace chrono = hamon::chrono;

	chrono::year_month_day ymd = chrono::year{2020}/3/1;
	VERIFY(ymd.year() == chrono::year{2020});
	VERIFY(ymd.month() == chrono::month{3});
	VERIFY(ymd.day() == chrono::day{1});
	VERIFY(ymd.ok());
	VERIFY(ymd == chrono::year{2020}/(chrono::month{3}/1));

	ymd += chrono::months{1};
	VERIFY(ymd.year() == chrono::year{2020});
	VERIFY(ymd.month() == chrono::month{4});
	VERIFY(ymd.day() == chrono::day{1});
	VERIFY(ymd.ok());
	VERIFY(ymd == 2020/(chrono::month{4}/1));

	ymd += chrono::months{10};
	VERIFY(ymd.year() == chrono::year{2021});
	VERIFY(ymd.month() == chrono::month{2});
	VERIFY(ymd.day() == chrono::day{1});
	VERIFY(ymd.ok());
	VERIFY(ymd == chrono::month{2}/1/chrono::year{2021});

	ymd += chrono::years{1};
	VERIFY(ymd.year() == chrono::year{2022});
	VERIFY(ymd.month() == chrono::month{2});
	VERIFY(ymd.day() == chrono::day{1});
	VERIFY(ymd.ok());
	VERIFY(ymd == chrono::month{2}/1/2022);

	ymd += chrono::years{5};
	VERIFY(ymd.year() == chrono::year{2027});
	VERIFY(ymd.month() == chrono::month{2});
	VERIFY(ymd.day() == chrono::day{1});
	VERIFY(ymd.ok());

	ymd -= chrono::months{3};
	VERIFY(ymd.year() == chrono::year{2026});
	VERIFY(ymd.month() == chrono::month{11});
	VERIFY(ymd.day() == chrono::day{1});
	VERIFY(ymd.ok());

	ymd -= chrono::years{3};
	VERIFY(ymd.year() == chrono::year{2023});
	VERIFY(ymd.month() == chrono::month{11});
	VERIFY(ymd.day() == chrono::day{1});
	VERIFY(ymd.ok());

	// monthsとyearsのどちらにも暗黙変換できるとき
	using decades = chrono::duration<int, std::ratio_multiply<chrono::years::period, std::ratio<10>>>;

	ymd += decades{3};
	VERIFY(ymd.year() == chrono::year{2053});
	VERIFY(ymd.month() == chrono::month{11});
	VERIFY(ymd.day() == chrono::day{1});
	VERIFY(ymd.ok());

	ymd -= decades{4};
	VERIFY(ymd.year() == chrono::year{2013});
	VERIFY(ymd.month() == chrono::month{11});
	VERIFY(ymd.day() == chrono::day{1});
	VERIFY(ymd.ok());

	VERIFY(ymd == chrono::year_month_day{chrono::sys_days{ymd}});
	VERIFY(ymd == chrono::year_month_day{chrono::local_days{ymd}});

	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	namespace chrono = hamon::chrono;

	chrono::year_month_day_last ymd = chrono::year{2020}/1/chrono::last;
	VERIFY(ymd.year() == chrono::year{2020});
	VERIFY(ymd.month() == chrono::month{1});
	VERIFY(ymd.day() == chrono::day{31});
	VERIFY(ymd.ok());
	VERIFY(ymd == chrono::year{2020}/chrono::month_day_last{chrono::month{1}});

	ymd += chrono::months{5};
	VERIFY(ymd.year() == chrono::year{2020});
	VERIFY(ymd.month() == chrono::month{6});
	VERIFY(ymd.day() == chrono::day{30});
	VERIFY(ymd.ok());
	VERIFY(ymd == 2020/chrono::month_day_last{chrono::month{6}});

	ymd += chrono::months{8};
	VERIFY(ymd.year() == chrono::year{2021});
	VERIFY(ymd.month() == chrono::month{2});
	VERIFY(ymd.day() == chrono::day{28});
	VERIFY(ymd.ok());
	VERIFY(ymd == chrono::month_day_last{chrono::month{2}}/chrono::year{2021});

	ymd += chrono::years{1};
	VERIFY(ymd.year() == chrono::year{2022});
	VERIFY(ymd.month() == chrono::month{2});
	VERIFY(ymd.day() == chrono::day{28});
	VERIFY(ymd.ok());
	VERIFY(ymd == chrono::month_day_last{chrono::month{2}}/2022);

	ymd += chrono::years{2};
	VERIFY(ymd.year() == chrono::year{2024});
	VERIFY(ymd.month() == chrono::month{2});
	VERIFY(ymd.day() == chrono::day{29});
	VERIFY(ymd.ok());

	ymd -= chrono::months{3};
	VERIFY(ymd.year() == chrono::year{2023});
	VERIFY(ymd.month() == chrono::month{11});
	VERIFY(ymd.day() == chrono::day{30});
	VERIFY(ymd.ok());

	ymd -= chrono::years{2};
	VERIFY(ymd.year() == chrono::year{2021});
	VERIFY(ymd.month() == chrono::month{11});
	VERIFY(ymd.day() == chrono::day{30});
	VERIFY(ymd.ok());

	// monthsとyearsのどちらにも暗黙変換できるとき
	using decades = chrono::duration<int, std::ratio_multiply<chrono::years::period, std::ratio<10>>>;

	ymd += decades{1};
	VERIFY(ymd.year() == chrono::year{2031});
	VERIFY(ymd.month() == chrono::month{11});
	VERIFY(ymd.day() == chrono::day{30});
	VERIFY(ymd.ok());

	ymd -= decades{2};
	VERIFY(ymd.year() == chrono::year{2011});
	VERIFY(ymd.month() == chrono::month{11});
	VERIFY(ymd.day() == chrono::day{30});
	VERIFY(ymd.ok());

	return true;
}

#undef VERIFY

GTEST_TEST(ChronoTest, YearMonthDayTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2());

	namespace chrono = hamon::chrono;

	// year_month_day
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd{chrono::year{1999}, chrono::month{12}, chrono::day{31}};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{1999}, ymd.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{12}, ymd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{31}, ymd.day());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ymd.ok());
	}
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd{chrono::year{2023}/chrono::April/chrono::last};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2023}, ymd.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{4}, ymd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{30}, ymd.day());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ymd.ok());
	}
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd{chrono::year{2020}/2/chrono::last};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, ymd.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{2}, ymd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{29}, ymd.day());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ymd.ok());
	}
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd{chrono::sys_days{}};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{1970}, ymd.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, ymd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{1}, ymd.day());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ymd.ok());
	}
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd{chrono::local_days{}};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{1970}, ymd.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, ymd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{1}, ymd.day());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ymd.ok());
	}

	// ok
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((-32768_y/1/1).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/0/1).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/1/0).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/1/1).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/1/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/1/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/1/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/2/28).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/2/29).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/2/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/3/1).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/3/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/3/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/3/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/4/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/4/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/4/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/5/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/5/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/5/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/6/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/6/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/6/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/7/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/7/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/7/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/8/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/8/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/8/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/9/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/9/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/9/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/10/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/10/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/10/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/11/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/11/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/11/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/12/0).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/12/1).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/12/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2020_y/12/31).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/12/32).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2020_y/13/1).ok());

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2021_y/2/28).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2021_y/2/29).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((2021_y/2/30).ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((2021_y/3/1).ok());
	}

	// compare
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd1{chrono::year{4}, chrono::month{5}, chrono::day{6}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd2{chrono::year{4}, chrono::month{5}, chrono::day{6}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd3{chrono::year{4}, chrono::month{5}, chrono::day{5}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd4{chrono::year{4}, chrono::month{5}, chrono::day{7}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd5{chrono::year{4}, chrono::month{4}, chrono::day{6}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd6{chrono::year{4}, chrono::month{6}, chrono::day{6}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd7{chrono::year{3}, chrono::month{5}, chrono::day{6}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day ymd8{chrono::year{5}, chrono::month{5}, chrono::day{6}};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 == ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 == ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 == ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 == ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 == ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 == ymd6);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 == ymd7);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 == ymd8);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 != ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 != ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 != ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 != ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 != ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 != ymd6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 != ymd7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 != ymd8);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <  ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <  ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <  ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <  ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <  ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <  ymd6);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <  ymd7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <  ymd8);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >  ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >  ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >  ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >  ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >  ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >  ymd6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >  ymd7);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >  ymd8);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <= ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <= ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <= ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <= ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <= ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <= ymd6);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <= ymd7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <= ymd8);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >= ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >= ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >= ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >= ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >= ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >= ymd6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >= ymd7);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >= ymd8);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(ymd1 <=> ymd1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(ymd1 <=> ymd2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ymd1 <=> ymd3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ymd1 <=> ymd4));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ymd1 <=> ymd5));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ymd1 <=> ymd6));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ymd1 <=> ymd7));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ymd1 <=> ymd8));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(ymd1 <=> ymd1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(ymd1 <=> ymd2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(ymd1 <=> ymd3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(ymd1 <=> ymd4));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(ymd1 <=> ymd5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(ymd1 <=> ymd6));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(ymd1 <=> ymd7));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(ymd1 <=> ymd8));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(ymd1 <=> ymd1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(ymd1 <=> ymd2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(ymd1 <=> ymd3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(ymd1 <=> ymd4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(ymd1 <=> ymd5));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(ymd1 <=> ymd6));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(ymd1 <=> ymd7));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(ymd1 <=> ymd8));
#endif
	}

	// sys_days
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{0},     chrono::sys_days{chrono::year{1970}/1/1}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{18322}, chrono::sys_days{chrono::year{2020}/3/1}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{20088}, chrono::sys_days{chrono::year{2024}/12/31}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{20172}, chrono::sys_days{chrono::year{2025}/3/25}.time_since_epoch());
	}

	// local_days
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{0},     chrono::local_days{chrono::year{1970}/1/1}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{18322}, chrono::local_days{chrono::year{2020}/3/1}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{20088}, chrono::local_days{chrono::year{2024}/12/31}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{20172}, chrono::local_days{chrono::year{2025}/3/25}.time_since_epoch());
	}

	{
		using namespace hamon::chrono_literals;

		// year_month_day + months
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/1 + hamon::chrono::months{1} == 2020_y/4/1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/1 + hamon::chrono::months{10} == 2021_y/1/1);

		// months + year_month_day
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::months{1} + 2020_y/3/1 == 2020_y/4/1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::months{40} + 2020_y/3/1 == 2023_y/7/1);

		// year_month_day - months
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/1 - hamon::chrono::months{1} == 2020_y/2/1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/1 - hamon::chrono::months{5} == 2019_y/10/1);

		// year_month_day + years
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/1 + hamon::chrono::years{1} == 2021_y/3/1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/1 + hamon::chrono::years{3} == 2023_y/3/1);

		// years + year_month_day
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::years{1} + 2020_y/3/1 == 2021_y/3/1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::years{4} + 2020_y/3/1 == 2024_y/3/1);

		// year_month_day - years
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/1 - hamon::chrono::years{1} == 2019_y/3/1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/1 - hamon::chrono::years{5} == 2015_y/3/1);

		// monthsとyearsのどちらにも暗黙変換できるとき
		{
			using decades = chrono::duration<int, std::ratio_multiply<chrono::years::period, std::ratio<10>>>;
			HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/10 + decades{1} == 2030_y/3/10);
			HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(decades{2} + 2020_y/3/10 == 2040_y/3/10);
			HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/10 - decades{3} == 1990_y/3/10);
		}
	}

	// Conventional syntax operators

	// year_month / day
	{
		HAMON_CXX11_CONSTEXPR auto date = chrono::year_month{chrono::year{2020}, chrono::month{1}}/chrono::day{2};
		static_assert(hamon::is_same<decltype(date), chrono::year_month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, date.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{2}, date.day());
	}

	// year_month / int
	{
		HAMON_CXX11_CONSTEXPR auto date = chrono::year_month{chrono::year{2020}, chrono::month{1}}/3;
		static_assert(hamon::is_same<decltype(date), chrono::year_month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, date.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{3}, date.day());
	}

	// year / month_day
	{
		HAMON_CXX11_CONSTEXPR auto date = chrono::year{2020}/chrono::month_day{chrono::month{2}, chrono::day{3}};
		static_assert(hamon::is_same<decltype(date), chrono::year_month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{2}, date.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{3}, date.day());
	}

	// int / month_day
	{
		HAMON_CXX11_CONSTEXPR auto date = 2021/chrono::month_day{chrono::month{2}, chrono::day{3}};
		static_assert(hamon::is_same<decltype(date), chrono::year_month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2021}, date.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{2}, date.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{3}, date.day());
	}

	// month_day / year
	{
		HAMON_CXX11_CONSTEXPR auto date = chrono::month_day{chrono::month{3}, chrono::day{4}}/chrono::year{2022};
		static_assert(hamon::is_same<decltype(date), chrono::year_month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2022}, date.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, date.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{4}, date.day());
	}

	// month_day / int
	{
		HAMON_CXX11_CONSTEXPR auto date = chrono::month_day{chrono::month{3}, chrono::day{4}}/2024;
		static_assert(hamon::is_same<decltype(date), chrono::year_month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2024}, date.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, date.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{4}, date.day());
	}

	// year_month_day_last
	{
		HAMON_CXX11_CONSTEXPR chrono::month_day_last mdl{chrono::month{3}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day_last ymd{chrono::year{2020}, mdl};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, ymd.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, ymd.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{31}, ymd.day());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(mdl, ymd.month_day_last());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ymd.ok());
	}

	// sys_days
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{30},    chrono::sys_days{chrono::year{1970}/1/chrono::last}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{18352}, chrono::sys_days{chrono::year{2020}/3/chrono::last}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{20088}, chrono::sys_days{chrono::year{2024}/12/chrono::last}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{20178}, chrono::sys_days{chrono::year{2025}/3/chrono::last}.time_since_epoch());
	}

	// local_days
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{30},    chrono::local_days{chrono::year{1970}/1/chrono::last}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{18352}, chrono::local_days{chrono::year{2020}/3/chrono::last}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{20088}, chrono::local_days{chrono::year{2024}/12/chrono::last}.time_since_epoch());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::days{20178}, chrono::local_days{chrono::year{2025}/3/chrono::last}.time_since_epoch());
	}

	// compare
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month_day_last ymd1{chrono::year{4}, chrono::month_day_last{chrono::month{3}}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day_last ymd2{chrono::year{4}, chrono::month_day_last{chrono::month{3}}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day_last ymd3{chrono::year{4}, chrono::month_day_last{chrono::month{2}}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day_last ymd4{chrono::year{4}, chrono::month_day_last{chrono::month{4}}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day_last ymd5{chrono::year{3}, chrono::month_day_last{chrono::month{3}}};
		HAMON_CXX11_CONSTEXPR chrono::year_month_day_last ymd6{chrono::year{5}, chrono::month_day_last{chrono::month{3}}};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 == ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 == ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 == ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 == ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 == ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 == ymd6);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 != ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 != ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 != ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 != ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 != ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 != ymd6);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <  ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <  ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <  ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <  ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <  ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <  ymd6);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >  ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >  ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >  ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >  ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >  ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >  ymd6);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <= ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <= ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <= ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <= ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 <= ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 <= ymd6);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >= ymd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >= ymd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >= ymd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >= ymd4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ymd1 >= ymd5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ymd1 >= ymd6);
	}

	{
		using namespace hamon::chrono_literals;

		// year_month_day_last + months
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/1/chrono::last + hamon::chrono::months{1} == 2020_y/2/29);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/2/chrono::last + hamon::chrono::months{2} == 2020_y/4/30);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/chrono::last + hamon::chrono::months{14} == 2021_y/5/31);

		// months + year_month_day_last
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::months{1} + 2020_y/1/chrono::last== 2020_y/2/29);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::months{3} + 2020_y/2/chrono::last== 2020_y/5/31);

		// year_month_day_last - months
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/12/chrono::last - hamon::chrono::months{1} == 2020_y/11/30);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3/chrono::last - hamon::chrono::months{6} == 2019_y/9/30);

		// year_month_day_last + years
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2019_y/2/chrono::last + hamon::chrono::years{1} == 2020_y/2/29);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/2/chrono::last + hamon::chrono::years{1} == 2021_y/2/28);

		// years + year_month_day_last
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::years{3} + 2019_y/5/chrono::last == 2022_y/5/31);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::years{4} + 2019_y/6/chrono::last == 2023_y/6/30);

		// year_month_day_last - years
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2024_y/2/chrono::last - hamon::chrono::years{1} == 2023_y/2/28);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2024_y/2/chrono::last - hamon::chrono::years{4} == 2020_y/2/29);
	}

	// Conventional syntax operators
	{
		// year_month / last_spec
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::year_month{chrono::year{2020}, chrono::month{1}}/chrono::last;
			static_assert(hamon::is_same<decltype(date), chrono::year_month_day_last const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{31}, date.day());
		}

		// year / month_day_last
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::year{2020}/chrono::month_day_last{chrono::month{2}};
			static_assert(hamon::is_same<decltype(date), chrono::year_month_day_last const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{2}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{29}, date.day());
		}

		// int / month_day_last
		{
			HAMON_CXX11_CONSTEXPR auto date = 2021/chrono::month_day_last{chrono::month{2}};
			static_assert(hamon::is_same<decltype(date), chrono::year_month_day_last const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2021}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{2}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{28}, date.day());
		}

		// month_day_last / year
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::month_day_last{chrono::month{4}}/chrono::year{2022};
			static_assert(hamon::is_same<decltype(date), chrono::year_month_day_last const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2022}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{4}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{30}, date.day());
		}

		// month_day_last / int
		{
			HAMON_CXX11_CONSTEXPR auto date = chrono::month_day_last{chrono::month{5}}/2023;
			static_assert(hamon::is_same<decltype(date), chrono::year_month_day_last const>::value, "");
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2023}, date.year());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{5}, date.month());
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{31}, date.day());
		}
	}
}

}	// namespace year_month_day_test

}	// namespace hamon_chrono_test
