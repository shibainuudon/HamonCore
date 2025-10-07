/**
 *	@file	file_clock.hpp
 *
 *	@brief	file_clock の定義
 */

#ifndef HAMON_CHRONO_FILE_CLOCK_HPP
#define HAMON_CHRONO_FILE_CLOCK_HPP

#include <hamon/chrono/file_clock_fwd.hpp>
#include <hamon/chrono/config.hpp>

#if !defined(HAMON_USE_STD_CHRONO)

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/sys_time.hpp>
#include <hamon/chrono/file_time.hpp>

namespace hamon {
namespace chrono {

// 30.7.6 Type file_clock[time.clock.file]

class file_clock
{
public:
	using rep        = long long;
	using period     = hamon::nano;
	using duration   = hamon::chrono::duration<rep, period>;
	using time_point = hamon::chrono::time_point<file_clock>;
	static constexpr const bool is_steady = false;

	static time_point now() noexcept;

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

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_FILE_CLOCK_HPP
