/**
 *	@file	unit_test_chrono_tai_clock.cpp
 *
 *	@brief	tai_clock のテスト
 */

#include <hamon/chrono/tai_clock.hpp>
#include <hamon/chrono/tai_seconds.hpp>
#include <hamon/chrono/tai_time.hpp>
#include <hamon/chrono/utc_clock.hpp>
#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace tai_clock_test
{

void to_utc_test()
{
	namespace chrono = hamon::chrono;
	using namespace hamon::chrono_literals;

	static_assert(hamon::is_same<chrono::utc_time<chrono::nanoseconds>,
		decltype(chrono::tai_clock::to_utc(chrono::tai_time<chrono::nanoseconds>{0_ns}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::microseconds>,
		decltype(chrono::tai_clock::to_utc(chrono::tai_time<chrono::microseconds>{0_us}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::milliseconds>,
		decltype(chrono::tai_clock::to_utc(chrono::tai_time<chrono::milliseconds>{0_ms}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::tai_clock::to_utc(chrono::tai_time<chrono::seconds>{chrono::seconds{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::tai_clock::to_utc(chrono::tai_time<chrono::minutes>{chrono::minutes{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::tai_clock::to_utc(chrono::tai_time<chrono::hours>{chrono::hours{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::tai_clock::to_utc(chrono::tai_time<chrono::days>{chrono::days{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::tai_clock::to_utc(chrono::tai_time<chrono::weeks>{chrono::weeks{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::tai_clock::to_utc(chrono::tai_time<chrono::months>{chrono::months{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::utc_time<chrono::seconds>,
		decltype(chrono::tai_clock::to_utc(chrono::tai_time<chrono::years>{chrono::years{0}}))>::value, "");

	static_assert(noexcept(chrono::tai_clock::to_utc(chrono::tai_seconds{0_s})), "");

	constexpr auto unix_to_tai_epoch_offset = chrono::sys_days{chrono::January / 1 / 1970} - chrono::sys_days{chrono::January / 1 / 1958};

	// [time.clock.tai.overview]/1
	// ... 1958-01-01 00:00:00 TAI is equivalent to 1957-12-31 23:59:50 UTC
	// ... 2000-01-01 00:00:00 UTC is equivalent to 2000-01-01 00:00:32 TAI
	EXPECT_TRUE(chrono::tai_clock::to_utc(chrono::tai_seconds{0_s}) ==
		chrono::utc_clock::from_sys(chrono::sys_days{chrono::January / 1 / 1958} - 10_s));
	EXPECT_TRUE(chrono::tai_clock::to_utc(chrono::tai_seconds{(chrono::sys_days{chrono::January / 1 / 2000} + unix_to_tai_epoch_offset).time_since_epoch()} + 32_s) ==
		chrono::utc_clock::from_sys(chrono::sys_days{chrono::January / 1 / 2000}));

	// "sys" is the time of the transition to the next leap second.
	// "elapsed" is the number of leap seconds before the transition.
	auto test_transition = [&](chrono::sys_days sys, chrono::seconds elapsed)
	{
		chrono::tai_seconds tai{sys.time_since_epoch() + unix_to_tai_epoch_offset + elapsed};

		EXPECT_TRUE(chrono::tai_clock::to_utc(tai - 1_ns)       == chrono::utc_clock::from_sys(sys - 1_ns));
		EXPECT_TRUE(chrono::tai_clock::to_utc(tai + 1_s)        == chrono::utc_clock::from_sys(sys));
		EXPECT_TRUE(chrono::tai_clock::to_utc(tai + 1_s + 1_ns) == chrono::utc_clock::from_sys(sys + 1_ns));
	};

	// Transitions from the start of UTC.
	test_transition(chrono::sys_days{chrono::July    / 1 / 1972}, 10_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1973}, 11_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1974}, 12_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1975}, 13_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1976}, 14_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1977}, 15_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1978}, 16_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1979}, 17_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1980}, 18_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1981}, 19_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1982}, 20_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1983}, 21_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1985}, 22_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1988}, 23_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1990}, 24_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1991}, 25_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1992}, 26_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1993}, 27_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1994}, 28_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1996}, 29_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1997}, 30_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1999}, 31_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 2006}, 32_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 2009}, 33_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 2012}, 34_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 2015}, 35_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 2017}, 36_s);
}

