/**
 *	@file	file_clock.hpp
 *
 *	@brief	file_clock の定義
 */

#ifndef HAMON_CHRONO_FILE_CLOCK_HPP
#define HAMON_CHRONO_FILE_CLOCK_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::file_clock;
using std::chrono::file_time;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/sys_time.hpp>
#include <hamon/chrono/detail/windows.hpp>
#include <hamon/chrono/detail/filetime_to_timespec.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/system_error/generic_category.hpp>
#include <hamon/system_error/system_error.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <ostream>	// basic_ostream
#include <istream>	// basic_istream

namespace hamon {
namespace chrono {

// [time.clock.file], type file_clock

class file_clock;

template <typename Duration>
using file_time = hamon::chrono::time_point<hamon::chrono::file_clock, Duration>;

// 30.7.6 Type file_clock[time.clock.file]

class file_clock
{
public:
	using rep        = long long;
	using period     = hamon::nano;
	using duration   = hamon::chrono::duration<rep, period>;
	using time_point = hamon::chrono::time_point<file_clock>;
	static constexpr const bool is_steady = false;

	static time_point now() noexcept
	{
		using secs  = hamon::chrono::duration<rep>;
		using nsecs = hamon::chrono::duration<rep, hamon::nano>;

#if defined(HAMON_PLATFORM_WIN32)
		FILETIME time;
		GetSystemTimeAsFileTime(&time);
		detail::TimeSpec tp = detail::filetime_to_timespec(time);
		return time_point(secs(tp.tv_sec) + hamon::chrono::duration_cast<duration>(nsecs(tp.tv_nsec)));
#else
		struct timespec tp;
		if (0 != clock_gettime(CLOCK_REALTIME, &tp))
		{
			hamon::detail::throw_system_error(errno, hamon::generic_category(), "clock_gettime(CLOCK_REALTIME) failed");
		}
		return time_point(secs(tp.tv_sec) + hamon::chrono::duration_cast<duration>(nsecs(tp.tv_nsec)));
#endif
	}

	template <typename Duration>
	static hamon::chrono::sys_time<Duration>
	to_sys(hamon::chrono::file_time<Duration> const& t)
	{
		return hamon::chrono::sys_time<Duration>(t.time_since_epoch());
	}

	template <typename Duration>
	static hamon::chrono::file_time<Duration>
	from_sys(hamon::chrono::sys_time<Duration> const& t)
	{
		return hamon::chrono::file_time<Duration>(t.time_since_epoch());
	}
};

// 30.7.6.3 Non-member functions[time.clock.file.nonmembers]

template <typename charT, typename traits, typename Duration>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, hamon::chrono::file_time<Duration> const& tp);
#if 0	// TODO
{
	// [time.clock.file.nonmembers]/1
	return os << format(os.getloc(), STATICALLY-WIDEN<charT>("{:L%F %T}"), t);
}
#endif

template <typename charT, typename traits, typename Duration, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	const charT* fmt,
	hamon::chrono::file_time<Duration>& tp,
	hamon::basic_string<charT, traits, Alloc>* abbrev = nullptr,
	hamon::chrono::minutes* offset = nullptr);

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_FILE_CLOCK_HPP
