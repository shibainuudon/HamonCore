/**
 *	@file	unit_test_chrono_time_zone.cpp
 *
 *	@brief	time_zone のテスト
 */

#include <hamon/chrono/time_zone.hpp>
#include <hamon/chrono/get_tzdb.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace time_zone_test
{

static_assert(!hamon::is_copy_constructible<hamon::chrono::time_zone>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::chrono::time_zone>::value, "");
static_assert( hamon::is_move_constructible<hamon::chrono::time_zone>::value, "");
static_assert( hamon::is_move_assignable<hamon::chrono::time_zone>::value, "");

inline void name_test()
{
	const hamon::chrono::tzdb& tzdb = hamon::chrono::get_tzdb();
	const hamon::chrono::time_zone& zone = tzdb.zones[0];

	static_assert(hamon::is_same<decltype(zone.name()), hamon::string_view>::value, "");
	static_assert(noexcept(zone.name()), "");

	EXPECT_TRUE(zone.name() != tzdb.zones[1].name());
}

inline void comparison_test()
{
	const hamon::chrono::tzdb& tzdb = hamon::chrono::get_tzdb();
	const hamon::chrono::time_zone& a = tzdb.zones[0];
	const hamon::chrono::time_zone& b = tzdb.zones[1];
	const hamon::chrono::time_zone& c = tzdb.zones[2];

	static_assert(hamon::is_same<decltype(a == a), bool>::value, "");
	static_assert(hamon::is_same<decltype(a != a), bool>::value, "");
	static_assert(hamon::is_same<decltype(a <  a), bool>::value, "");
	static_assert(hamon::is_same<decltype(a >  a), bool>::value, "");
	static_assert(hamon::is_same<decltype(a <= a), bool>::value, "");
	static_assert(hamon::is_same<decltype(a >= a), bool>::value, "");
	static_assert(noexcept(a == a), "");
	static_assert(noexcept(a != a), "");
	static_assert(noexcept(a <  a), "");
	static_assert(noexcept(a >  a), "");
	static_assert(noexcept(a <= a), "");
	static_assert(noexcept(a >= a), "");

	EXPECT_TRUE(!(b == a));
	EXPECT_TRUE( (b == b));
	EXPECT_TRUE(!(b == c));

	EXPECT_TRUE( (b != a));
	EXPECT_TRUE(!(b != b));
	EXPECT_TRUE( (b != c));

	EXPECT_TRUE(!(b <  a));
	EXPECT_TRUE(!(b <  b));
	EXPECT_TRUE( (b <  c));

	EXPECT_TRUE( (b >  a));
	EXPECT_TRUE(!(b >  b));
	EXPECT_TRUE(!(b >  c));

	EXPECT_TRUE(!(b <= a));
	EXPECT_TRUE( (b <= b));
	EXPECT_TRUE( (b <= c));

	EXPECT_TRUE( (b >= a));
	EXPECT_TRUE( (b >= b));
	EXPECT_TRUE(!(b >= c));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(hamon::is_same<decltype(a <=> a), hamon::strong_ordering>::value, "");
	static_assert(noexcept(a <=> a), "");

	EXPECT_TRUE(hamon::is_gt(b <=> a));
	EXPECT_TRUE(hamon::is_eq(b <=> b));
	EXPECT_TRUE(hamon::is_lt(b <=> c));
#endif
}

GTEST_TEST(ChronoTest, TimeZoneTest)
{
	name_test();
	comparison_test();
}

}	// namespace time_zone_test

}	// namespace hamon_chrono_test
