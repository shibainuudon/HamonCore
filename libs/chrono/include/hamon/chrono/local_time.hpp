/**
 *	@file	local_time.hpp
 *
 *	@brief	local_time の定義
 */

#ifndef HAMON_CHRONO_LOCAL_TIME_HPP
#define HAMON_CHRONO_LOCAL_TIME_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::local_time;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/time_point.hpp>
#include <ostream>	// basic_ostream
#include <istream>	// basic_istream

namespace hamon {
namespace chrono {

// [time.clock.local], local time
struct local_t {};

template <typename Duration>
using local_time = time_point<local_t, Duration>;

// TODO
#if 0
template <typename charT, typename traits, typename Duration>
basic_ostream<charT, traits>&
operator<<(
	basic_ostream<charT, traits>& os,
	const local_time<Duration>& tp);

template <typename charT, typename traits, typename Duration, typename Alloc = allocator<charT>>
basic_istream<charT, traits>&
from_stream(
	basic_istream<charT, traits>& is,
	const charT* fmt,
	local_time<Duration>& tp,
	basic_string<charT, traits, Alloc>* abbrev = nullptr,
	minutes* offset = nullptr);
#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_LOCAL_TIME_HPP
