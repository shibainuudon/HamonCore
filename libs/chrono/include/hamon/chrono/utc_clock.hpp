/**
 *	@file	utc_clock.hpp
 *
 *	@brief	utc_clock の定義
 */

#ifndef HAMON_CHRONO_UTC_CLOCK_HPP
#define HAMON_CHRONO_UTC_CLOCK_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::utc_clock;
using std::chrono::utc_time;
using std::chrono::utc_seconds;
using std::chrono::leap_second_info;
using std::chrono::get_leap_second_info;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/chrono/get_tzdb.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string.hpp>
#include <ostream>	// basic_ostream
#include <istream>	// basic_istream

namespace hamon {
namespace chrono {

// [time.clock.utc], class utc_clock

class utc_clock;

template <typename Duration>
using utc_time  = hamon::chrono::time_point<hamon::chrono::utc_clock, Duration>;

using utc_seconds = hamon::chrono::utc_time<hamon::chrono::seconds>;

struct leap_second_info;

template <typename Duration>
leap_second_info get_leap_second_info(utc_time<Duration> const& ut);

// 30.7.3 Class utc_clock[time.clock.utc]

class utc_clock
{
public:
	using rep        = hamon::chrono::system_clock::rep;
	using period     = hamon::chrono::system_clock::period;
	using duration   = hamon::chrono::duration<rep, period>;
	using time_point = hamon::chrono::time_point<utc_clock>;
	static constexpr bool is_steady = false; // The system_clock is not steady.

	static time_point now()
	{
		// [time.clock.utc.members]/1
		return from_sys(hamon::chrono::system_clock::now());
	}

	template <typename Duration>
	static hamon::chrono::sys_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>
	to_sys(hamon::chrono::utc_time<Duration> const& t)
	{
		// [time.clock.utc.members]/2
		using D = hamon::common_type_t<Duration, hamon::chrono::seconds>;
		auto info = hamon::chrono::get_leap_second_info(t);

		using R = hamon::chrono::sys_time<D>;
		R result{ t.time_since_epoch() - info.elapsed };
		if (info.is_leap_second)
		{
			return hamon::chrono::floor<hamon::chrono::seconds>(result) + hamon::chrono::seconds{1} - D{1};
		}

		return result;
	}

	template <typename Duration>
	static hamon::chrono::utc_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>
	from_sys(hamon::chrono::sys_time<Duration> const& t)
	{
		// [time.clock.utc.members]/3
		using R = hamon::chrono::utc_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>;
		auto const& tzdb = hamon::chrono::get_tzdb();
		R result{ t.time_since_epoch() };
		for (const auto& leap_second : tzdb.leap_seconds)
		{
			if (leap_second > t)
			{
				return result;
			}

			result += leap_second.value();
		}
		return result;
	}
};

// 30.7.3.3 Non-member functions[time.clock.utc.nonmembers]

template <typename charT, typename traits, typename Duration>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, hamon::chrono::utc_time<Duration> const& t);
#if 0	// TODO
{
	// [time.clock.utc.nonmembers]/1
	return os << format(os.getloc(), STATICALLY-WIDEN<charT>("{:L%F %T}"), t);
}
#endif

template <typename charT, typename traits, typename Duration, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	const charT* fmt,
	hamon::chrono::utc_time<Duration>& tp,
	hamon::basic_string<charT, traits, Alloc>* abbrev = nullptr,
	hamon::chrono::minutes* offset = nullptr);

// [time.clock.utc.nonmembers]/5
struct leap_second_info
{
	bool                   is_leap_second;
	hamon::chrono::seconds elapsed;
};

template <typename Duration>
hamon::chrono::leap_second_info
get_leap_second_info(hamon::chrono::utc_time<Duration> const& ut)
{
	// [time.clock.utc.nonmembers]/6
	auto const& tzdb = hamon::chrono::get_tzdb();
	if (HAMON_UNLIKELY(tzdb.leap_seconds.empty()))
	{
		return { false, hamon::chrono::seconds{0} };
	}

	hamon::chrono::sys_seconds sys{ hamon::chrono::floor<hamon::chrono::seconds>(ut).time_since_epoch() };
	hamon::chrono::seconds elapsed{ 0 };
	for (auto const& leap_second : tzdb.leap_seconds)
	{
		if (sys == leap_second.date() + elapsed)
		{
			return { leap_second.value() > hamon::chrono::seconds{0}, elapsed + leap_second.value() };
		}

		if (sys < leap_second.date() + elapsed)
		{
			return { false, elapsed };
		}

		elapsed += leap_second.value();
	}

	return { false, elapsed };
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_UTC_CLOCK_HPP
