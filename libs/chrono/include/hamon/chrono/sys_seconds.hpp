/**
 *	@file	sys_seconds.hpp
 *
 *	@brief	sys_seconds の定義
 */

#ifndef HAMON_CHRONO_SYS_SECONDS_HPP
#define HAMON_CHRONO_SYS_SECONDS_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::sys_seconds;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/sys_time.hpp>
#include <hamon/chrono/duration.hpp>

namespace hamon {
namespace chrono {

// [time.clock.system], class system_clock

using sys_seconds = hamon::chrono::sys_time<hamon::chrono::seconds>;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_SYS_SECONDS_HPP


