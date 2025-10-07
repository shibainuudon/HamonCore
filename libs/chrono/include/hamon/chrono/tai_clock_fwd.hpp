/**
 *	@file	tai_clock_fwd.hpp
 *
 *	@brief	tai_clock の前方宣言
 */

#ifndef HAMON_CHRONO_TAI_CLOCK_FWD_HPP
#define HAMON_CHRONO_TAI_CLOCK_FWD_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::tai_clock;

}	// namespace chrono
}	// namespace hamon

#else

namespace hamon {
namespace chrono {

// [time.clock.tai], class tai_clock

class tai_clock;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TAI_CLOCK_FWD_HPP
