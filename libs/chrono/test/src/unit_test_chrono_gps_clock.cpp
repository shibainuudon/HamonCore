/**
 *	@file	unit_test_chrono_gps_clock.cpp
 *
 *	@brief	gps_clock のテスト
 */

#include <hamon/chrono/gps_clock.hpp>
#include <hamon/chrono/gps_time.hpp>
#include <hamon/chrono/gps_seconds.hpp>
#include <hamon/chrono/utc_time.hpp>
#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace gps_clock_test
{

void to_utc_test()
{
	namespace chrono = hamon::chrono;
	using namespace hamon::chrono_literals;

	static_assert(hamon::is_same<chrono::utc_time<chrono::nanoseconds>,
		decltype(chrono::gps_clock::to_utc(chrono::gps_time<chrono::nanoseconds>{0_ns}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::microseconds>,
		decltype(chrono::gps_clock::to_utc(chrono::gps_time<chrono::microseconds>{0_us}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::milliseconds>,
		decltype(chrono::gps_clock::to_utc(chrono::gps_time<chrono::milliseconds>{0_ms}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::gps_clock::to_utc(chrono::gps_time<chrono::seconds>{chrono::seconds{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::gps_clock::to_utc(chrono::gps_time<chrono::minutes>{chrono::minutes{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::gps_clock::to_utc(chrono::gps_time<chrono::hours>{chrono::hours{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::gps_clock::to_utc(chrono::gps_time<chrono::days>{chrono::days{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::gps_clock::to_utc(chrono::gps_time<chrono::weeks>{chrono::weeks{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::gps_clock::to_utc(chrono::gps_time<chrono::months>{chrono::months{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::gps_clock::to_utc(chrono::gps_time<chrono::years>{chrono::years{ 0 }}))>::value, "");

	static_assert(noexcept(chrono::gps_clock::to_utc(chrono::gps_seconds{0_s})), "");

	EXPECT_TRUE(chrono::gps_clock::to_utc(chrono::gps_seconds{ 0_s }) ==
		chrono::utc_clock::from_sys(chrono::sys_days{ chrono::January / 6 / 1980 }));

	// "sys" is the time of the transition to the next leap second.
	// "elapsed" is the number of leap seconds before the transition.
	auto test_transition = [](chrono::sys_days sys, chrono::seconds elapsed)
	{
		constexpr auto unix_to_gps_epoch_offset =
			chrono::sys_days{ chrono::January / 1 / 1970 } - chrono::sys_days{ chrono::January / 6 / 1980 };
		chrono::gps_seconds gps{ sys.time_since_epoch() + unix_to_gps_epoch_offset + elapsed };

		EXPECT_TRUE(chrono::gps_clock::to_utc(gps - 1_ns)       == chrono::utc_clock::from_sys(sys - 1_ns));
		EXPECT_TRUE(chrono::gps_clock::to_utc(gps + 1_s)        == chrono::utc_clock::from_sys(sys));
		EXPECT_TRUE(chrono::gps_clock::to_utc(gps + 1_s + 1_ns) == chrono::utc_clock::from_sys(sys + 1_ns));
	};

	// Transitions from the start of UTC.
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1972 }, -9_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1973 }, -8_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1974 }, -7_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1975 }, -6_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1976 }, -5_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1977 }, -4_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1978 }, -3_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1979 }, -2_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1980 }, -1_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1981 },  0_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1982 },  1_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1983 },  2_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1985 },  3_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1988 },  4_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1990 },  5_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1991 },  6_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1992 },  7_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1993 },  8_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1994 },  9_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1996 }, 10_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1997 }, 11_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1999 }, 12_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 2006 }, 13_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 2009 }, 14_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 2012 }, 15_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 2015 }, 16_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 2017 }, 17_s);
}