void from_utc_test()
{
	namespace chrono = hamon::chrono;
	using namespace hamon::chrono_literals;

	static_assert(hamon::is_same<chrono::tai_time<chrono::nanoseconds>,
		decltype(chrono::tai_clock::from_utc(chrono::utc_time<chrono::nanoseconds>{0_ns}))>::value, "");
	static_assert(hamon::is_same<chrono::tai_time<chrono::microseconds>,
		decltype(chrono::tai_clock::from_utc(chrono::utc_time<chrono::microseconds>{0_us}))>::value, "");
	static_assert(hamon::is_same<chrono::tai_time<chrono::milliseconds>,
		decltype(chrono::tai_clock::from_utc(chrono::utc_time<chrono::milliseconds>{0_ms}))>::value, "");
	static_assert(hamon::is_same<chrono::tai_time<chrono::seconds>,
		decltype(chrono::tai_clock::from_utc(chrono::utc_time<chrono::seconds>{chrono::seconds{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::tai_time<chrono::seconds>,
		decltype(chrono::tai_clock::from_utc(chrono::utc_time<chrono::minutes>{chrono::minutes{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::tai_time<chrono::seconds>,
		decltype(chrono::tai_clock::from_utc(chrono::utc_time<chrono::hours>{chrono::hours{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::tai_time<chrono::seconds>,
		decltype(chrono::tai_clock::from_utc(chrono::utc_time<chrono::days>{chrono::days{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::tai_time<chrono::seconds>,
		decltype(chrono::tai_clock::from_utc(chrono::utc_time<chrono::weeks>{chrono::weeks{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::tai_time<chrono::seconds>,
		decltype(chrono::tai_clock::from_utc(chrono::utc_time<chrono::months>{chrono::months{0}}))>::value, "");
	static_assert(hamon::is_same<chrono::tai_time<chrono::seconds>,
		decltype(chrono::tai_clock::from_utc(chrono::utc_time<chrono::years>{chrono::years{0}}))>::value, "");

	static_assert(noexcept(chrono::tai_clock::from_utc(chrono::utc_seconds{0_s})), "");

	constexpr auto unix_to_tai_epoch_offset = chrono::sys_days{chrono::January / 1 / 1970} - chrono::sys_days{chrono::January / 1 / 1958};

	// [time.clock.tai.overview]/1
	// ... 1958-01-01 00:00:00 TAI is equivalent to 1957-12-31 23:59:50 UTC
	// ... 2000-01-01 00:00:00 UTC is equivalent to 2000-01-01 00:00:32 TAI
	EXPECT_TRUE(chrono::tai_clock::from_utc(chrono::utc_clock::from_sys(chrono::sys_days{chrono::January / 1 / 1958} - 10_s)) ==
		chrono::tai_seconds{0_s});
	EXPECT_TRUE(chrono::tai_clock::from_utc(chrono::utc_clock::from_sys(chrono::sys_days{chrono::January / 1 / 2000})) ==
		chrono::tai_seconds{(chrono::sys_days{chrono::January / 1 / 2000} + unix_to_tai_epoch_offset).time_since_epoch()} + 32_s);

	// "sys" is the time of the transition to the next leap second.
	// "elapsed" is the number of leap seconds before the transition.
	auto test_transition = [&](chrono::sys_days sys, chrono::seconds elapsed)
	{
		chrono::tai_seconds tai{sys.time_since_epoch() + unix_to_tai_epoch_offset + elapsed};

		EXPECT_TRUE(chrono::tai_clock::from_utc(chrono::utc_clock::from_sys(sys - 1_ns)) == tai - 1_ns);
		EXPECT_TRUE(chrono::tai_clock::from_utc(chrono::utc_clock::from_sys(sys))        == tai + 1_s);
		EXPECT_TRUE(chrono::tai_clock::from_utc(chrono::utc_clock::from_sys(sys) + 1_ns) == tai + 1_s + 1_ns);
	};

	// Transitions from the start of UTC.
	test_transition(chrono::sys_days{chrono::July    / 1 / 1972}, 10_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1973}, 11_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1974}, 12_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1975}, 13_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1976}, 14_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1977}, 15_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1978}, 16_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1979}, 17_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1980}, 18_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1981}, 19_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1982}, 20_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1983}, 21_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1985}, 22_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1988}, 23_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1990}, 24_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1991}, 25_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1992}, 26_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1993}, 27_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1994}, 28_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1996}, 29_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 1997}, 30_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 1999}, 31_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 2006}, 32_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 2009}, 33_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 2012}, 34_s);
	test_transition(chrono::sys_days{chrono::July    / 1 / 2015}, 35_s);
	test_transition(chrono::sys_days{chrono::January / 1 / 2017}, 36_s);
}

GTEST_TEST(ChronoTest, TaiClockTest)
{
	using Clock = hamon::chrono::tai_clock;
	using rep                = typename Clock::rep;
	using period             = typename Clock::period;
	using duration           = typename Clock::duration;
	using time_point         = typename Clock::time_point;
	constexpr bool is_steady = Clock::is_steady;

	static_assert(hamon::is_same<rep, hamon::chrono::utc_clock::rep>::value, "");
	static_assert(hamon::is_arithmetic<rep>::value, "");
	static_assert(hamon::is_signed<rep>::value, "");

	static_assert(hamon::is_same<period, hamon::chrono::utc_clock::period>::value, "");
	static_assert(hamon::is_same<period, hamon::ratio<period::num, period::den>>::value, "");

	static_assert(hamon::is_same<duration, hamon::chrono::duration<rep, period>>::value, "");
	static_assert(hamon::is_same<time_point, hamon::chrono::time_point<Clock>>::value, "");
	static_assert(is_steady == false, "");

	// typedefs
	static_assert(hamon::is_same<hamon::chrono::tai_time<int>,  hamon::chrono::time_point<Clock, int>>::value, "");
	static_assert(hamon::is_same<hamon::chrono::tai_time<long>, hamon::chrono::time_point<Clock, long>>::value, "");
	static_assert(hamon::is_same<hamon::chrono::tai_seconds,    hamon::chrono::tai_time<hamon::chrono::seconds>>::value, "");

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

}	// namespace tai_clock_test

}	// namespace hamon_chrono_test
