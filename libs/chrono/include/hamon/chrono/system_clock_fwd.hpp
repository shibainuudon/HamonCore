/**
 *	@file	system_clock_fwd.hpp
 *
 *	@brief	system_clock の前方宣言
 */

#ifndef HAMON_CHRONO_SYSTEM_CLOCK_FWD_HPP
#define HAMON_CHRONO_SYSTEM_CLOCK_FWD_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::system_clock;

}	// namespace chrono
}	// namespace hamon

#else

namespace hamon {
namespace chrono {

// [time.clock.system], class system_clock

class system_clock;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_SYSTEM_CLOCK_FWD_HPP
