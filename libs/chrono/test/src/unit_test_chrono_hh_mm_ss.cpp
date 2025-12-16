/**
 *	@file	unit_test_chrono_hh_mm_ss.cpp
 *
 *	@brief	hh_mm_ss のテスト
 */

#include <hamon/chrono/hh_mm_ss.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace hh_mm_ss_test
{

template <typename Duration>
HAMON_CXX11_CONSTEXPR long long check_default_ctor()
{
	using HMS = hamon::chrono::hh_mm_ss<Duration>;
	static_assert( hamon::is_default_constructible<HMS>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<HMS>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<HMS>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<HMS>::value, "");
	return HMS().to_duration().count();
}

template <typename Duration>
void check_ctor()
{
	using HMS = hamon::chrono::hh_mm_ss<Duration>;
	static_assert( hamon::is_constructible<HMS, Duration>::value, "");
	static_assert(!hamon::is_nothrow_constructible<HMS, Duration>::value, "");
	static_assert(!hamon::is_trivially_constructible<HMS, Duration>::value, "");
	static_assert(!hamon::is_implicitly_constructible<HMS, Duration>::value, "");
}

template <typename Duration>
HAMON_CXX11_CONSTEXPR bool check_neg(Duration d)
{
	using HMS = hamon::chrono::hh_mm_ss<Duration>;
	static_assert(hamon::is_same<bool, decltype(hamon::declval<HMS>().is_negative())>::value, "");
	static_assert(noexcept(hamon::declval<HMS>().is_negative()), "");
	return HMS(d).is_negative();
}

template <typename Duration>
HAMON_CXX11_CONSTEXPR long check_hours(Duration d)
{
	using HMS = hamon::chrono::hh_mm_ss<Duration>;
	static_assert(hamon::is_same<hamon::chrono::hours, decltype(hamon::declval<HMS>().hours())>::value, "");
	static_assert(noexcept(hamon::declval<HMS>().hours()), "");
	return HMS(d).hours().count();
}

template <typename Duration>
HAMON_CXX11_CONSTEXPR long check_minutes(Duration d)
{
	using HMS = hamon::chrono::hh_mm_ss<Duration>;
	static_assert(hamon::is_same<hamon::chrono::minutes, decltype(hamon::declval<HMS>().minutes())>::value, "");
	static_assert(noexcept(hamon::declval<HMS>().minutes()), "");
	return HMS(d).minutes().count();
}

template <typename Duration>
HAMON_CXX11_CONSTEXPR hamon::int64_t check_seconds(Duration d)
{
	using HMS = hamon::chrono::hh_mm_ss<Duration>;
	static_assert(hamon::is_same<hamon::chrono::seconds, decltype(hamon::declval<HMS>().seconds())>::value, "");
	static_assert(noexcept(hamon::declval<HMS>().seconds()), "");
	return HMS(d).seconds().count();
}

template <typename Duration>
HAMON_CXX11_CONSTEXPR hamon::int64_t check_subseconds(Duration d)
{
	using HMS = hamon::chrono::hh_mm_ss<Duration>;
	static_assert(hamon::is_same<typename HMS::precision, decltype(hamon::declval<HMS>().subseconds())>::value, "");
	static_assert(noexcept(hamon::declval<HMS>().subseconds()), "");
	return HMS(d).subseconds().count();
}

template <typename Duration>
HAMON_CXX11_CONSTEXPR long long check_precision(Duration d)
{
	using HMS = hamon::chrono::hh_mm_ss<Duration>;
	using precision = typename HMS::precision;
	static_assert(hamon::is_same<typename HMS::precision, decltype(static_cast<precision>(hamon::declval<HMS>()))>::value, "");
	static_assert(noexcept(static_cast<precision>(hamon::declval<HMS>())), "");
	return static_cast<precision>(HMS(d)).count();
}

template <typename Duration>
HAMON_CXX11_CONSTEXPR long long check_duration(Duration d)
{
	using HMS = hamon::chrono::hh_mm_ss<Duration>;
	static_assert(hamon::is_same<typename HMS::precision, decltype(hamon::declval<HMS>().to_duration())>::value, "");
	static_assert(noexcept(hamon::declval<HMS>().to_duration()), "");
	return HMS(d).to_duration().count();
}

GTEST_TEST(ChronoTest, HHMMSSTest)
{
	using namespace hamon::chrono;

	// fractional_width
	static_assert(hh_mm_ss<hours>::fractional_width == 0, "");
	static_assert(hh_mm_ss<minutes>::fractional_width == 0, "");
	static_assert(hh_mm_ss<seconds>::fractional_width == 0, "");
	static_assert(hh_mm_ss<milliseconds>::fractional_width == 3, "");
	static_assert(hh_mm_ss<microseconds>::fractional_width == 6, "");
	static_assert(hh_mm_ss<nanoseconds>::fractional_width == 9, "");
	static_assert(hh_mm_ss<duration<int, hamon::ratio<1, 2>>>::fractional_width == 1, "");
	static_assert(hh_mm_ss<duration<int, hamon::ratio<1, 3>>>::fractional_width == 6, "");
	static_assert(hh_mm_ss<duration<int, hamon::ratio<1, 4>>>::fractional_width == 2, "");
	static_assert(hh_mm_ss<duration<int, hamon::ratio<1, 5>>>::fractional_width == 1, "");
	static_assert(hh_mm_ss<duration<int, hamon::ratio<1, 6>>>::fractional_width == 6, "");
	static_assert(hh_mm_ss<duration<int, hamon::ratio<1, 7>>>::fractional_width == 6, "");
	static_assert(hh_mm_ss<duration<int, hamon::ratio<1, 8>>>::fractional_width == 3, "");
	static_assert(hh_mm_ss<duration<int, hamon::ratio<1, 9>>>::fractional_width == 6, "");
	static_assert(hh_mm_ss<duration<int, hamon::ratio<1, 10>>>::fractional_width == 1, "");
	static_assert(hh_mm_ss<duration<int, hamon::ratio<756, 625>>>::fractional_width == 4, "");

	// precision
	static_assert(hamon::is_same<hh_mm_ss<hours>::precision, duration<hamon::int64_t, hamon::ratio<1, 1>>>::value, "");
	static_assert(hamon::is_same<hh_mm_ss<minutes>::precision, duration<hamon::int64_t, hamon::ratio<1, 1>>>::value, "");
	static_assert(hamon::is_same<hh_mm_ss<seconds>::precision, duration<hamon::int64_t, hamon::ratio<1, 1>>>::value, "");
	static_assert(hamon::is_same<hh_mm_ss<milliseconds>::precision, duration<hamon::int64_t, hamon::ratio<1, 1000>>>::value, "");
	static_assert(hamon::is_same<hh_mm_ss<microseconds>::precision, duration<hamon::int64_t, hamon::ratio<1, 1000000LL>>>::value, "");
	static_assert(hamon::is_same<hh_mm_ss<nanoseconds>::precision, duration<hamon::int64_t, hamon::ratio<1, 1000000000LL>>>::value, "");

	// default ctor
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(check_default_ctor<hours>() == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(check_default_ctor<minutes>() == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(check_default_ctor<seconds>() == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(check_default_ctor<milliseconds>() == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(check_default_ctor<microseconds>() == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(check_default_ctor<nanoseconds>() == 0);

	// ctor
	check_ctor<hours>();
	check_ctor<minutes>();
	check_ctor<seconds>();
	check_ctor<milliseconds>();
	check_ctor<microseconds>();
	check_ctor<nanoseconds>();

	using microfortnights = duration<int, hamon::ratio<756, 625>>;

	// is_negative
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!check_neg(minutes( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_neg(minutes(-1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!check_neg(seconds( 5000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_neg(seconds(-5000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!check_neg(minutes( 5000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_neg(minutes(-5000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!check_neg(hours( 11)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_neg(hours(-11)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!check_neg(milliseconds( 123456789LL)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_neg(milliseconds(-123456789LL)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!check_neg(microseconds( 123456789LL)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_neg(microseconds(-123456789LL)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!check_neg(nanoseconds( 123456789LL)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_neg(nanoseconds(-123456789LL)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!check_neg(microfortnights( 10000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_neg(microfortnights(-10000)));

	// hours
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(minutes( 1)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(minutes(-1)) == 0);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(seconds( 5000)) == 1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(seconds(-5000)) == 1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(minutes( 5000)) == 83);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(minutes(-5000)) == 83);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(hours( 11))     == 11);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(hours(-11))     == 11);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(milliseconds( 123456789LL)) == 34);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(milliseconds(-123456789LL)) == 34);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(microseconds( 123456789LL)) ==  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(microseconds(-123456789LL)) ==  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(nanoseconds( 123456789LL))  ==  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(nanoseconds(-123456789LL))  ==  0);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(microfortnights(  1000)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(microfortnights( -1000)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(microfortnights( 10000)) == 3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_hours(microfortnights(-10000)) == 3);

	// minutes
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(minutes( 1)) == 1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(minutes(-1)) == 1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(seconds( 5000)) == 23);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(seconds(-5000)) == 23);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(minutes( 5000)) == 20);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(minutes(-5000)) == 20);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(hours( 11))     == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(hours(-11))     == 0);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(milliseconds( 123456789LL)) == 17);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(milliseconds(-123456789LL)) == 17);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(microseconds( 123456789LL)) == 2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(microseconds(-123456789LL)) == 2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(nanoseconds( 123456789LL))  == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(nanoseconds(-123456789LL))  == 0);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(microfortnights(  1000)) == 20);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(microfortnights( -1000)) == 20);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(microfortnights( 10000)) == 21);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_minutes(microfortnights(-10000)) == 21);

	// seconds
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(seconds( 1)) == 1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(seconds(-1)) == 1);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(seconds( 5000)) == 20);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(seconds(-5000)) == 20);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(minutes( 5000)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(minutes(-5000)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(hours( 11))     == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(hours(-11))     == 0);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(milliseconds( 123456789LL)) == 36);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(milliseconds(-123456789LL)) == 36);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(microseconds( 123456789LL)) == 3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(microseconds(-123456789LL)) == 3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(nanoseconds( 123456789LL))  == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(nanoseconds(-123456789LL))  == 0);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(microfortnights(  1000)) ==  9);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(microfortnights( -1000)) ==  9);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(microfortnights( 10000)) == 36);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_seconds(microfortnights(-10000)) == 36);

	// subseconds
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(seconds( 1)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(seconds(-1)) == 0);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(seconds( 5000)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(seconds(-5000)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(minutes( 5000)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(minutes(-5000)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(hours( 11))     == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(hours(-11))     == 0);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(milliseconds( 123456789LL)) == 789);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(milliseconds(-123456789LL)) == 789);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(microseconds( 123456789LL)) == 456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(microseconds(-123456789LL)) == 456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(nanoseconds( 123456789LL))  == 123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(nanoseconds(-123456789LL))  == 123456789LL);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(microfortnights(  1000)) == 6000);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(microfortnights( -1000)) == 6000);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(microfortnights( 10000)) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_subseconds(microfortnights(-10000)) == 0);

	// operator precision()
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(minutes( 1)) ==  60);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(minutes(-1)) == -60);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(seconds( 5000)) ==    5000LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(seconds(-5000)) ==   -5000LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(minutes( 5000)) ==  300000LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(minutes(-5000)) == -300000LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(hours( 11))     ==   39600LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(hours(-11))     ==  -39600LL);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(milliseconds( 123456789LL)) ==  123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(milliseconds(-123456789LL)) == -123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(microseconds( 123456789LL)) ==  123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(microseconds(-123456789LL)) == -123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(nanoseconds( 123456789LL))  ==  123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(nanoseconds(-123456789LL))  == -123456789LL);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(microfortnights(  1000)) ==   12096000);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(microfortnights( -1000)) ==  -12096000);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(microfortnights( 10000)) ==  120960000);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_precision(microfortnights(-10000)) == -120960000);

	// to_duration
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(minutes( 1)) ==  60);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(minutes(-1)) == -60);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(seconds( 5000)) ==    5000LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(seconds(-5000)) ==   -5000LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(minutes( 5000)) ==  300000LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(minutes(-5000)) == -300000LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(hours( 11))     ==   39600LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(hours(-11))     ==  -39600LL);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(milliseconds( 123456789LL)) ==  123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(milliseconds(-123456789LL)) == -123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(microseconds( 123456789LL)) ==  123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(microseconds(-123456789LL)) == -123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(nanoseconds( 123456789LL))  ==  123456789LL);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(nanoseconds(-123456789LL))  == -123456789LL);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(microfortnights(  1000)) ==   12096000);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(microfortnights( -1000)) ==  -12096000);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(microfortnights( 10000)) ==  120960000);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( check_duration(microfortnights(-10000)) == -120960000);
}

}	// namespace hh_mm_ss_test

}	// namespace hamon_chrono_test
