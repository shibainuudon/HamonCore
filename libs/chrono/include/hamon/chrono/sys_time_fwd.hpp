/**
 *	@file	sys_time_fwd.hpp
 *
 *	@brief	sys_time の前方宣言
 */

#ifndef HAMON_CHRONO_SYS_TIME_FWD_HPP
#define HAMON_CHRONO_SYS_TIME_FWD_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::sys_time;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/system_clock_fwd.hpp>
#include <hamon/chrono/time_point/time_point_fwd.hpp>

namespace hamon {
namespace chrono {

// [time.clock.system], class system_clock

template <typename Duration>
using sys_time = hamon::chrono::time_point<hamon::chrono::system_clock, Duration>;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_SYS_TIME_FWD_HPP
