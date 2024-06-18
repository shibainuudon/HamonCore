/**
 *	@file	duration_fwd.hpp
 *
 *	@brief	duration の前方宣言
 */

#ifndef HAMON_CHRONO_DURATION_DURATION_FWD_HPP
#define HAMON_CHRONO_DURATION_DURATION_FWD_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::duration;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/ratio/ratio.hpp>

namespace hamon {
namespace chrono {

// [time.duration], class template duration
template <typename Rep, typename Period = hamon::ratio<1>>
class duration;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_DURATION_DURATION_FWD_HPP
