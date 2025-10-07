/**
 *	@file	utc_seconds.hpp
 *
 *	@brief	utc_seconds の定義
 */

#ifndef HAMON_CHRONO_UTC_SECONDS_HPP
#define HAMON_CHRONO_UTC_SECONDS_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::utc_seconds;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/utc_time.hpp>
#include <hamon/chrono/duration.hpp>

namespace hamon {
namespace chrono {

// [time.clock.utc], class utc_clock

using utc_seconds = hamon::chrono::utc_time<hamon::chrono::seconds>;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_UTC_SECONDS_HPP
