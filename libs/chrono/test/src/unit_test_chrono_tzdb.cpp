/**
 *	@file	unit_test_chrono_tzdb.cpp
 *
 *	@brief	tzdb のテスト
 */

#include <hamon/chrono/tzdb.hpp>
#include <hamon/chrono/time_zone.hpp>
#include <hamon/chrono/time_zone_link.hpp>
#include <hamon/chrono/leap_second.hpp>
#include <hamon/chrono/get_tzdb.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/ranges.hpp>
#include <hamon/stdexcept/runtime_error.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace tzdb_test
{

namespace leap_seconds_test
{

static void test()
{
	using namespace hamon::literals::chrono_literals;

	using P = hamon::pair<hamon::chrono::sys_seconds, hamon::chrono::seconds>;
	static const P leap_seconds[] =
	{
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1972_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1973_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1974_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1975_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1976_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1977_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1978_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1979_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1980_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1981_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1982_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1983_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1985_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1988_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1990_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1991_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1992_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1993_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1994_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1996_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1997_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{1999_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{2006_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{2009_y / hamon::chrono::January / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{2012_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{2015_y / hamon::chrono::July    / 1}}, 1_s),
		hamon::make_pair(hamon::chrono::sys_seconds{hamon::chrono::sys_days{2017_y / hamon::chrono::January / 1}}, 1_s),
	};

	const hamon::chrono::tzdb& tzdb = hamon::chrono::get_tzdb();

	EXPECT_TRUE(tzdb.leap_seconds.size() >= hamon::ranges::size(leap_seconds));
	EXPECT_TRUE((hamon::ranges::equal(
		leap_seconds,
		tzdb.leap_seconds | hamon::ranges::views::take((long)hamon::ranges::size(leap_seconds)),
		[](P const& lhs, hamon::chrono::leap_second const& rhs)
		{ return lhs.first == rhs.date() && lhs.second == rhs.value(); })));
}

}	// namespace leap_seconds_test

namespace locate_zone_test
{

static void test_zone(hamon::string_view zone)
{
	const hamon::chrono::time_zone* tz = hamon::chrono::get_tzdb().locate_zone(zone);
	EXPECT_TRUE(tz);
	EXPECT_TRUE(tz->name() == zone);
}

static void test_link(hamon::string_view link, hamon::string_view zone)
{
	const hamon::chrono::time_zone* tz = hamon::chrono::get_tzdb().locate_zone(link);
	EXPECT_TRUE(tz);
	EXPECT_TRUE(tz->name() == zone);
}

static void test_exception()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	EXPECT_THROW(hamon::chrono::get_tzdb().locate_zone("This is not a time zone"), hamon::runtime_error);
#endif
}

static void test()
{
	const hamon::chrono::tzdb& db = hamon::chrono::get_tzdb();
	for (const auto& zone : db.zones)
	{
		test_zone(zone.name());
	}

	for (const auto& link : db.links)
	{
		test_link(link.name(), link.target());
	}

	test_exception();
}

}	// namespace locate_zone_test

GTEST_TEST(ChronoTest, TzdbTest)
{
	{
		hamon::chrono::tzdb tzdb;
		static_assert(hamon::is_same<decltype(tzdb.version),      hamon::string>::value, "");
		static_assert(hamon::is_same<decltype(tzdb.zones),        hamon::vector<hamon::chrono::time_zone>>::value, "");
		static_assert(hamon::is_same<decltype(tzdb.links),        hamon::vector<hamon::chrono::time_zone_link>>::value, "");
		static_assert(hamon::is_same<decltype(tzdb.leap_seconds), hamon::vector<hamon::chrono::leap_second>>::value, "");
	}

	leap_seconds_test::test();
	locate_zone_test::test();
//	current_zone_test::test();
}

}	// namespace tzdb_test

}	// namespace hamon_chrono_test
