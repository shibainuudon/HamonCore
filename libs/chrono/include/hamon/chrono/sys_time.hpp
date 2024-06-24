/**
 *	@file	sys_time.hpp
 *
 *	@brief	sys_time の定義
 */

#ifndef HAMON_CHRONO_SYS_TIME_HPP
#define HAMON_CHRONO_SYS_TIME_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::sys_time;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/system_clock.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/treat_as_floating_point.hpp>
#include <hamon/chrono/detail/statically_widen.hpp>
#include <ostream>	// basic_ostream
#include <istream>	// basic_istream

namespace hamon {
namespace chrono {

// [time.clock.system], class system_clock

template <typename Duration>
using sys_time = hamon::chrono::time_point<hamon::chrono::system_clock, Duration>;

// 29.7.2.3 Non-member functions[time.clock.system.nonmembers]
// TODO
//template <typename charT, typename traits, typename Duration>
//requires (!hamon::chrono::treat_as_floating_point<typename Duration::rep>::value && Duration{1} < days{1})	// [time.clock.system.nonmembers]/1
//std::basic_ostream<charT, traits>&
//operator<<(std::basic_ostream<charT, traits>& os, sys_time<Duration> const& tp)
//{
//	// [time.clock.system.nonmembers]/2
//	return os << format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{:L%F %T}"), tp);
//}

// TODO
//template <typename charT, typename traits, typename Duration, typename Alloc = allocator<charT>>
//std::basic_istream<charT, traits>&
//from_stream(
//	std::basic_istream<charT, traits>& is, charT const* fmt,
//	sys_time<Duration>& tp,
//	basic_string<charT, traits, Alloc>* abbrev = nullptr,
//	minutes* offset = nullptr);

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_SYS_TIME_HPP


