/**
 *	@file	steady_clock.hpp
 *
 *	@brief	steady_clock の定義
 */

#ifndef HAMON_CHRONO_STEADY_CLOCK_HPP
#define HAMON_CHRONO_STEADY_CLOCK_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::steady_clock;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/ratio.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_PLATFORM_WIN32)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace hamon {
namespace chrono {

// 30.7.7 Class steady_clock[time.clock.steady]
class steady_clock
{
public:
	using rep        = hamon::int64_t;
	using period     = hamon::ratio<1, 1000000000>;	// nano
	using duration   = hamon::chrono::duration<rep, period>;
	using time_point = hamon::chrono::time_point<steady_clock>;
	static constexpr bool is_steady = true;

private:
#if defined(HAMON_PLATFORM_WIN32)
	static LARGE_INTEGER query_performance_frequency()
	{
		LARGE_INTEGER val;
		(void)QueryPerformanceFrequency(&val);
		return val;
	}

	static nanoseconds now_impl() noexcept
	{
		static const LARGE_INTEGER freq = query_performance_frequency();

		LARGE_INTEGER counter;
		(void)QueryPerformanceCounter(&counter);

		using nano = hamon::ratio<1, 1000000000>;
		auto seconds   = counter.QuadPart / freq.QuadPart;
		auto fractions = counter.QuadPart % freq.QuadPart;
		auto dur       = seconds * nano::den + fractions * nano::den / freq.QuadPart;

		return nanoseconds(dur);
	}
#else
	static nanoseconds now_impl() noexcept
	{
		struct timespec tp;
		if (0 != clock_gettime(CLOCK_MONOTONIC_RAW, &tp))
		{
			//hamon::detail::throw_system_error(errno, "clock_gettime(CLOCK_MONOTONIC_RAW) failed");
		}
		return seconds(tp.tv_sec) + nanoseconds(tp.tv_nsec);
	}
#endif

public:
	static time_point now() noexcept
	{
		return time_point(duration_cast<duration>(now_impl()));
	}
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_STEADY_CLOCK_HPP
