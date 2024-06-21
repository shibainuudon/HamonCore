/**
 *	@file	time_point_fwd.hpp
 *
 *	@brief	time_point の前方宣言
 */

#ifndef HAMON_CHRONO_TIME_POINT_TIME_POINT_FWD_HPP
#define HAMON_CHRONO_TIME_POINT_TIME_POINT_FWD_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::time_point;

}	// namespace chrono
}	// namespace hamon

#else

namespace hamon {
namespace chrono {

template <typename Clock, typename Duration = typename Clock::duration>
class time_point;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TIME_POINT_TIME_POINT_FWD_HPP
