/**
 *	@file	unit_test_chrono_year.cpp
 *
 *	@brief	year のテスト
 */

#include <hamon/chrono/year.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/compare.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace year_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::chrono::year y{0};
	VERIFY(int{y} == 0);
	VERIFY(y.ok());

	{
		auto& t = ++y;
		VERIFY(&t == &y);
		VERIFY(int{y} == 1);
		VERIFY(y.ok());
	}
	{
		auto t = y++;
		VERIFY(&t != &y);
		VERIFY(int{t} == 1);
		VERIFY(int{y} == 2);
		VERIFY(y.ok());
	}
	{
		auto& t = --y;
		VERIFY(&t == &y);
		VERIFY(int{y} == 1);
		VERIFY(y.ok());
	}
	{
		auto t = y--;
		VERIFY(&t != &y);
		VERIFY(int{t} == 1);
		VERIFY(int{y} == 0);
		VERIFY(y.ok());
	}
	{
		auto& t = y += hamon::chrono::years{3};
		VERIFY(&t == &y);
		VERIFY(int{y} == 3);
		VERIFY(y.ok());
	}
	{
		auto& t = y -= hamon::chrono::years{5};
		VERIFY(&t == &y);
		VERIFY(int{y} == -2);
		VERIFY(y.ok());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ChronoTest, YearTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

	{
		HAMON_CXX11_CONSTEXPR hamon::chrono::year y{12};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, int{y});
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, int{+y});
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-12, int{-y});
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(y.ok());
	}

	// ok
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::year{-32768}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{-32767}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{ 0}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{ 1}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{12}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{13}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{32767}.ok());

	// is_leap
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{ 0}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::year{ 1}.is_leap());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{2004}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{2008}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{2012}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{2016}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{2020}.is_leap());

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{1600}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::year{1700}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::year{1800}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::year{1900}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{2000}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::year{2100}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::year{2200}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::year{2300}.is_leap());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::year{2400}.is_leap());

	// min, max
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 32767, int{hamon::chrono::year::max()});
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-32767, int{hamon::chrono::year::min()});

	// compare
	{
		HAMON_CXX11_CONSTEXPR hamon::chrono::year y1{3};
		HAMON_CXX11_CONSTEXPR hamon::chrono::year y2{3};
		HAMON_CXX11_CONSTEXPR hamon::chrono::year y3{4};
		HAMON_CXX11_CONSTEXPR hamon::chrono::year y4{2};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 == y1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 == y2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 == y3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 == y4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 != y1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 != y2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 != y3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 != y4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 <  y1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 <  y2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 <  y3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 <  y4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 >  y1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 >  y2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 >  y3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 >  y4);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 <= y1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 <= y2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 <= y3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 <= y4);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 >= y1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 >= y2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(y1 >= y3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (y1 >= y4);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(y1 <=> y1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(y1 <=> y2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(y1 <=> y3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(y1 <=> y4));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(y1 <=> y1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(y1 <=> y2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(y1 <=> y3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(y1 <=> y4));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(y1 <=> y1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(y1 <=> y2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(y1 <=> y3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(y1 <=> y4));
#endif
	}

	// year + years
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::year{0}    + hamon::chrono::years{3}  == hamon::chrono::year{3});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::year{2025} + hamon::chrono::years{16} == hamon::chrono::year{2041});

	// years + year
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::years{2} + hamon::chrono::year{4}    == hamon::chrono::year{6});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::years{3} + hamon::chrono::year{2024} == hamon::chrono::year{2027});

	// year - years
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::year{5}    - hamon::chrono::years{1}    == hamon::chrono::year{4});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::year{2025} - hamon::chrono::years{16}   == hamon::chrono::year{2009});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::year{2025} - hamon::chrono::years{4000} == hamon::chrono::year{-1975});

	// year - year
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::year{5}    - hamon::chrono::year{1}    == hamon::chrono::years{4});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::year{2025} - hamon::chrono::year{2020} == hamon::chrono::years{5});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::year{2014} - hamon::chrono::year{2020} == hamon::chrono::years{-6});

	// literals
	{
		using namespace hamon::literals::chrono_literals;
		HAMON_CXX11_CONSTEXPR auto y = 2020_y;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(y == hamon::chrono::year{2020});
	}
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR auto y = 2021_y;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(y == hamon::chrono::year{2021});
	}
	{
		using namespace hamon::literals;
		HAMON_CXX11_CONSTEXPR auto y = 2022_y;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(y == hamon::chrono::year{2022});
	}
	{
		using namespace hamon::chrono;
		HAMON_CXX11_CONSTEXPR auto y = 2023_y;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(y == hamon::chrono::year{2023});
	}
	{
		using namespace hamon;
		HAMON_CXX11_CONSTEXPR auto y = 2024_y;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(y == hamon::chrono::year{2024});
	}
}

}	// namespace year_test

}	// namespace hamon_chrono_test
