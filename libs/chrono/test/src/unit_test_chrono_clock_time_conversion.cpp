/**
 *	@file	unit_test_chrono_clock_time_conversion.cpp
 *
 *	@brief	clock_time_conversion のテスト
 */

#include <hamon/chrono/clock_time_conversion.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/chrono/utc_clock.hpp>
#include <hamon/chrono/gps_clock.hpp>
#include <hamon/chrono/tai_clock.hpp>
#include <hamon/chrono/file_clock.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace clock_time_conversion_test
{

template <typename Dest, typename Source, typename = void>
struct can_conversion
	: hamon::false_type{};

template <typename Dest, typename Source>
struct can_conversion<Dest, Source,
	hamon::void_t<decltype(hamon::chrono::clock_time_conversion<Dest, Source>{}(Source::now()))>>
	: hamon::true_type{};

GTEST_TEST(ChronoTest, ClockTimeConversionTest)
{
	using hamon::chrono::clock_time_conversion;
	using hamon::chrono::system_clock;
	using hamon::chrono::utc_clock;
	using hamon::chrono::gps_clock;
	using hamon::chrono::tai_clock;
	using hamon::chrono::file_clock;

	static_assert( can_conversion<system_clock, system_clock>::value, "");
	static_assert( can_conversion<system_clock, utc_clock>::value, "");
	static_assert(!can_conversion<system_clock, gps_clock>::value, "");
	static_assert(!can_conversion<system_clock, tai_clock>::value, "");
	static_assert( can_conversion<system_clock, file_clock>::value, "");

	static_assert( can_conversion<utc_clock, system_clock>::value, "");
	static_assert( can_conversion<utc_clock, utc_clock>::value, "");
	static_assert( can_conversion<utc_clock, gps_clock>::value, "");
	static_assert( can_conversion<utc_clock, tai_clock>::value, "");
	static_assert(!can_conversion<utc_clock, file_clock>::value, "");

	static_assert(!can_conversion<gps_clock, system_clock>::value, "");
	static_assert( can_conversion<gps_clock, utc_clock>::value, "");
	static_assert( can_conversion<gps_clock, gps_clock>::value, "");
	static_assert(!can_conversion<gps_clock, tai_clock>::value, "");
	static_assert(!can_conversion<gps_clock, file_clock>::value, "");

	static_assert(!can_conversion<tai_clock, system_clock>::value, "");
	static_assert( can_conversion<tai_clock, utc_clock>::value, "");
	static_assert(!can_conversion<tai_clock, gps_clock>::value, "");
	static_assert( can_conversion<tai_clock, tai_clock>::value, "");
	static_assert(!can_conversion<tai_clock, file_clock>::value, "");

	static_assert( can_conversion<file_clock, system_clock>::value, "");
	static_assert(!can_conversion<file_clock, utc_clock>::value, "");
	static_assert(!can_conversion<file_clock, gps_clock>::value, "");
	static_assert(!can_conversion<file_clock, tai_clock>::value, "");
	static_assert( can_conversion<file_clock, file_clock>::value, "");

	// clock_time_conversion<Clock, Clock>
	{
		auto t = clock_time_conversion<tai_clock, tai_clock>{}(tai_clock::now());
		static_assert(hamon::is_same<decltype(t), tai_clock::time_point>::value, "");
	}
	{
		auto t = clock_time_conversion<file_clock, file_clock>{}(file_clock::now());
		static_assert(hamon::is_same<decltype(t), file_clock::time_point>::value, "");
	}

	// clock_time_conversion<system_clock, system_clock>
	{
		auto t = clock_time_conversion<system_clock, system_clock>{}(system_clock::now());
		static_assert(hamon::is_same<decltype(t), system_clock::time_point>::value, "");
	}

	// clock_time_conversion<utc_clock, utc_clock>
	{
		auto t = clock_time_conversion<utc_clock, utc_clock>{}(utc_clock::now());
		static_assert(hamon::is_same<decltype(t), utc_clock::time_point>::value, "");
	}

	// clock_time_conversion<utc_clock, system_clock>
	{
		auto t = clock_time_conversion<utc_clock, system_clock>{}(system_clock::now());
		static_assert(hamon::is_same<decltype(t), utc_clock::time_point>::value, "");
	}

	// clock_time_conversion<system_clock, utc_clock>
	{
		auto t = clock_time_conversion<system_clock, utc_clock>{}(utc_clock::now());
		static_assert(hamon::is_same<decltype(t), system_clock::time_point>::value, "");
	}

	// clock_time_conversion<system_clock, SourceClock>
	{
		auto t = clock_time_conversion<system_clock, file_clock>{}(file_clock::now());
		static_assert(hamon::is_same<decltype(t), decltype(file_clock::to_sys(file_clock::now()))>::value, "");
	}

	// clock_time_conversion<DestClock, system_clock>
	{
		auto t = clock_time_conversion<file_clock, system_clock>{}(system_clock::now());
		static_assert(hamon::is_same<decltype(t), decltype(file_clock::from_sys(system_clock::now()))>::value, "");
	}

	// clock_time_conversion<utc_clock, SourceClock>
	{
		auto t = clock_time_conversion<utc_clock, gps_clock>{}(gps_clock::now());
		static_assert(hamon::is_same<decltype(t), decltype(gps_clock::to_utc(gps_clock::now()))>::value, "");
	}
	{
		auto t = clock_time_conversion<utc_clock, tai_clock>{}(tai_clock::now());
		static_assert(hamon::is_same<decltype(t), decltype(tai_clock::to_utc(tai_clock::now()))>::value, "");
	}

	// clock_time_conversion<DestClock, utc_clock>
	{
		auto t = clock_time_conversion<gps_clock, utc_clock>{}(utc_clock::now());
		static_assert(hamon::is_same<decltype(t), decltype(gps_clock::from_utc(utc_clock::now()))>::value, "");
	}
	{
		auto t = clock_time_conversion<tai_clock, utc_clock>{}(utc_clock::now());
		static_assert(hamon::is_same<decltype(t), decltype(tai_clock::from_utc(utc_clock::now()))>::value, "");
	}
}

}	// namespace clock_time_conversion_test

}	// namespace hamon_chrono_test
