/**
 *	@file	clock_cast.hpp
 *
 *	@brief	clock_cast の定義
 */

#ifndef HAMON_CHRONO_CLOCK_CAST_HPP
#define HAMON_CHRONO_CLOCK_CAST_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::clock_cast;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/clock_time_conversion.hpp>
#include <hamon/detail/overload_priority.hpp>

namespace hamon {
namespace chrono {

namespace detail {

// [time.clock.cast.fn]/1.1
template <typename DestClock, typename SourceClock, typename Duration>
auto clock_cast_impl(chrono::time_point<SourceClock, Duration> const& t, hamon::detail::overload_priority<4>)
->decltype(clock_time_conversion<DestClock, SourceClock>{}(t))
{
	return clock_time_conversion<DestClock, SourceClock>{}(t);
}

// [time.clock.cast.fn]/1.2
template <typename DestClock, typename SourceClock, typename Duration>
auto clock_cast_impl(chrono::time_point<SourceClock, Duration> const& t, hamon::detail::overload_priority<3>)
->decltype(clock_time_conversion<DestClock, system_clock>{}(
		clock_time_conversion<system_clock, SourceClock>{}(t)))
{
	return clock_time_conversion<DestClock, system_clock>{}(
		clock_time_conversion<system_clock, SourceClock>{}(t));
}

// [time.clock.cast.fn]/1.3
template <typename DestClock, typename SourceClock, typename Duration>
auto clock_cast_impl(chrono::time_point<SourceClock, Duration> const& t, hamon::detail::overload_priority<2>)
->decltype(clock_time_conversion<DestClock, utc_clock>{}(
		clock_time_conversion<utc_clock, SourceClock>{}(t)))
{
	return clock_time_conversion<DestClock, utc_clock>{}(
		clock_time_conversion<utc_clock, SourceClock>{}(t));
}

// [time.clock.cast.fn]/1.4
template <typename DestClock, typename SourceClock, typename Duration>
auto clock_cast_impl(chrono::time_point<SourceClock, Duration> const& t, hamon::detail::overload_priority<1>)
->decltype(clock_time_conversion<DestClock, utc_clock>{}(
		clock_time_conversion<utc_clock, system_clock>{}(
			clock_time_conversion<system_clock, SourceClock>{}(t))))
{
	return clock_time_conversion<DestClock, utc_clock>{}(
		clock_time_conversion<utc_clock, system_clock>{}(
			clock_time_conversion<system_clock, SourceClock>{}(t)));
}

// [time.clock.cast.fn]/1.5
template <typename DestClock, typename SourceClock, typename Duration>
auto clock_cast_impl(chrono::time_point<SourceClock, Duration> const& t, hamon::detail::overload_priority<0>)
->decltype(clock_time_conversion<DestClock, system_clock>{}(
		clock_time_conversion<system_clock, utc_clock>{}(
			clock_time_conversion<utc_clock, SourceClock>{}(t))))
{
	return clock_time_conversion<DestClock, system_clock>{}(
		clock_time_conversion<system_clock, utc_clock>{}(
			clock_time_conversion<utc_clock, SourceClock>{}(t)));
}

}	// namespace detail

// 30.7.10.6 Function template clock_cast[time.clock.cast.fn]

template <typename DestClock, typename SourceClock, typename Duration>
auto clock_cast(chrono::time_point<SourceClock, Duration> const& t)
->decltype(detail::clock_cast_impl<DestClock>(t, hamon::detail::overload_priority<4>{}))
{
	return detail::clock_cast_impl<DestClock>(t, hamon::detail::overload_priority<4>{});
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_CLOCK_CAST_HPP
