/**
 *	@file	unit_test_chrono_leap_second.cpp
 *
 *	@brief	leap_second のテスト
 */

#include <hamon/chrono/leap_second.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

static_assert( hamon::is_copy_constructible<hamon::chrono::leap_second>::value, "");
static_assert( hamon::is_copy_assignable<hamon::chrono::leap_second>::value, "");
static_assert( hamon::is_move_constructible<hamon::chrono::leap_second>::value, "");
static_assert( hamon::is_move_assignable<hamon::chrono::leap_second>::value, "");

GTEST_TEST(ChronoTest, LeapSecondTest)
{
}

}	// namespace hamon_chrono_test
