/**
 *	@file	utc_time.hpp
 *
 *	@brief	utc_time の定義
 */

#ifndef HAMON_CHRONO_UTC_TIME_HPP
#define HAMON_CHRONO_UTC_TIME_HPP

#include <hamon/chrono/utc_time_fwd.hpp>
#include <hamon/chrono/config.hpp>

#if !defined(HAMON_USE_STD_CHRONO)

#include <hamon/chrono/duration.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string.hpp>
#include <ostream>	// basic_ostream
#include <istream>	// basic_istream

namespace hamon {
namespace chrono {

template <typename charT, typename traits, typename Duration>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, hamon::chrono::utc_time<Duration> const& t);

template <typename charT, typename traits, typename Duration, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	const charT* fmt,
	hamon::chrono::utc_time<Duration>& tp,
	hamon::basic_string<charT, traits, Alloc>* abbrev = nullptr,
	hamon::chrono::minutes* offset = nullptr);

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_UTC_TIME_HPP
