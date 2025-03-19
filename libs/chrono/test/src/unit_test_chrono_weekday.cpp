/**
 *	@file	unit_test_chrono_weekday.cpp
 *
 *	@brief	weekday のテスト
 */

#include <hamon/chrono/weekday.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/compare.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace weekday_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test()
{
	auto wd = hamon::chrono::Sunday;
	VERIFY(wd.c_encoding() == 0);
	VERIFY(wd.ok());

	{
		auto& t = ++wd;
		VERIFY(&t == &wd);
		VERIFY(wd.c_encoding() == 1);
		VERIFY(wd.ok());
	}
	{
		auto t = wd++;
		VERIFY(&t != &wd);
		VERIFY(t.c_encoding() == 1);
		VERIFY(wd.c_encoding() == 2);
		VERIFY(wd.ok());
	}
	{
		auto& t = --wd;
		VERIFY(&t == &wd);
		VERIFY(wd.c_encoding() == 1);
		VERIFY(wd.ok());
	}
	{
		auto t = wd--;
		VERIFY(&t != &wd);
		VERIFY(t.c_encoding() == 1);
		VERIFY(wd.c_encoding() == 0);
		VERIFY(wd.ok());
	}
	{
		auto& t = wd += hamon::chrono::days{3};
		VERIFY(&t == &wd);
		VERIFY(wd.c_encoding() == 3);
		VERIFY(wd.ok());
	}
	{
		auto& t = wd += hamon::chrono::days{5};
		VERIFY(&t == &wd);
		VERIFY(wd.c_encoding() == 1);
		VERIFY(wd.ok());
	}
	{
		auto& t = wd -= hamon::chrono::days{2};
		VERIFY(&t == &wd);
		VERIFY(wd.c_encoding() == 6);
		VERIFY(wd.ok());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ChronoTest, WeekdayTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

	{
		// TODO
		// sys_days からのコンストラクタ
		// weekday wd{sys_days{1970y/January/1}};
	}
	{
		// TODO
		// local_days からのコンストラクタ
		// weekday wd{local_days{1970y/January/1}};
	}

	// c_encoding
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, hamon::chrono::Sunday.c_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, hamon::chrono::Monday.c_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, hamon::chrono::Tuesday.c_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, hamon::chrono::Wednesday.c_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, hamon::chrono::Thursday.c_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, hamon::chrono::Friday.c_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6u, hamon::chrono::Saturday.c_encoding());

	// iso_encoding
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, hamon::chrono::Sunday.iso_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, hamon::chrono::Monday.iso_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, hamon::chrono::Tuesday.iso_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, hamon::chrono::Wednesday.iso_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, hamon::chrono::Thursday.iso_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, hamon::chrono::Friday.iso_encoding());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6u, hamon::chrono::Saturday.iso_encoding());

	// ok
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::weekday{6}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::chrono::weekday{7}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::weekday{8}.ok());
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::chrono::weekday{99}.ok());

	// compare
	{
		HAMON_CXX11_CONSTEXPR hamon::chrono::weekday wd1{3};
		HAMON_CXX11_CONSTEXPR hamon::chrono::weekday wd2{3};
		HAMON_CXX11_CONSTEXPR hamon::chrono::weekday wd3{4};
		HAMON_CXX11_CONSTEXPR hamon::chrono::weekday wd4{2};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wd1 == wd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wd1 == wd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wd1 == wd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wd1 == wd4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wd1 != wd1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wd1 != wd2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wd1 != wd3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wd1 != wd4);
	}

	// weekday + days
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::Sunday + hamon::chrono::days{3} == hamon::chrono::Wednesday);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::Saturday + hamon::chrono::days{3} == hamon::chrono::Tuesday);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::Saturday + hamon::chrono::days{10} == hamon::chrono::Tuesday);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::Monday + hamon::chrono::days{6} == hamon::chrono::Sunday);

	// days + weekday
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::days{3} + hamon::chrono::Sunday == hamon::chrono::Wednesday);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::days{3} + hamon::chrono::Saturday == hamon::chrono::Tuesday);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::days{17} + hamon::chrono::Sunday == hamon::chrono::Wednesday);

	// weekday - days
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::Sunday - hamon::chrono::days{3} == hamon::chrono::Thursday);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::Tuesday - hamon::chrono::days{3} == hamon::chrono::Saturday);

	// weekday - weekday
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::Sunday - hamon::chrono::Wednesday == hamon::chrono::days{4});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::Tuesday - hamon::chrono::Saturday == hamon::chrono::days{3});
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::chrono::Sunday - hamon::chrono::Monday == hamon::chrono::days{6});

	// weekday_indexed
	{
		HAMON_CXX11_CONSTEXPR auto wi1 = hamon::chrono::Sunday[1];
		HAMON_CXX11_CONSTEXPR auto wi2 = hamon::chrono::Sunday[1];
		HAMON_CXX11_CONSTEXPR auto wi3 = hamon::chrono::Sunday[2];
		HAMON_CXX11_CONSTEXPR auto wi4 = hamon::chrono::Monday[1];
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::Sunday, wi1.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::Sunday, wi2.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::Sunday, wi3.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::Monday, wi4.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, wi1.index());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, wi2.index());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, wi3.index());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, wi4.index());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(wi1.ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(wi2.ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(wi3.ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(wi4.ok());

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wi1 == wi1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wi1 == wi2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wi1 == wi3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wi1 == wi4);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wi1 != wi1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wi1 != wi2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wi1 != wi3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wi1 != wi4);
	}

	// weekday_last
	{
		HAMON_CXX11_CONSTEXPR auto wl1 = hamon::chrono::Sunday[hamon::chrono::last];
		HAMON_CXX11_CONSTEXPR auto wl2 = hamon::chrono::Sunday[hamon::chrono::last];
		HAMON_CXX11_CONSTEXPR auto wl3 = hamon::chrono::Monday[hamon::chrono::last];
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::Sunday, wl1.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::Sunday, wl2.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::Monday, wl3.weekday());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(wl1.ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(wl2.ok());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(wl3.ok());

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wl1 == wl1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wl1 == wl2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wl1 == wl3);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wl1 != wl1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(wl1 != wl2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (wl1 != wl3);
	}
}

}	// namespace weekday_test

}	// namespace hamon_chrono_test
