/**
 *	@file	time_point_fwd.hpp
 *
 *	@brief	time_point の前方宣言
 */

#ifndef HAMON_CHRONO_TIME_POINT_TIME_POINT_FWD_HPP
#define HAMON_CHRONO_TIME_POINT_TIME_POINT_FWD_HPP

namespace hamon {
namespace chrono {

template <typename Clock, typename Duration = typename Clock::duration>
class time_point;

}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_TIME_POINT_TIME_POINT_FWD_HPP
