/**
 *	@file	unit_test_chrono_utc_clock.cpp
 *
 *	@brief	utc_clock のテスト
 */

#include <hamon/chrono/utc_clock.hpp>
#include <hamon/chrono/utc_seconds.hpp>
#include <hamon/chrono/sys_seconds.hpp>
#include <hamon/chrono/sys_time.hpp>
#include <hamon/chrono/year_month_day.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/cmath/nextafter.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace utc_clock_test
{

template <typename Duration>
static void test_leap_seconds(hamon::chrono::utc_time<Duration> time, hamon::chrono::sys_time<Duration> expected)
{
	auto result = hamon::chrono::utc_clock::to_sys(time);
	EXPECT_TRUE(result == expected);
}

static hamon::chrono::sys_seconds get_sys_time(long long seconds_since_1900)
{
	// The file leap-seconds.list stores dates since 1 January 1900, 00:00:00, we want
	// seconds since 1 January 1970.
	constexpr auto offset =
		hamon::chrono::sys_days{ hamon::chrono::January / 1 / 1970 } - hamon::chrono::sys_days{ hamon::chrono::January / 1 / 1900 };
	return hamon::chrono::sys_seconds{ hamon::chrono::seconds{seconds_since_1900} - offset };
}

void to_sys_test()
{
	namespace chrono = hamon::chrono;
	using namespace hamon::chrono_literals;

	static_assert(hamon::is_same<chrono::sys_time<chrono::nanoseconds>,
		decltype(chrono::utc_clock::to_sys(chrono::utc_time<chrono::nanoseconds>{0_ns}))>::value, "");
	static_assert(hamon::is_same<chrono::sys_time<chrono::microseconds>,
		decltype(chrono::utc_clock::to_sys(chrono::utc_time<chrono::microseconds>{0_us}))>::value, "");
	static_assert(hamon::is_same<chrono::sys_time<chrono::milliseconds>,
		decltype(chrono::utc_clock::to_sys(chrono::utc_time<chrono::milliseconds>{0_ms}))>::value, "");
	static_assert(hamon::is_same<chrono::sys_time<chrono::seconds>,
		decltype(chrono::utc_clock::to_sys(chrono::utc_time<chrono::seconds>{chrono::seconds{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::sys_time<chrono::seconds>,
		decltype(chrono::utc_clock::to_sys(chrono::utc_time<chrono::minutes>{chrono::minutes{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::sys_time<chrono::seconds>,
		decltype(chrono::utc_clock::to_sys(chrono::utc_time<chrono::hours>{chrono::hours{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::sys_time<chrono::seconds>,
		decltype(chrono::utc_clock::to_sys(chrono::utc_time<chrono::days>{chrono::days{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::sys_time<chrono::seconds>,
		decltype(chrono::utc_clock::to_sys(chrono::utc_time<chrono::weeks>{chrono::weeks{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::sys_time<chrono::seconds>,
		decltype(chrono::utc_clock::to_sys(chrono::utc_time<chrono::months>{chrono::months{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::sys_time<chrono::seconds>,
		decltype(chrono::utc_clock::to_sys(chrono::utc_time<chrono::years>{chrono::years{ 0 }}))>::value, "");

	static_assert(!noexcept(chrono::utc_clock::to_sys(chrono::utc_seconds{0_s})), "");

	// test_transitions
	{
		test_leap_seconds(chrono::utc_seconds::min(), chrono::sys_seconds::min());

		// Epoch transition no transitions.
		test_leap_seconds(chrono::utc_seconds{ -1_s }, chrono::sys_seconds{ -1_s });
		test_leap_seconds(chrono::utc_seconds{  0_s }, chrono::sys_seconds{  0_s });
		test_leap_seconds(chrono::utc_seconds{  1_s }, chrono::sys_seconds{  1_s });

		// "sys" is the time of the transition to the next leap second.
		// "elapsed" is the number of leap seconds before the transition.
		// "positive" is the leap second added +1_s? If not it's -1_s.
		auto test_transition = [](chrono::sys_seconds sys, chrono::seconds elapsed, bool positive)
		{
			// Note at the time of writing all leap seconds are positive so the else
			// branch is never executed. The private test for this function tests
			// negative leap seconds and uses the else branch.

			chrono::utc_seconds utc = chrono::utc_seconds{ sys.time_since_epoch() } + elapsed;
			if (positive)
			{
				// Every transition has the following tests
				// - 1_ns before the start of the transition no adjustment needed
				// -         at the start of the transition sys is clamped at the time just prior to the moment
				//                                          of the leap second insertion. The exact value depends
				//                                          on the resolution of the result type.
				// - 1_ns before the end   of the transition sys is still clamped like before
				// -         at the end   of the transition sys is 1_s behind the utc time
				// - 1_ns after  the end   of the transition sys is still 1_s behind the utc time
				test_leap_seconds(utc - 1_ns,       sys - 1_ns);
				test_leap_seconds(utc,              sys - 1_s);
				test_leap_seconds(utc + 0_ns,       sys - 1_ns);
				test_leap_seconds(utc + 1_s - 1_ns, sys - 1_ns);
				test_leap_seconds(utc + 1_s,        sys);
				test_leap_seconds(utc + 1_s + 0_ns, sys + 0_ns);
				test_leap_seconds(utc + 1_s + 1_ns, sys + 1_ns);
			}
			else
			{
				// Every transition has the following tests
				// - 1_ns before the transition no adjustment needed
				// -         at the transition sys is 1_s ahead of the utc time
				// - 1_ns after  the transition sys is still 1_s ahead of the utc time
				test_leap_seconds(utc - 1_ns, sys - 1_ns);
				test_leap_seconds(utc,        sys + 1_s);
				test_leap_seconds(utc + 1_ns, sys + 1_s + 1_ns);
			}
		};

		// Transitions from the start of UTC.
		test_transition(get_sys_time(2287785600), 0_s, true);  // 1 Jul 1972
		test_transition(get_sys_time(2303683200), 1_s, true);  // 1 Jan 1973
		test_transition(get_sys_time(2335219200), 2_s, true);  // 1 Jan 1974
		test_transition(get_sys_time(2366755200), 3_s, true);  // 1 Jan 1975
		test_transition(get_sys_time(2398291200), 4_s, true);  // 1 Jan 1976
		test_transition(get_sys_time(2429913600), 5_s, true);  // 1 Jan 1977
		test_transition(get_sys_time(2461449600), 6_s, true);  // 1 Jan 1978
		test_transition(get_sys_time(2492985600), 7_s, true);  // 1 Jan 1979
		test_transition(get_sys_time(2524521600), 8_s, true);  // 1 Jan 1980
		test_transition(get_sys_time(2571782400), 9_s, true);  // 1 Jul 1981
		test_transition(get_sys_time(2603318400), 10_s, true); // 1 Jul 1982
		test_transition(get_sys_time(2634854400), 11_s, true); // 1 Jul 1983
		test_transition(get_sys_time(2698012800), 12_s, true); // 1 Jul 1985
		test_transition(get_sys_time(2776982400), 13_s, true); // 1 Jan 1988
		test_transition(get_sys_time(2840140800), 14_s, true); // 1 Jan 1990
		test_transition(get_sys_time(2871676800), 15_s, true); // 1 Jan 1991
		test_transition(get_sys_time(2918937600), 16_s, true); // 1 Jul 1992
		test_transition(get_sys_time(2950473600), 17_s, true); // 1 Jul 1993
		test_transition(get_sys_time(2982009600), 18_s, true); // 1 Jul 1994
		test_transition(get_sys_time(3029443200), 19_s, true); // 1 Jan 1996
		test_transition(get_sys_time(3076704000), 20_s, true); // 1 Jul 1997
		test_transition(get_sys_time(3124137600), 21_s, true); // 1 Jan 1999
		test_transition(get_sys_time(3345062400), 22_s, true); // 1 Jan 2006
		test_transition(get_sys_time(3439756800), 23_s, true); // 1 Jan 2009
		test_transition(get_sys_time(3550089600), 24_s, true); // 1 Jul 2012
		test_transition(get_sys_time(3644697600), 25_s, true); // 1 Jul 2015
		test_transition(get_sys_time(3692217600), 26_s, true); // 1 Jan 2017
	}

	// test_transitions_floating_point
	{
		// Based on test_transitions but uses a floating-point duration.
		using F = float;

		auto test_transition = [](chrono::sys_seconds sys, chrono::seconds elapsed, bool positive)
		{
			// Note at the time of writing all leap seconds are positive so the else
			// branch is never executed. The private test for this function tests
			// negative leap seconds and uses the else branch.

			chrono::utc_seconds utc = chrono::utc_seconds{ sys.time_since_epoch() } + elapsed;

			using D = chrono::duration<F>;
			using S = chrono::time_point<chrono::system_clock, D>;
			using U = chrono::time_point<chrono::utc_clock, D>;

			S s{ sys.time_since_epoch() };
			bool is_leap_second = (s.time_since_epoch().count() == static_cast<F>(sys.time_since_epoch().count()));
			EXPECT_TRUE(is_leap_second);

			U u{ utc.time_since_epoch() };
			if (positive)
			{
				test_leap_seconds(u - 1_ns,       s - 1_ns);
				test_leap_seconds(u,              s - 1_s);
				test_leap_seconds(u + 0_ns,       s - 1_ns);
				test_leap_seconds(u + 1_s - 1_ns, s - 1_ns);
				test_leap_seconds(u + 1_s,        s);
				test_leap_seconds(u + 1_s + 0_ns, s + 0_ns);
				test_leap_seconds(u + 1_s + 1_ns, s + 1_ns);

				test_leap_seconds(
					U{ D{hamon::nextafter(u.time_since_epoch().count(), F{0})} },
					S{ D{hamon::nextafter(s.time_since_epoch().count(), F{0})} });
				test_leap_seconds(
					u,
					S{ D{s.time_since_epoch().count() - F{1}} });
				test_leap_seconds(
					U{ D{u.time_since_epoch().count() + F{1}} },
					s);
				test_leap_seconds(
					U{ D{hamon::nextafter(u.time_since_epoch().count() + F{1}, hamon::numeric_limits<F>::max())} },
					S{ D{hamon::nextafter(s.time_since_epoch().count(), hamon::numeric_limits<F>::max())} });
			}
		};

		// Transitions from the start of UTC.
		test_transition(get_sys_time(2287785600), 0_s, true);  // 1 Jul 1972
		test_transition(get_sys_time(2303683200), 1_s, true);  // 1 Jan 1973
		test_transition(get_sys_time(2335219200), 2_s, true);  // 1 Jan 1974
		test_transition(get_sys_time(2366755200), 3_s, true);  // 1 Jan 1975
		test_transition(get_sys_time(2398291200), 4_s, true);  // 1 Jan 1976
		test_transition(get_sys_time(2429913600), 5_s, true);  // 1 Jan 1977
		test_transition(get_sys_time(2461449600), 6_s, true);  // 1 Jan 1978
		test_transition(get_sys_time(2492985600), 7_s, true);  // 1 Jan 1979
		test_transition(get_sys_time(2524521600), 8_s, true);  // 1 Jan 1980
		test_transition(get_sys_time(2571782400), 9_s, true);  // 1 Jul 1981
		test_transition(get_sys_time(2603318400), 10_s, true); // 1 Jul 1982
		test_transition(get_sys_time(2634854400), 11_s, true); // 1 Jul 1983
		test_transition(get_sys_time(2698012800), 12_s, true); // 1 Jul 1985
		test_transition(get_sys_time(2776982400), 13_s, true); // 1 Jan 1988
		test_transition(get_sys_time(2840140800), 14_s, true); // 1 Jan 1990
		test_transition(get_sys_time(2871676800), 15_s, true); // 1 Jan 1991
		test_transition(get_sys_time(2918937600), 16_s, true); // 1 Jul 1992
		test_transition(get_sys_time(2950473600), 17_s, true); // 1 Jul 1993
		test_transition(get_sys_time(2982009600), 18_s, true); // 1 Jul 1994
		test_transition(get_sys_time(3029443200), 19_s, true); // 1 Jan 1996
		test_transition(get_sys_time(3076704000), 20_s, true); // 1 Jul 1997
		test_transition(get_sys_time(3124137600), 21_s, true); // 1 Jan 1999
		test_transition(get_sys_time(3345062400), 22_s, true); // 1 Jan 2006
		test_transition(get_sys_time(3439756800), 23_s, true); // 1 Jan 2009
		test_transition(get_sys_time(3550089600), 24_s, true); // 1 Jul 2012
		test_transition(get_sys_time(3644697600), 25_s, true); // 1 Jul 2015
		test_transition(get_sys_time(3692217600), 26_s, true); // 1 Jan 2017
	}
}

template <typename Duration>
static void test_leap_seconds(hamon::chrono::time_point<hamon::chrono::system_clock, Duration> time,
	hamon::chrono::seconds leap_seconds)
{
	auto utc = hamon::chrono::utc_clock::from_sys(time);
	auto diff = utc.time_since_epoch() - time.time_since_epoch();
	EXPECT_TRUE(diff == leap_seconds);
}

void from_sys_test()
{
	namespace chrono = hamon::chrono;
	using namespace hamon::chrono_literals;

	static_assert(hamon::is_same<chrono::utc_time<chrono::nanoseconds>,
		decltype(chrono::utc_clock::from_sys(chrono::sys_time<chrono::nanoseconds>{0_ns}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::microseconds>,
		decltype(chrono::utc_clock::from_sys(chrono::sys_time<chrono::microseconds>{0_us}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::milliseconds>,
		decltype(chrono::utc_clock::from_sys(chrono::sys_time<chrono::milliseconds>{0_ms}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::utc_clock::from_sys(chrono::sys_time<chrono::seconds>{chrono::seconds{ 0 }})) > ::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::utc_clock::from_sys(chrono::sys_time<chrono::minutes>{chrono::minutes{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::utc_clock::from_sys(chrono::sys_time<chrono::hours>{chrono::hours{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::utc_clock::from_sys(chrono::sys_time<chrono::days>{chrono::days{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::utc_clock::from_sys(chrono::sys_time<chrono::weeks>{chrono::weeks{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::utc_clock::from_sys(chrono::sys_time<chrono::months>{chrono::months{ 0 }}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::utc_clock::from_sys(chrono::sys_time<chrono::years>{chrono::years{ 0 }}))>::value, "");

	static_assert(!noexcept(chrono::utc_clock::from_sys(chrono::sys_seconds{0_s})), "");

	{
		// [time.clock.utc.members]/3
		auto t = hamon::chrono::sys_days{ hamon::chrono::July / 1 / 2015 } - 2_ns;
		test_leap_seconds(t, 25_s);

		t += 1_ns;
		test_leap_seconds(t, 25_s);

		t += 1_ns;
		test_leap_seconds(t, 26_s);

		t += 1_ns;
		test_leap_seconds(t, 26_s);
	}

	test_leap_seconds(chrono::sys_seconds::min(), 0_s);
	test_leap_seconds(chrono::sys_days::min(), 0_s);

	// Epoch transition no transitions.
	test_leap_seconds(chrono::sys_seconds{ -1_s }, 0_s);
	test_leap_seconds(chrono::sys_seconds{ 0_s }, 0_s);
	test_leap_seconds(chrono::sys_seconds{ 1_s }, 0_s);

	// Transitions from the start of UTC.
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1972 } - 1_ns, 0_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1972 },        0_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1972 } + 1_ns, 0_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1972 } - 1_ns, 0_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1972 },        1_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1972 } + 1_ns, 1_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1973 } - 1_ns, 1_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1973 },        2_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1973 } + 1_ns, 2_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1974 } - 1_ns, 2_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1974 },        3_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1974 } + 1_ns, 3_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1975 } - 1_ns, 3_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1975 },        4_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1975 } + 1_ns, 4_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1976 } - 1_ns, 4_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1976 },        5_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1976 } + 1_ns, 5_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1977 } - 1_ns, 5_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1977 },        6_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1977 } + 1_ns, 6_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1978 } - 1_ns, 6_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1978 },        7_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1978 } + 1_ns, 7_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1979 } - 1_ns, 7_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1979 },        8_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1979 } + 1_ns, 8_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1980 } - 1_ns, 8_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1980 },        9_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1980 } + 1_ns, 9_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1981 } - 1_ns,  9_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1981 },        10_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1981 } + 1_ns, 10_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1982 } - 1_ns, 10_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1982 },        11_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1982 } + 1_ns, 11_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1983 } - 1_ns, 11_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1983 },        12_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1983 } + 1_ns, 12_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1985 } - 1_ns, 12_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1985 },        13_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1985 } + 1_ns, 13_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1988 } - 1_ns, 13_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1988 },        14_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1988 } + 1_ns, 14_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1990 } - 1_ns, 14_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1990 },        15_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1990 } + 1_ns, 15_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1991 } - 1_ns, 15_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1991 },        16_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1991 } + 1_ns, 16_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1992 } - 1_ns, 16_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1992 },        17_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1992 } + 1_ns, 17_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1993 } - 1_ns, 17_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1993 },        18_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1993 } + 1_ns, 18_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1994 } - 1_ns, 18_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1994 },        19_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1994 } + 1_ns, 19_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1996 } - 1_ns, 19_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1996 },        20_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1996 } + 1_ns, 20_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1997 } - 1_ns, 20_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1997 },        21_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 1997 } + 1_ns, 21_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1999 } - 1_ns, 21_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1999 },        22_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 1999 } + 1_ns, 22_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2006 } - 1_ns, 22_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2006 },        23_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2006 } + 1_ns, 23_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2009 } - 1_ns, 23_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2009 },        24_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2009 } + 1_ns, 24_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 2012 } - 1_ns, 24_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 2012 },        25_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 2012 } + 1_ns, 25_s);

	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 2015 } - 1_ns, 25_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 2015 },        26_s);
	test_leap_seconds(chrono::sys_days{ chrono::July / 1 / 2015 } + 1_ns, 26_s);

	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2017 } - 1_ns, 26_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2017 },        27_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2017 } + 1_ns, 27_s);

	// This validates status when the tests were written.
	// It's not possible to test the future; there might be additional leap
	// seconds in the future.
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2024 } - 1_ns, 27_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2024 },        27_s);
	test_leap_seconds(chrono::sys_days{ chrono::January / 1 / 2024 } + 1_ns, 27_s);
}

