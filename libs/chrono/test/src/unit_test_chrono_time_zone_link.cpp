/**
 *	@file	unit_test_chrono_time_zone_link.cpp
 *
 *	@brief	time_zone_link のテスト
 */

#include <hamon/chrono/time_zone_link.hpp>
#include <hamon/chrono/get_tzdb.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace time_zone_link_test
{

static_assert(!hamon::is_copy_constructible<hamon::chrono::time_zone_link>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::chrono::time_zone_link>::value, "");
static_assert( hamon::is_move_constructible<hamon::chrono::time_zone_link>::value, "");
static_assert( hamon::is_move_assignable<hamon::chrono::time_zone_link>::value, "");

inline void name_test()
{
	const hamon::chrono::tzdb& tzdb = hamon::chrono::get_tzdb();
	const hamon::chrono::time_zone_link& link = tzdb.links[0];

	static_assert(hamon::is_same<decltype(link.name()), hamon::string_view>::value, "");
	static_assert(noexcept(link.name()), "");

	EXPECT_TRUE(link.name() != tzdb.links[1].name());
}

inline void target_test()
{
	const hamon::chrono::tzdb& tzdb = hamon::chrono::get_tzdb();
	const hamon::chrono::time_zone_link& link = tzdb.links[0];

	static_assert(hamon::is_same<decltype(link.target()), hamon::string_view>::value, "");
	static_assert(noexcept(link.target()), "");
}

inline void comparison_test()
{
	const hamon::chrono::tzdb& tzdb = hamon::chrono::get_tzdb();
	const hamon::chrono::time_zone_link& a = tzdb.links[0];
	const hamon::chrono::time_zone_link& b = tzdb.links[1];
	const hamon::chrono::time_zone_link& c = tzdb.links[2];

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

GTEST_TEST(ChronoTest, TimeZoneLinkTest)
{
	name_test();
	target_test();
	comparison_test();
}

}	// namespace time_zone_link_test

}	// namespace hamon_chrono_test
