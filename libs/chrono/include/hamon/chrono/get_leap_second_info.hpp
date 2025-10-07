/**
 *	@file	get_leap_second_info.hpp
 *
 *	@brief	get_leap_second_info の定義
 */

#ifndef HAMON_CHRONO_GET_LEAP_SECOND_INFO_HPP
#define HAMON_CHRONO_GET_LEAP_SECOND_INFO_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::get_leap_second_info;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/leap_second_info.hpp>
#include <hamon/chrono/utc_time.hpp>

namespace hamon {
namespace chrono {

// [time.clock.utc], class utc_clock

template <typename Duration>
hamon::chrono::leap_second_info
get_leap_second_info(hamon::chrono::utc_time<Duration> const& ut);

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_GET_LEAP_SECOND_INFO_HPP
