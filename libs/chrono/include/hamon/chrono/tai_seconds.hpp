/**
 *	@file	tai_seconds.hpp
 *
 *	@brief	tai_seconds の定義
 */

#ifndef HAMON_CHRONO_TAI_SECONDS_HPP
#define HAMON_CHRONO_TAI_SECONDS_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::tai_seconds;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/tai_time.hpp>
#include <hamon/chrono/duration.hpp>

namespace hamon {
namespace chrono {

// [time.clock.tai], class tai_clock

using tai_seconds = hamon::chrono::tai_time<hamon::chrono::seconds>;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TAI_SECONDS_HPP
