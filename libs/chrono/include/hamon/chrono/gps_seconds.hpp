/**
 *	@file	gps_seconds.hpp
 *
 *	@brief	gps_seconds の定義
 */

#ifndef HAMON_CHRONO_GPS_SECONDS_HPP
#define HAMON_CHRONO_GPS_SECONDS_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::gps_seconds;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/gps_time.hpp>
#include <hamon/chrono/duration.hpp>

namespace hamon {
namespace chrono {

// [time.clock.gps], class gps_clock

using gps_seconds = hamon::chrono::gps_time<hamon::chrono::seconds>;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_GPS_SECONDS_HPP
