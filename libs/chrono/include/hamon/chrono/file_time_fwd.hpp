/**
 *	@file	file_time_fwd.hpp
 *
 *	@brief	file_time の前方宣言
 */

#ifndef HAMON_CHRONO_FILE_TIME_FWD_HPP
#define HAMON_CHRONO_FILE_TIME_FWD_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::file_time;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/time_point/time_point_fwd.hpp>
#include <hamon/chrono/file_clock_fwd.hpp>

namespace hamon {
namespace chrono {

// [time.clock.file], type file_clock

template <typename Duration>
using file_time = hamon::chrono::time_point<hamon::chrono::file_clock, Duration>;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_FILE_TIME_FWD_HPP
