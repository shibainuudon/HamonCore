/**
 *	@file	file_clock_fwd.hpp
 *
 *	@brief	file_clock の前方宣言
 */

#ifndef HAMON_CHRONO_FILE_CLOCK_FWD_HPP
#define HAMON_CHRONO_FILE_CLOCK_FWD_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::file_clock;

}	// namespace chrono
}	// namespace hamon

#else

namespace hamon {
namespace chrono {

// [time.clock.file], type file_clock

class file_clock;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_FILE_CLOCK_FWD_HPP
