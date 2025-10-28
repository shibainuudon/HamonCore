/**
 *	@file	clock_time_conversion.hpp
 *
 *	@brief	clock_time_conversion の定義
 */

#ifndef HAMON_CHRONO_CLOCK_TIME_CONVERSION_HPP
#define HAMON_CHRONO_CLOCK_TIME_CONVERSION_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::clock_time_conversion;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/chrono/utc_clock.hpp>
#include <hamon/type_traits/common_type.hpp>

namespace hamon {
namespace chrono {

// 30.7.10.1 Class template clock_time_conversion[time.clock.conv]

template <typename DestClock, typename SourceClock>
struct clock_time_conversion;

// 30.7.10.2 Identity conversions[time.clock.cast.id]

template <typename Clock>
struct clock_time_conversion<Clock, Clock>
{
	template <typename Duration>
	time_point<Clock, Duration>
	operator()(time_point<Clock, Duration> const& t) const
	{
		// [time.clock.cast.id]/1
		return t;
	}
};

template <>
struct clock_time_conversion<system_clock, system_clock>
{
	template <typename Duration>
	sys_time<Duration>
	operator()(sys_time<Duration> const& t) const
	{
		// [time.clock.cast.id]/2
		return t;
	}
};

template <>
struct clock_time_conversion<utc_clock, utc_clock>
{
	template <typename Duration>
	utc_time<Duration>
	operator()(utc_time<Duration> const& t) const
	{
		// [time.clock.cast.id]/3
		return t;
	}
};

// 30.7.10.3 Conversions between system_clock and utc_clock[time.clock.cast.sys.utc]

template <>
struct clock_time_conversion<utc_clock, system_clock>
{
	template <typename Duration>
	utc_time<hamon::common_type_t<Duration, seconds>>
	operator()(sys_time<Duration> const& t) const
	{
		// [time.clock.cast.sys.utc]/1
		return utc_clock::from_sys(t);
	}
};

template <>
struct clock_time_conversion<system_clock, utc_clock>
{
	template <typename Duration>
	sys_time<hamon::common_type_t<Duration, seconds>>
	operator()(utc_time<Duration> const& t) const
	{
		// [time.clock.cast.sys.utc]/2
		return utc_clock::to_sys(t);
	}
};

namespace detail
{

template <typename TimePoint, typename Clock>
struct is_time_point_for
	: public hamon::false_type {};

template <typename Clock, typename Duration>
struct is_time_point_for<time_point<Clock, Duration>, Clock>
	: public hamon::true_type {};

}	// namespace detail

// 30.7.10.4 Conversions between system_clock and other clocks[time.clock.cast.sys]

template <typename SourceClock>
struct clock_time_conversion<system_clock, SourceClock>
{
	template <typename Duration, typename SourceClock2 = SourceClock>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		requires requires(time_point<SourceClock, Duration> const& t) { SourceClock::to_sys(t); }	// [time.clock.cast.sys]/1
#endif
	auto operator()(time_point<SourceClock, Duration> const& t) const
		-> decltype(SourceClock2::to_sys(t))
	{
		// [time.clock.cast.sys]/2
		static_assert(detail::is_time_point_for<decltype(SourceClock::to_sys(t)), system_clock>::value, "");

		// [time.clock.cast.sys]/3
		return SourceClock::to_sys(t);
	}
};

template <typename DestClock>
struct clock_time_conversion<DestClock, system_clock>
{
	template <typename Duration, typename DestClock2 = DestClock>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		requires requires(sys_time<Duration> const& t) { DestClock::from_sys(t); }	// [time.clock.cast.sys]/4
#endif
	auto operator()(sys_time<Duration> const& t) const
		-> decltype(DestClock2::from_sys(t))
	{
		// [time.clock.cast.sys]/5
		static_assert(detail::is_time_point_for<decltype(DestClock::from_sys(t)), DestClock>::value, "");

		// [time.clock.cast.sys]/6
		return DestClock::from_sys(t);
	}
};

// 30.7.10.5 Conversions between utc_clock and other clocks[time.clock.cast.utc]

template <typename SourceClock>
struct clock_time_conversion<utc_clock, SourceClock>
{
	template <typename Duration, typename SourceClock2 = SourceClock>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		requires requires(time_point<SourceClock, Duration> const& t) { SourceClock::to_utc(t); }	// [time.clock.cast.utc]/1
#endif
	auto operator()(time_point<SourceClock, Duration> const& t) const
		-> decltype(SourceClock2::to_utc(t))
	{
		// [time.clock.cast.utc]/2
		static_assert(detail::is_time_point_for<decltype(SourceClock::to_utc(t)), utc_clock>::value, "");

		// [time.clock.cast.utc]/3
		return SourceClock::to_utc(t);
	}
};

template <typename DestClock>
struct clock_time_conversion<DestClock, utc_clock>
{
	template <typename Duration, typename DestClock2 = DestClock>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		requires requires(utc_time<Duration> const& t) { DestClock::from_utc(t); }	// [time.clock.cast.utc]/4
#endif
	auto operator()(utc_time<Duration> const& t) const
		-> decltype(DestClock2::from_utc(t))
	{
		// [time.clock.cast.utc]/5
		static_assert(detail::is_time_point_for<decltype(DestClock::from_utc(t)), DestClock>::value, "");

		// [time.clock.cast.utc]/6
		return DestClock::from_utc(t);
	}
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_CLOCK_TIME_CONVERSION_HPP
