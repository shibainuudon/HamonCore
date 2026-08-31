/**
 *	@file	local_time.hpp
 *
 *	@brief	local_time の定義
 */

#ifndef HAMON_CHRONO_LOCAL_TIME_HPP
#define HAMON_CHRONO_LOCAL_TIME_HPP

#include <hamon/chrono/time_point.hpp>
#include <hamon/istream/basic_istream.hpp>
#include <ostream>	// basic_ostream

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
hamon::basic_istream<charT, traits>&
from_stream(
	hamon::basic_istream<charT, traits>& is,
	const charT* fmt,
	local_time<Duration>& tp,
	basic_string<charT, traits, Alloc>* abbrev = nullptr,
	minutes* offset = nullptr);
#endif

}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_LOCAL_TIME_HPP