void from_utc_test()
{
	namespace chrono = hamon::chrono;
	using namespace hamon::chrono_literals;

	static_assert(hamon::is_same<chrono::gps_time<chrono::nanoseconds>,
		decltype(chrono::gps_clock::from_utc(chrono::utc_time<chrono::nanoseconds>{0_ns}))>::value, "");
	static_assert(hamon::is_same<chrono::gps_time<chrono::microseconds>,
		decltype(chrono::gps_clock::from_utc(chrono::utc_time<chrono::microseconds>{0_us}))>::value, "");
	static_assert(hamon::is_same<chrono::gps_time<chrono::milliseconds>,
		decltype(chrono::gps_clock::from_utc(chrono::utc_time<chrono::milliseconds>{0_ms}))>::value, "");
	static_assert(hamon::is_same<chrono::gps_time<chrono::seconds>,
		decltype(chrono::gps_clock::from_utc(chrono::utc_time<chrono::seconds>{chrono::seconds{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::gps_time<chrono::seconds>,
		decltype(chrono::gps_clock::from_utc(chrono::utc_time<chrono::minutes>{chrono::minutes{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::gps_time<chrono::seconds>,
		decltype(chrono::gps_clock::from_utc(chrono::utc_time<chrono::hours>{chrono::hours{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::gps_time<chrono::seconds>,
		decltype(chrono::gps_clock::from_utc(chrono::utc_time<chrono::days>{chrono::days{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::gps_time<chrono::seconds>,
		decltype(chrono::gps_clock::from_utc(chrono::utc_time<chrono::weeks>{chrono::weeks{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::gps_time<chrono::seconds>,
		decltype(chrono::gps_clock::from_utc(chrono::utc_time<chrono::months>{chrono::months{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::gps_time<chrono::seconds>,
		decltype(chrono::gps_clock::from_utc(chrono::utc_time<chrono::years>{chrono::years{ 0 }}))>::value, "");

	static_assert(noexcept(chrono::gps_clock::from_utc(chrono::utc_seconds{0_s})), "");

	// [time.clock.gps.overview]/1
	//   The clock gps_clock measures seconds since the first Sunday of January,
	//   1980 00:00:00 UTC.
	// The first Sunday is 1980-1-6 (so January sixth)
	// ... 1980-01-06 00:00:00 GPS is equivalent to 1980-01-06 00:00:00 UTC
	EXPECT_TRUE(chrono::gps_clock::from_utc(chrono::utc_clock::from_sys(chrono::sys_days{ chrono::January / 6 / 1980 })) ==
		chrono::gps_seconds{ 0_s });

	// "sys" is the time of the transition to the next leap second.
	// "elapsed" is the number of leap seconds before the transition.
	auto test_transition = [](chrono::sys_days sys, chrono::seconds elapsed)
	{
		constexpr auto unix_to_gps_epoch_offset =
			chrono::sys_days{ chrono::January / 1 / 1970 } - chrono::sys_days{ chrono::January / 6 / 1980 };
		chrono::gps_seconds gps{ sys.time_since_epoch() + unix_to_gps_epoch_offset + elapsed };

		EXPECT_TRUE(chrono::gps_clock::from_utc(chrono::utc_clock::from_sys(sys - 1_ns)) == gps - 1_ns);
		EXPECT_TRUE(chrono::gps_clock::from_utc(chrono::utc_clock::from_sys(sys))        == gps + 1_s);
		EXPECT_TRUE(chrono::gps_clock::from_utc(chrono::utc_clock::from_sys(sys) + 1_ns) == gps + 1_s + 1_ns);
	};

	// Transitions from the start of UTC.
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1972 }, -9_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1973 }, -8_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1974 }, -7_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1975 }, -6_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1976 }, -5_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1977 }, -4_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1978 }, -3_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1979 }, -2_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1980 }, -1_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1981 },  0_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1982 },  1_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1983 },  2_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1985 },  3_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1988 },  4_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1990 },  5_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1991 },  6_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1992 },  7_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1993 },  8_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1994 },  9_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1996 }, 10_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 1997 }, 11_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 1999 }, 12_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 2006 }, 13_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 2009 }, 14_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 2012 }, 15_s);
	test_transition(chrono::sys_days{ chrono::July    / 1 / 2015 }, 16_s);
	test_transition(chrono::sys_days{ chrono::January / 1 / 2017 }, 17_s);
}

GTEST_TEST(ChronoTest, GpsClockTest)
{
	using Clock = hamon::chrono::gps_clock;
	using rep        = typename Clock::rep;
	using period     = typename Clock::period;
	using duration   = typename Clock::duration;
	using time_point = typename Clock::time_point;

	static_assert(hamon::is_same<rep, hamon::chrono::utc_clock::rep>::value, "");
	static_assert(hamon::is_arithmetic<rep>::value, "");
	static_assert(hamon::is_signed<rep>::value, "");

	static_assert(hamon::is_same<period, hamon::chrono::utc_clock::period>::value, "");
	static_assert(hamon::is_same<period, hamon::ratio<period::num, period::den>>::value, "");

	static_assert(hamon::is_same<duration, hamon::chrono::duration<rep, period>>::value, "");
	static_assert(hamon::is_same<time_point, hamon::chrono::time_point<hamon::chrono::gps_clock>>::value, "");
	static_assert(Clock::is_steady == false, "");

	// typedefs
	static_assert(hamon::is_same<hamon::chrono::gps_time<int>,  hamon::chrono::time_point<hamon::chrono::gps_clock, int>>::value, "");
	static_assert(hamon::is_same<hamon::chrono::gps_time<long>, hamon::chrono::time_point<hamon::chrono::gps_clock, long>>::value, "");
	static_assert(hamon::is_same<hamon::chrono::gps_seconds,    hamon::chrono::gps_time<hamon::chrono::seconds>>::value, "");

	static_assert(!noexcept(Clock::now()), "");
	static_assert(hamon::is_same<time_point, decltype(Clock::now())>::value, "");
	{
		auto t = Clock::now();
		EXPECT_TRUE(t >= time_point::min());
		EXPECT_TRUE(t <= time_point::max());
	}

	to_utc_test();
	from_utc_test();
}

}	// namespace gps_clock_test

}	// namespace hamon_chrono_test
