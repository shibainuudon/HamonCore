/**
 *	@file	high_resolution_clock.hpp
 *
 *	@brief	high_resolution_clock の定義
 */

#ifndef HAMON_CHRONO_HIGH_RESOLUTION_CLOCK_HPP
#define HAMON_CHRONO_HIGH_RESOLUTION_CLOCK_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::high_resolution_clock;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/steady_clock.hpp>

namespace hamon {
namespace chrono {

// 30.7.8 Class high_resolution_clock[time.clock.hires]

#if 1
using high_resolution_clock = hamon::chrono::steady_clock;
#else
using high_resolution_clock = hamon::chrono::system_clock;
#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_HIGH_RESOLUTION_CLOCK_HPP
