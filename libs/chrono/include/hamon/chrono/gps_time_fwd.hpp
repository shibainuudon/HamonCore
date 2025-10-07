/**
 *	@file	gps_time_fwd.hpp
 *
 *	@brief	gps_time の前方宣言
 */

#ifndef HAMON_CHRONO_GPS_TIME_FWD_HPP
#define HAMON_CHRONO_GPS_TIME_FWD_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::gps_time;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/time_point/time_point_fwd.hpp>
#include <hamon/chrono/gps_clock_fwd.hpp>

namespace hamon {
namespace chrono {

// [time.clock.gps], class gps_clock

template <typename Duration>
using gps_time = hamon::chrono::time_point<hamon::chrono::gps_clock, Duration>;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_GPS_TIME_FWD_HPP
