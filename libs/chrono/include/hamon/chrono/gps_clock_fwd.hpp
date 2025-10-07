/**
 *	@file	gps_clock_fwd.hpp
 *
 *	@brief	gps_clock の前方宣言
 */

#ifndef HAMON_CHRONO_GPS_CLOCK_FWD_HPP
#define HAMON_CHRONO_GPS_CLOCK_FWD_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::gps_clock;

}	// namespace chrono
}	// namespace hamon

#else

namespace hamon {
namespace chrono {

// [time.clock.gps], class gps_clock

class gps_clock;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_GPS_CLOCK_FWD_HPP
