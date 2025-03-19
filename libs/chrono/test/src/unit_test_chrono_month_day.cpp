/**
 *	@file	unit_test_chrono_month_day.cpp
 *
 *	@brief	month_day のテスト
 */

#include <hamon/chrono/month_day.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace month_day_test
{

GTEST_TEST(ChronoTest, MonthDayTest)
{
	namespace chrono = hamon::chrono;

	// month_day
	{
		HAMON_CXX11_CONSTEXPR chrono::month_day md{chrono::month{3}, chrono::day{1}};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, md.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{1}, md.day());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(md.ok());
	}

	// ok
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{1}, chrono::day{ 0}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{1}, chrono::day{ 1}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{1}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{1}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{1}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{2}, chrono::day{28}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{2}, chrono::day{29}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{2}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{3}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{3}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{3}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{4}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{4}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{4}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{5}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{5}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{5}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{6}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{6}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{6}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{7}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{7}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{7}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{8}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{8}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{8}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{9}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{9}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{9}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{10}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{10}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{10}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{11}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{11}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{11}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{12}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((chrono::month_day{chrono::month{12}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{12}, chrono::day{32}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{13}, chrono::day{ 0}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{13}, chrono::day{ 1}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{13}, chrono::day{30}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{13}, chrono::day{31}}.ok()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((chrono::month_day{chrono::month{13}, chrono::day{32}}.ok()));

	// compare
	{
		HAMON_CXX11_CONSTEXPR chrono::month_day md1{chrono::month{4}, chrono::day{5}};
		HAMON_CXX11_CONSTEXPR chrono::month_day md2{chrono::month{4}, chrono::day{5}};
		HAMON_CXX11_CONSTEXPR chrono::month_day md3{chrono::month{4}, chrono::day{4}};
		HAMON_CXX11_CONSTEXPR chrono::month_day md4{chrono::month{4}, chrono::day{6}};
		HAMON_CXX11_CONSTEXPR chrono::month_day md5{chrono::month{3}, chrono::day{5}};
		HAMON_CXX11_CONSTEXPR chrono::month_day md6{chrono::month{3}, chrono::day{6}};
		HAMON_CXX11_CONSTEXPR chrono::month_day md7{chrono::month{5}, chrono::day{4}};
		HAMON_CXX11_CONSTEXPR chrono::month_day md8{chrono::month{5}, chrono::day{5}};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 == md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 == md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 == md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 == md4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 == md5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 == md6);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 == md7);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 == md8);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 != md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 != md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 != md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 != md4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 != md5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 != md6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 != md7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 != md8);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <  md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <  md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <  md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <  md4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <  md5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <  md6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <  md7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <  md8);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >  md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >  md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >  md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >  md4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >  md5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >  md6);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >  md7);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >  md8);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <= md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <= md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <= md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <= md4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <= md5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <= md6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <= md7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <= md8);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >= md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >= md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >= md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >= md4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >= md5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >= md6);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >= md7);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >= md8);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(md1 <=> md1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(md1 <=> md2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(md1 <=> md3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(md1 <=> md4));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(md1 <=> md5));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(md1 <=> md6));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(md1 <=> md7));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(md1 <=> md8));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(md1 <=> md1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(md1 <=> md2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(md1 <=> md3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(md1 <=> md4));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(md1 <=> md5));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(md1 <=> md6));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(md1 <=> md7));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(md1 <=> md8));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(md1 <=> md1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(md1 <=> md2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(md1 <=> md3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(md1 <=> md4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(md1 <=> md5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(md1 <=> md6));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(md1 <=> md7));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(md1 <=> md8));
#endif
	}

	// month_day_last
	{
		HAMON_CXX11_CONSTEXPR chrono::month_day_last md{chrono::month{3}};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, md.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(md.ok());
	}

	// compare
	{
		HAMON_CXX11_CONSTEXPR chrono::month_day_last md1{chrono::month{3}};
		HAMON_CXX11_CONSTEXPR chrono::month_day_last md2{chrono::month{3}};
		HAMON_CXX11_CONSTEXPR chrono::month_day_last md3{chrono::month{4}};
		HAMON_CXX11_CONSTEXPR chrono::month_day_last md4{chrono::month{2}};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 == md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 == md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 == md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 == md4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 != md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 != md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 != md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 != md4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <  md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <  md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <  md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <  md4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >  md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >  md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >  md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >  md4);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <= md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <= md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 <= md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 <= md4);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >= md1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >= md2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(md1 >= md3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (md1 >= md4);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(md1 <=> md1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(md1 <=> md2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(md1 <=> md3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(md1 <=> md4));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(md1 <=> md1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(md1 <=> md2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(md1 <=> md3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(md1 <=> md4));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(md1 <=> md1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(md1 <=> md2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(md1 <=> md3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(md1 <=> md4));
#endif
	}

	// Conventional syntax operators

	// month / day
	{
		HAMON_CXX11_CONSTEXPR auto md = chrono::March/chrono::day{1};
		static_assert(hamon::is_same<decltype(md), chrono::month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, md.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{1}, md.day());
	}
	// month / int
	{
		HAMON_CXX11_CONSTEXPR auto md = chrono::March/2;
		static_assert(hamon::is_same<decltype(md), chrono::month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, md.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{2}, md.day());
	}
	// int / day
	{
		HAMON_CXX11_CONSTEXPR auto md = 4/chrono::day{1};
		static_assert(hamon::is_same<decltype(md), chrono::month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{4}, md.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{1}, md.day());
	}
	// day / month
	{
		HAMON_CXX11_CONSTEXPR auto md = chrono::day{3}/chrono::March;
		static_assert(hamon::is_same<decltype(md), chrono::month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, md.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{3}, md.day());
	}
	// day / int
	{
		HAMON_CXX11_CONSTEXPR auto md = chrono::day{4}/5;
		static_assert(hamon::is_same<decltype(md), chrono::month_day const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{5}, md.month());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::day{4}, md.day());
	}
	// month / last_spec
	{
		HAMON_CXX11_CONSTEXPR auto md = chrono::March/chrono::last;
		static_assert(hamon::is_same<decltype(md), chrono::month_day_last const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{3}, md.month());
	}
	// int / last_spec
	{
		HAMON_CXX11_CONSTEXPR auto md = 4/chrono::last;
		static_assert(hamon::is_same<decltype(md), chrono::month_day_last const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{4}, md.month());
	}
	// last_spec / month
	{
		HAMON_CXX11_CONSTEXPR auto md = chrono::last/chrono::January;
		static_assert(hamon::is_same<decltype(md), chrono::month_day_last const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{1}, md.month());
	}
	// last_spec / int
	{
		HAMON_CXX11_CONSTEXPR auto md = chrono::last/10;
		static_assert(hamon::is_same<decltype(md), chrono::month_day_last const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(chrono::month{10}, md.month());
	}
}

}	// namespace month_day_test

}	// namespace hamon_chrono_test
