/**
 *	@file	unit_test_chrono_day.cpp
 *
 *	@brief	day のテスト
 */

#include <hamon/chrono/day.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/compare.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace day_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::chrono::day d{0};
	VERIFY(unsigned{d} == 0);
	VERIFY(!d.ok());

	{
		auto& t = ++d;
		VERIFY(&t == &d);
		VERIFY(unsigned{d} == 1);
		VERIFY(d.ok());
	}
	{
		auto t = d++;
		VERIFY(&t != &d);
		VERIFY(unsigned{t} == 1);
		VERIFY(unsigned{d} == 2);
		VERIFY(d.ok());
	}
	{
		auto& t = --d;
		VERIFY(&t == &d);
		VERIFY(unsigned{d} == 1);
		VERIFY(d.ok());
	}
	{
		auto t = d--;
		VERIFY(&t != &d);
		VERIFY(unsigned{t} == 1);
		VERIFY(unsigned{d} == 0);
		VERIFY(!d.ok());
	}
	{
		auto& t = d += hamon::chrono::days{3};
		VERIFY(&t == &d);
		VERIFY(unsigned{d} == 3);
		VERIFY(d.ok());
	}
	{
		auto& t = d -= hamon::chrono::days{2};
		VERIFY(&t == &d);
		VERIFY(unsigned{d} == 1);
		VERIFY(d.ok());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ChronoTest, DayTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

	{
		HAMON_CXX11_CONSTEXPR hamon::chrono::day d{12};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12u, unsigned{d});
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(d.ok());
	}

	// ok
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::day{ 0}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::day{ 1}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::day{30}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::day{31}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::day{32}.ok());

	// compare
	{
		HAMON_CXX11_CONSTEXPR hamon::chrono::day d1{3};
		HAMON_CXX11_CONSTEXPR hamon::chrono::day d2{3};
		HAMON_CXX11_CONSTEXPR hamon::chrono::day d3{4};
		HAMON_CXX11_CONSTEXPR hamon::chrono::day d4{2};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 == d1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 == d2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 == d3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 == d4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 != d1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 != d2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 != d3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 != d4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 <  d1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 <  d2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 <  d3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 <  d4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 >  d1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 >  d2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 >  d3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 >  d4);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 <= d1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 <= d2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 <= d3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 <= d4);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 >= d1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 >= d2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(d1 >= d3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (d1 >= d4);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(d1 <=> d1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_eq(d1 <=> d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(d1 <=> d3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_eq(d1 <=> d4));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(d1 <=> d1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(d1 <=> d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_lt(d1 <=> d3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_lt(d1 <=> d4));

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(d1 <=> d1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(d1 <=> d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_gt(d1 <=> d3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_gt(d1 <=> d4));
#endif
	}

	// day + days
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::day{0} + hamon::chrono::days{3} == hamon::chrono::day{3});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::day{1} + hamon::chrono::days{5} == hamon::chrono::day{6});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::day{5} + hamon::chrono::days{30} == hamon::chrono::day{35});

	// days + day
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::days{2} + hamon::chrono::day{4} == hamon::chrono::day{6});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::days{5} + hamon::chrono::day{4} == hamon::chrono::day{9});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::days{25} + hamon::chrono::day{9} == hamon::chrono::day{34});

	// day - days
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::day{5} - hamon::chrono::days{1} == hamon::chrono::day{4});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::day{31} - hamon::chrono::days{2} == hamon::chrono::day{29});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::day{1} - hamon::chrono::days{3} == hamon::chrono::day{unsigned(-2)});

	// day - day
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::day{5} - hamon::chrono::day{1} == hamon::chrono::days{4});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::day{5} - hamon::chrono::day{10} == hamon::chrono::days{-5});

	// literals
	{
		using namespace hamon::literals::chrono_literals;
		HAMON_CXX11_CONSTEXPR auto d = 3_d;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(d == hamon::chrono::day{3});
	}
	{
		using namespace hamon::chrono_literals;
		HAMON_CXX11_CONSTEXPR auto d = 4_d;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(d == hamon::chrono::day{4});
	}
	{
		using namespace hamon::literals;
		HAMON_CXX11_CONSTEXPR auto d = 5_d;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(d == hamon::chrono::day{5});
	}
	{
		using namespace hamon::chrono;
		HAMON_CXX11_CONSTEXPR auto d = 6_d;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(d == hamon::chrono::day{6});
	}
	{
		using namespace hamon;
		HAMON_CXX11_CONSTEXPR auto d = 7_d;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(d == hamon::chrono::day{7});
	}
}

}	// namespace day_test

}	// namespace hamon_chrono_test
