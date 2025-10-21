/**
 *	@file	tai_clock.hpp
 *
 *	@brief	tai_clock の定義
 */

#ifndef HAMON_CHRONO_TAI_CLOCK_HPP
#define HAMON_CHRONO_TAI_CLOCK_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::tai_clock;
using std::chrono::tai_time;
using std::chrono::tai_seconds;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/utc_clock.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string.hpp>
#include <ostream>	// basic_ostream
#include <istream>	// basic_istream

namespace hamon {
namespace chrono {

// [time.clock.tai], class tai_clock

class tai_clock;

template <typename Duration>
using tai_time  = hamon::chrono::time_point<hamon::chrono::tai_clock, Duration>;

using tai_seconds = hamon::chrono::tai_time<hamon::chrono::seconds>;

// 30.7.4 Class tai_clock[time.clock.tai]

class tai_clock
{
public:
	using rep        = hamon::chrono::utc_clock::rep;
	using period     = hamon::chrono::utc_clock::period;
	using duration   = hamon::chrono::duration<rep, period>;
	using time_point = hamon::chrono::time_point<tai_clock>;
	static constexpr bool is_steady = false; // The utc_clock is not steady.

	static time_point now()
	{
		// [time.clock.tai.members]/1
		return from_utc(hamon::chrono::utc_clock::now());
	}

	template <typename Duration>
	static hamon::chrono::utc_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>
	to_utc(hamon::chrono::tai_time<Duration> const& t) noexcept
	{
		// [time.clock.tai.members]/2
		return hamon::chrono::utc_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>{t.time_since_epoch()} - hamon::chrono::seconds{378691210};
	}

	template <typename Duration>
	static hamon::chrono::tai_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>
	from_utc(hamon::chrono::utc_time<Duration> const& t) noexcept
	{
		// [time.clock.tai.members]/3
		return hamon::chrono::tai_time<hamon::common_type_t<Duration, hamon::chrono::seconds>>{t.time_since_epoch()} + hamon::chrono::seconds{378691210};
	}
};

// 30.7.4.3 Non-member functions[time.clock.tai.nonmembers]

template <typename charT, typename traits, typename Duration>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, hamon::chrono::tai_time<Duration> const& t);
#if 0	// TODO
{
	// [time.clock.tai.nonmembers]/1
	return os << format(os.getloc(), STATICALLY-WIDEN<charT>("{:L%F %T}"), t);
}
#endif

template <typename charT, typename traits, typename Duration, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	const charT* fmt,
	hamon::chrono::tai_time<Duration>& tp,
	hamon::basic_string<charT, traits, Alloc>* abbrev = nullptr,
	hamon::chrono::minutes* offset = nullptr);

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TAI_CLOCK_HPP
