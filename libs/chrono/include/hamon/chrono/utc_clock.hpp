/**
 *	@file	utc_clock.hpp
 *
 *	@brief	utc_clock の定義
 */

#ifndef HAMON_CHRONO_UTC_CLOCK_HPP
#define HAMON_CHRONO_UTC_CLOCK_HPP

#include <hamon/chrono/utc_clock_fwd.hpp>
#include <hamon/chrono/config.hpp>

#if !defined(HAMON_USE_STD_CHRONO)

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/chrono/sys_time_fwd.hpp>
#include <hamon/chrono/utc_time_fwd.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits/common_type.hpp>

namespace hamon {
namespace chrono {

// 30.7.3 Class utc_clock[time.clock.utc]

class utc_clock
{
public:
	using rep        = hamon::chrono::system_clock::rep;
	using period     = hamon::chrono::system_clock::period;
	using duration   = hamon::chrono::duration<rep, period>;
	using time_point = hamon::chrono::time_point<utc_clock>;
	static constexpr bool is_steady = false; // The system_clock is not steady.

	static time_point now()
	{
		// [time.clock.utc.members]/1
		return from_sys(hamon::chrono::system_clock::now());
	}

	template <typename Duration>
	static hamon::chrono::sys_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>
	to_sys(hamon::chrono::utc_time<Duration> const& t);

	template <typename Duration>
	static hamon::chrono::utc_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>
	from_sys(hamon::chrono::sys_time<Duration> const& t);
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_UTC_CLOCK_HPP
