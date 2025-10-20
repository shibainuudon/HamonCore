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
using std::chrono::sys_time;
using std::chrono::sys_seconds;
using std::chrono::sys_days;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/treat_as_floating_point.hpp>
#include <hamon/chrono/detail/windows.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/ratio.hpp>
#include <hamon/system_error/generic_category.hpp>
#include <hamon/system_error/system_error.hpp>
#include <hamon/config.hpp>
#include <ctime>
#include <ostream>	// basic_ostream
#include <istream>	// basic_istream

namespace hamon {
namespace chrono {

// [time.clock.system], class system_clock

class system_clock;

template <typename Duration>
using sys_time = hamon::chrono::time_point<hamon::chrono::system_clock, Duration>;

using sys_seconds = hamon::chrono::sys_time<hamon::chrono::seconds>;
using sys_days = hamon::chrono::sys_time<hamon::chrono::days>;

// 30.7.2 Class system_clock[time.clock.system]

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
			hamon::detail::throw_system_error(errno, hamon::generic_category(), "clock_gettime(CLOCK_REALTIME) failed");
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

// 30.7.2.3 Non-member functions[time.clock.system.nonmembers]

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
//template <typename charT, typename traits>
//std::basic_ostream<charT, traits>&
//operator<<(std::basic_ostream<charT, traits>& os, sys_days const& dp)
//{
//	// [time.clock.system.nonmembers]/4,5
//	return os << year_month_day{dp};
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

#endif // HAMON_CHRONO_SYSTEM_CLOCK_HPP
