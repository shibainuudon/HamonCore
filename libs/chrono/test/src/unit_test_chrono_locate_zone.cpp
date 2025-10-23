/**
 *	@file	unit_test_chrono_locate_zone.cpp
 *
 *	@brief	locate_zone のテスト
 */

#include <hamon/chrono/locate_zone.hpp>
#include <hamon/chrono/time_zone.hpp>
#include <hamon/chrono/get_tzdb.hpp>
#include <hamon/stdexcept/runtime_error.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace locate_zone_test
{

static void test_zone(hamon::string_view zone)
{
	const hamon::chrono::time_zone* tz = hamon::chrono::locate_zone(zone);
	EXPECT_TRUE(tz);
	EXPECT_TRUE(tz->name() == zone);
}

static void test_link(hamon::string_view link, hamon::string_view zone)
{
	const hamon::chrono::time_zone* tz = hamon::chrono::locate_zone(link);
	EXPECT_TRUE(tz);
	EXPECT_TRUE(tz->name() == zone);
}

static void test_exception()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	EXPECT_THROW(hamon::chrono::locate_zone("This is not a time zone"), hamon::runtime_error);
#endif
}

GTEST_TEST(ChronoTest, LocateZoneTest)
{
	static_assert(hamon::is_same<decltype(hamon::chrono::locate_zone(hamon::string_view{})), hamon::chrono::time_zone const*>::value, "");
	static_assert(!noexcept(hamon::chrono::locate_zone(hamon::string_view{})), "");

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

}	// namespace hamon_chrono_test
