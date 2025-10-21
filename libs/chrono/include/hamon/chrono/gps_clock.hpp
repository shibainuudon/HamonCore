/**
 *	@file	gps_clock.hpp
 *
 *	@brief	gps_clock の定義
 */

#ifndef HAMON_CHRONO_GPS_CLOCK_HPP
#define HAMON_CHRONO_GPS_CLOCK_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::gps_clock;
using std::chrono::gps_time;
using std::chrono::gps_seconds;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/utc_clock.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string.hpp>
#include <ostream>	// basic_ostream
#include <istream>	// basic_istream

namespace hamon {
namespace chrono {

// [time.clock.gps], class gps_clock

class gps_clock;

template <typename Duration>
using gps_time = hamon::chrono::time_point<hamon::chrono::gps_clock, Duration>;

using gps_seconds = hamon::chrono::gps_time<hamon::chrono::seconds>;

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
	to_utc(hamon::chrono::gps_time<Duration> const& t) noexcept
	{
		// [time.clock.gps.members]/2
		return hamon::chrono::utc_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>{t.time_since_epoch()} + hamon::chrono::seconds{315964809};
	}

	template <typename Duration>
	static hamon::chrono::gps_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>
	from_utc(hamon::chrono::utc_time<Duration> const& t) noexcept
	{
		// [time.clock.gps.members]/3
		return hamon::chrono::gps_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>{t.time_since_epoch()} - hamon::chrono::seconds{315964809};
	}
};

// 30.7.5.3 Non-member functions[time.clock.gps.nonmembers]

template <typename charT, typename traits, typename Duration>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, hamon::chrono::gps_time<Duration> const& t);
#if 0	// TODO
{
	// [time.clock.gps.nonmembers]/1
	return os << format(os.getloc(), STATICALLY-WIDEN<charT>("{:L%F %T}"), t);
}
#endif

template <typename charT, typename traits, typename Duration, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	const charT* fmt,
	hamon::chrono::gps_time<Duration>& tp,
	hamon::basic_string<charT, traits, Alloc>* abbrev = nullptr,
	hamon::chrono::minutes* offset = nullptr);

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_GPS_CLOCK_HPP
