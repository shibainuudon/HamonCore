/**
 *	@file	leap_second_info.hpp
 *
 *	@brief	leap_second_info の定義
 */

#ifndef HAMON_CHRONO_LEAP_SECOND_INFO_HPP
#define HAMON_CHRONO_LEAP_SECOND_INFO_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::leap_second_info;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>

namespace hamon {
namespace chrono {

// [time.clock.utc], class utc_clock

struct leap_second_info
{
	bool                   is_leap_second;
	hamon::chrono::seconds elapsed;
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_LEAP_SECOND_INFO_HPP
