/**
 *	@file	system_clock.hpp
 *
 *	@brief	system_clock の定義
 */

#ifndef HAMON_CHRONO_SYSTEM_CLOCK_HPP
#define HAMON_CHRONO_SYSTEM_CLOCK_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::system_clock;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/detail/windows.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/ratio.hpp>
#include <hamon/config.hpp>
#include <ctime>

namespace hamon {
namespace chrono {

// 29.7.2 Class system_clock[time.clock.system]

class system_clock
{
public:
	using rep        = hamon::int64_t;
	using period     = hamon::ratio<1, 10000000>; // 100 nanoseconds
	using duration   = hamon::chrono::duration<rep, period>;
	using time_point = hamon::chrono::time_point<system_clock>;
	static constexpr bool is_steady = false;

	static_assert(duration::min() < duration::zero(), "[time.clock.system.members]/1");

private:
#if defined(HAMON_PLATFORM_WIN32)
	static nanoseconds now_impl() noexcept
	{
		// FILETIME is in 100ns units
		using filetime_duration = hamon::chrono::duration<hamon::int64_t, hamon::ratio<1, 10000000>>;

		// The Windows epoch is Jan 1 1601, the Unix epoch Jan 1 1970.
		static constexpr const seconds nt_to_unix_epoch {11644473600};

		FILETIME ft;
		GetSystemTimePreciseAsFileTime(&ft);
		filetime_duration d
		{
			(static_cast<hamon::int64_t>(ft.dwHighDateTime) << 32) |
			 static_cast<hamon::int64_t>(ft.dwLowDateTime)
		};
		return d - nt_to_unix_epoch;
	}
#else
	static nanoseconds now_impl() noexcept
	{
		struct timespec tp;
		if (0 != clock_gettime(CLOCK_REALTIME, &tp))
		{
			//__throw_system_error(errno, "clock_gettime(CLOCK_REALTIME) failed");
		}
		return seconds(tp.tv_sec) + nanoseconds(tp.tv_nsec);
	}
#endif

public:
	static time_point now() noexcept
	{
		return time_point(duration_cast<duration>(now_impl()));
	}

	// mapping to/from C type time_t
	static std::time_t to_time_t(time_point const& t) noexcept
	{
		return duration_cast<hamon::chrono::seconds>(t.time_since_epoch()).count();
	}

	static time_point from_time_t(std::time_t t) noexcept
	{
		return time_point{hamon::chrono::seconds{t}};
	}
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_SYSTEM_CLOCK_HPP
