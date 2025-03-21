/**
 *	@file	unit_test_chrono_year_month.cpp
 *
 *	@brief	year_month のテスト
 */

#include <hamon/chrono/year_month.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace year_month_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test()
{
	namespace chrono = hamon::chrono;

	chrono::year_month ym = chrono::year{2020}/3;
	VERIFY(ym.year() == chrono::year{2020});
	VERIFY(ym.month() == chrono::month{3});
	VERIFY(ym.ok());

	ym += chrono::months{1};
	VERIFY(ym.year() == chrono::year{2020});
	VERIFY(ym.month() == chrono::month{4});
	VERIFY(ym.ok());

	ym += chrono::months{10};
	VERIFY(ym.year() == chrono::year{2021});
	VERIFY(ym.month() == chrono::month{2});
	VERIFY(ym.ok());

	ym += chrono::years{1};
	VERIFY(ym.year() == chrono::year{2022});
	VERIFY(ym.month() == chrono::month{2});
	VERIFY(ym.ok());

	ym += chrono::years{3};
	VERIFY(ym.year() == chrono::year{2025});
	VERIFY(ym.month() == chrono::month{2});
	VERIFY(ym.ok());

	ym -= chrono::months{3};
	VERIFY(ym.year() == chrono::year{2024});
	VERIFY(ym.month() == chrono::month{11});
	VERIFY(ym.ok());

	ym -= chrono::years{2};
	VERIFY(ym.year() == chrono::year{2022});
	VERIFY(ym.month() == chrono::month{11});
	VERIFY(ym.ok());

	// monthsとyearsのどちらにも暗黙変換できるとき
	using decades = chrono::duration<int, std::ratio_multiply<chrono::years::period, std::ratio<10>>>;

	ym += decades{3};
	VERIFY(ym.year() == chrono::year{2052});
	VERIFY(ym.month() == chrono::month{11});
	VERIFY(ym.ok());

	ym -= decades{2};
	VERIFY(ym.year() == chrono::year{2032});
	VERIFY(ym.month() == chrono::month{11});
	VERIFY(ym.ok());

	return true;
}

#undef VERIFY

GTEST_TEST(ChronoTest, YearMonthTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

	namespace chrono = hamon::chrono;

	// year_month
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month ym{chrono::year{1999}, chrono::month{12}};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{1999}, ym.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{12}, ym.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(ym.ok());
	}

	// ok
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::year_month{chrono::year{0}, chrono::month{ 0}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::year_month{chrono::year{0}, chrono::month{ 1}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::year_month{chrono::year{0}, chrono::month{12}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::year_month{chrono::year{0}, chrono::month{13}}.ok()));

	// compare
	{
		HAMON_CXX11_CONSTEXPR chrono::year_month ym1{chrono::year{4}, chrono::month{5}};
		HAMON_CXX11_CONSTEXPR chrono::year_month ym2{chrono::year{4}, chrono::month{5}};
		HAMON_CXX11_CONSTEXPR chrono::year_month ym3{chrono::year{4}, chrono::month{4}};
		HAMON_CXX11_CONSTEXPR chrono::year_month ym4{chrono::year{4}, chrono::month{6}};
		HAMON_CXX11_CONSTEXPR chrono::year_month ym5{chrono::year{3}, chrono::month{5}};
		HAMON_CXX11_CONSTEXPR chrono::year_month ym6{chrono::year{3}, chrono::month{6}};
		HAMON_CXX11_CONSTEXPR chrono::year_month ym7{chrono::year{5}, chrono::month{4}};
		HAMON_CXX11_CONSTEXPR chrono::year_month ym8{chrono::year{5}, chrono::month{5}};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 == ym1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 == ym2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 == ym3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 == ym4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 == ym5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 == ym6);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 == ym7);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 == ym8);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 != ym1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 != ym2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 != ym3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 != ym4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 != ym5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 != ym6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 != ym7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 != ym8);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 <  ym1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 <  ym2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 <  ym3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 <  ym4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 <  ym5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 <  ym6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 <  ym7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 <  ym8);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 >  ym1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 >  ym2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 >  ym3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 >  ym4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 >  ym5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 >  ym6);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 >  ym7);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 >  ym8);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 <= ym1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 <= ym2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 <= ym3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 <= ym4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 <= ym5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 <= ym6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 <= ym7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 <= ym8);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 >= ym1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 >= ym2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 >= ym3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 >= ym4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 >= ym5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (ym1 >= ym6);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 >= ym7);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(ym1 >= ym8);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(ym1 <=> ym1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(ym1 <=> ym2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ym1 <=> ym3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ym1 <=> ym4));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ym1 <=> ym5));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ym1 <=> ym6));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ym1 <=> ym7));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(ym1 <=> ym8));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(ym1 <=> ym1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(ym1 <=> ym2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(ym1 <=> ym3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(ym1 <=> ym4));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(ym1 <=> ym5));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(ym1 <=> ym6));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(ym1 <=> ym7));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(ym1 <=> ym8));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(ym1 <=> ym1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(ym1 <=> ym2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(ym1 <=> ym3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(ym1 <=> ym4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(ym1 <=> ym5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(ym1 <=> ym6));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(ym1 <=> ym7));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(ym1 <=> ym8));
#endif
	}

	using namespace hamon::chrono_literals;

	// year_month + months
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3 + hamon::chrono::months{1} == 2020_y/4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3 + hamon::chrono::months{14} == 2021_y/5);

	// months + year_month
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::months{1} + 2020_y/3== 2020_y/4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::months{8} + 2021_y/11== 2022_y/7);

	// year_month - months
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3 - hamon::chrono::months{1} == 2020_y/2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3 - hamon::chrono::months{3} == 2019_y/12);

	// year_month - year_month
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3 - 2019_y/12 == hamon::chrono::months{3});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2024_y/12 - 2024_y/5 == hamon::chrono::months{7});

	// year_month + years
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3 + hamon::chrono::years{1} == 2021_y/3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2021_y/1 + hamon::chrono::years{3} == 2024_y/1);

	// years + year_month
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::years{1} + 2020_y/3== 2021_y/3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::years{5} + 1999_y/8== 2004_y/8);

	// year_month - years
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3 - hamon::chrono::years{1} == 2019_y/3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2025_y/3 - hamon::chrono::years{8} == 2017_y/3);

	// monthsとyearsのどちらにも暗黙変換できるとき
	{
		using decades = chrono::duration<int, std::ratio_multiply<chrono::years::period, std::ratio<10>>>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3 + decades{1} == 2030_y/3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(decades{2} + 2020_y/3 == 2040_y/3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(2020_y/3 - decades{3} == 1990_y/3);
	}

	// Conventional syntax operators

	// year / month
	{
		HAMON_CXX11_CONSTEXPR auto date = chrono::year{2020}/chrono::month{1};
		static_assert(hamon::is_same<decltype(date), chrono::year_month const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, date.month());
	}
	{
		HAMON_CXX11_CONSTEXPR auto date = 2021_y/chrono::March;
		static_assert(hamon::is_same<decltype(date), chrono::year_month const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2021}, date.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, date.month());
	}
	// year / int
	{
		HAMON_CXX11_CONSTEXPR auto date = chrono::year{2020}/2;
		static_assert(hamon::is_same<decltype(date), chrono::year_month const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::year{2020}, date.year());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{2}, date.month());
	}
}

}	// namespace year_month_test

}	// namespace hamon_chrono_test
