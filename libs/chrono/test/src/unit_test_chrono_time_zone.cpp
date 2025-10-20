/**
 *	@file	unit_test_chrono_time_zone.cpp
 *
 *	@brief	time_zone のテスト
 */

#include <hamon/chrono/time_zone.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

static_assert(!hamon::is_copy_constructible<hamon::chrono::time_zone>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::chrono::time_zone>::value, "");
static_assert( hamon::is_move_constructible<hamon::chrono::time_zone>::value, "");
static_assert( hamon::is_move_assignable<hamon::chrono::time_zone>::value, "");

GTEST_TEST(ChronoTest, TimeZoneTest)
{
}

}	// namespace hamon_chrono_test
