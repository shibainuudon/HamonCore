/**
 *	@file	utc_clock_fwd.hpp
 *
 *	@brief	utc_clock の前方宣言
 */

#ifndef HAMON_CHRONO_UTC_CLOCK_FWD_HPP
#define HAMON_CHRONO_UTC_CLOCK_FWD_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::utc_clock;

}	// namespace chrono
}	// namespace hamon

#else

namespace hamon {
namespace chrono {

// [time.clock.utc], class utc_clock

class utc_clock;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_UTC_CLOCK_FWD_HPP
