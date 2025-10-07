/**
 *	@file	gps_clock.hpp
 *
 *	@brief	gps_clock の定義
 */

#ifndef HAMON_CHRONO_GPS_CLOCK_HPP
#define HAMON_CHRONO_GPS_CLOCK_HPP

#include <hamon/chrono/gps_clock_fwd.hpp>
#include <hamon/chrono/config.hpp>

#if !defined(HAMON_USE_STD_CHRONO)

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/utc_clock.hpp>
#include <hamon/chrono/utc_time_fwd.hpp>
#include <hamon/chrono/gps_time_fwd.hpp>
#include <hamon/type_traits/common_type.hpp>

namespace hamon {
namespace chrono {

// 30.7.5 Class gps_clock[time.clock.gps]

class gps_clock
{
public:
	using rep        = hamon::chrono::utc_clock::rep;
	using period     = hamon::chrono::utc_clock::period;
	using duration   = hamon::chrono::duration<rep, period>;
	using time_point = hamon::chrono::time_point<gps_clock>;
	static constexpr bool is_steady = false; // The utc_clock is not steady.

	static time_point now()
	{
		// [time.clock.gps.members]/1
		return from_utc(hamon::chrono::utc_clock::now());
	}

	template <typename Duration>
	static hamon::chrono::utc_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>
	to_utc(hamon::chrono::gps_time<Duration> const&) noexcept;

	template <typename Duration>
	static hamon::chrono::gps_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>
	from_utc(hamon::chrono::utc_time<Duration> const&) noexcept;
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_GPS_CLOCK_HPP