GTEST_TEST(ChronoTest, UtcClockTest)
{
	using Clock = hamon::chrono::utc_clock;
	using rep                = typename Clock::rep;
	using period             = typename Clock::period;
	using duration           = typename Clock::duration;
	using time_point         = typename Clock::time_point;
	constexpr bool is_steady = Clock::is_steady;

	static_assert(hamon::is_same<rep, hamon::chrono::system_clock::rep>::value, "");
	static_assert(hamon::is_arithmetic<rep>::value, "");
	static_assert(hamon::is_signed<rep>::value, "");

	static_assert(hamon::is_same<period, hamon::chrono::system_clock::period>::value, "");
	static_assert(hamon::is_same<period, hamon::ratio<period::num, period::den>>::value, "");

	static_assert(hamon::is_same<duration, hamon::chrono::duration<rep, period>>::value, "");
	static_assert(hamon::is_same<time_point, hamon::chrono::time_point<hamon::chrono::utc_clock>>::value, "");
	static_assert(is_steady == false, "");

	// typedefs
	static_assert(hamon::is_same<hamon::chrono::utc_time<int>,  hamon::chrono::time_point<hamon::chrono::utc_clock, int>>::value, "");
	static_assert(hamon::is_same<hamon::chrono::utc_time<long>, hamon::chrono::time_point<hamon::chrono::utc_clock, long>>::value, "");
	static_assert(hamon::is_same<hamon::chrono::utc_seconds,    hamon::chrono::utc_time<hamon::chrono::seconds>>::value, "");

	static_assert(!noexcept(Clock::now()), "");
	static_assert(hamon::is_same<time_point, decltype(Clock::now())>::value, "");
	{
		auto t = Clock::now();
		EXPECT_TRUE(t >= Clock::time_point::min());
		EXPECT_TRUE(t <= Clock::time_point::max());

		auto t2 = Clock::now();
		EXPECT_TRUE(t2 - t >= hamon::chrono::seconds(0));
		// This may fail if the tests takes a long time to complete.
		EXPECT_TRUE(t2 - t <  hamon::chrono::seconds(42));
	}

	to_sys_test();
	from_sys_test();
}

}	// namespace utc_clock_test

}	// namespace hamon_chrono_test
