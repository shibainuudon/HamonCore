/**
 *	@file	unit_test_chrono_time_zone_link.cpp
 *
 *	@brief	time_zone_link のテスト
 */

#include <hamon/chrono/time_zone_link.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

static_assert(!hamon::is_copy_constructible<hamon::chrono::time_zone_link>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::chrono::time_zone_link>::value, "");
static_assert( hamon::is_move_constructible<hamon::chrono::time_zone_link>::value, "");
static_assert( hamon::is_move_assignable<hamon::chrono::time_zone_link>::value, "");

GTEST_TEST(ChronoTest, TimeZoneLinkTest)
{
}

}	// namespace hamon_chrono_test
