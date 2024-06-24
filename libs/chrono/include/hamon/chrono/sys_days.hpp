/**
 *	@file	sys_days.hpp
 *
 *	@brief	sys_days の定義
 */

#ifndef HAMON_CHRONO_SYS_DAYS_HPP
#define HAMON_CHRONO_SYS_DAYS_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::sys_days;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/sys_time.hpp>
#include <hamon/chrono/duration.hpp>
#include <ostream>	// basic_ostream

namespace hamon {
namespace chrono {

// [time.clock.system], class system_clock

using sys_days = hamon::chrono::sys_time<hamon::chrono::days>;

// 29.7.2.3 Non-member functions[time.clock.system.nonmembers]
// TODO
//template <typename charT, typename traits>
//std::basic_ostream<charT, traits>&
//operator<<(std::basic_ostream<charT, traits>& os, sys_days const& dp)
//{
//	// [time.clock.system.nonmembers]/4,5
//	return os << year_month_day{dp};
//}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_SYS_DAYS_HPP


