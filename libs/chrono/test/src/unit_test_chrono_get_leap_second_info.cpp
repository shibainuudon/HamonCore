/**
 *	@file	unit_test_chrono_get_leap_second_info.cpp
 *
 *	@brief	get_leap_second_info のテスト
 *
 *	template<class Duration>
 *	leap_second_info get_leap_second_info(const utc_time<Duration>& ut);
 */

#include <hamon/chrono/utc_clock.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace get_leap_second_info_test
{

template <typename Duration>
static void test_leap_second_info(
	hamon::chrono::time_point<hamon::chrono::utc_clock, Duration> time, bool is_leap_second, hamon::chrono::seconds elapsed)
{
	hamon::chrono::leap_second_info result = hamon::chrono::get_leap_second_info(time);
	EXPECT_TRUE(result.is_leap_second == is_leap_second);
	EXPECT_TRUE(result.elapsed == elapsed);
}

static hamon::chrono::utc_seconds get_utc_time(long long seconds_since_1900)
{
	// The file leap-seconds.list stores dates since 1 January 1900, 00:00:00, we want
	// seconds since 1 January 1970.
	constexpr auto offset =
		hamon::chrono::sys_days{ hamon::chrono::January / 1 / 1970 } - hamon::chrono::sys_days{ hamon::chrono::January / 1 / 1900 };
	return hamon::chrono::utc_seconds{ hamon::chrono::seconds{seconds_since_1900} - offset };
}

GTEST_TEST(ChronoTest, GetLeapSecondInfoTest)
{
	using namespace hamon::literals::chrono_literals;

	test_leap_second_info(hamon::chrono::utc_seconds::min(), false, 0_s);

	// Epoch transition no transitions.
	test_leap_second_info(hamon::chrono::utc_seconds{ -1_s }, false, 0_s);
	test_leap_second_info(hamon::chrono::utc_seconds{  0_s }, false, 0_s);
	test_leap_second_info(hamon::chrono::utc_seconds{  1_s }, false, 0_s);

	// Transitions from the start of UTC.
	auto test_transition = [](hamon::chrono::utc_seconds time, hamon::chrono::seconds elapsed, bool positive) {
		// Note at the time of writing all leap seconds are positive so the else
		// branch is never executed. The private test for this function tests
		// negative leap seconds and uses the else branch.

		if (positive)
		{
			// Every transition has the following tests
			// - 1ns before the start of the transition is_leap_second -> false, elapsed -> elapsed
			// -         at the start of the transition is_leap_second -> true,  elapsed -> elapsed + 1
			// - 1ns after  the start of the transition is_leap_second -> true,  elapsed -> elapsed + 1
			// - 1ns before the end   of the transition is_leap_second -> true,  elapsed -> elapsed + 1
			// -         at the end   of the transition is_leap_second -> false, elapsed -> elapsed + 1

			test_leap_second_info(time - 1_ns,       false, elapsed);
			test_leap_second_info(time,              true,  elapsed + 1_s);
			test_leap_second_info(time + 1_ns,       true,  elapsed + 1_s);
			test_leap_second_info(time + 1_s - 1_ns, true,  elapsed + 1_s);
			test_leap_second_info(time + 1_s,        false, elapsed + 1_s);
		}
		else
		{
			// Every transition has the following tests
			// - 1ns before the transition is_leap_second -> false, elapsed -> elapsed
			// -         at the transition is_leap_second -> false  elapsed -> elapsed - 1
			// - 1ns after  the transition is_leap_second -> false, elapsed -> elapsed - 1
			test_leap_second_info(time - 1_ns, false, elapsed);
			test_leap_second_info(time,        false, elapsed - 1_s);
			test_leap_second_info(time + 1_ns, false, elapsed - 1_s);
		}
	};

	// The timestamps are from leap-seconds.list in the IANA database.
	// Note the times stamps are timestamps without leap seconds so the number
	// here are incremented by x "leap seconds".
	test_transition(get_utc_time(2287785600 +  0),  0_s, true); // 1 Jul 1972
	test_transition(get_utc_time(2303683200 +  1),  1_s, true); // 1 Jan 1973
	test_transition(get_utc_time(2335219200 +  2),  2_s, true); // 1 Jan 1974
	test_transition(get_utc_time(2366755200 +  3),  3_s, true); // 1 Jan 1975
	test_transition(get_utc_time(2398291200 +  4),  4_s, true); // 1 Jan 1976
	test_transition(get_utc_time(2429913600 +  5),  5_s, true); // 1 Jan 1977
	test_transition(get_utc_time(2461449600 +  6),  6_s, true); // 1 Jan 1978
	test_transition(get_utc_time(2492985600 +  7),  7_s, true); // 1 Jan 1979
	test_transition(get_utc_time(2524521600 +  8),  8_s, true); // 1 Jan 1980
	test_transition(get_utc_time(2571782400 +  9),  9_s, true); // 1 Jul 1981
	test_transition(get_utc_time(2603318400 + 10), 10_s, true); // 1 Jul 1982
	test_transition(get_utc_time(2634854400 + 11), 11_s, true); // 1 Jul 1983
	test_transition(get_utc_time(2698012800 + 12), 12_s, true); // 1 Jul 1985
	test_transition(get_utc_time(2776982400 + 13), 13_s, true); // 1 Jan 1988
	test_transition(get_utc_time(2840140800 + 14), 14_s, true); // 1 Jan 1990
	test_transition(get_utc_time(2871676800 + 15), 15_s, true); // 1 Jan 1991
	test_transition(get_utc_time(2918937600 + 16), 16_s, true); // 1 Jul 1992
	test_transition(get_utc_time(2950473600 + 17), 17_s, true); // 1 Jul 1993
	test_transition(get_utc_time(2982009600 + 18), 18_s, true); // 1 Jul 1994
	test_transition(get_utc_time(3029443200 + 19), 19_s, true); // 1 Jan 1996
	test_transition(get_utc_time(3076704000 + 20), 20_s, true); // 1 Jul 1997
	test_transition(get_utc_time(3124137600 + 21), 21_s, true); // 1 Jan 1999
	test_transition(get_utc_time(3345062400 + 22), 22_s, true); // 1 Jan 2006
	test_transition(get_utc_time(3439756800 + 23), 23_s, true); // 1 Jan 2009
	test_transition(get_utc_time(3550089600 + 24), 24_s, true); // 1 Jul 2012
	test_transition(get_utc_time(3644697600 + 25), 25_s, true); // 1 Jul 2015
	test_transition(get_utc_time(3692217600 + 26), 26_s, true); // 1 Jan 2017
}

}	// namespace get_leap_second_info_test

}	// namespace hamon_chrono_test
