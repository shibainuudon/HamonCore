/**
 *	@file	this_thread.hpp
 *
 *	@brief	this_thread の定義
 */

#ifndef HAMON_THREAD_THIS_THREAD_HPP
#define HAMON_THREAD_THIS_THREAD_HPP

#include <hamon/thread/thread.hpp>
#include <hamon/thread/detail/thread_impl.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/is_clock.hpp>
#include <hamon/cstdint/uint64_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.4.5 Namespace this_thread[thread.thread.this]

namespace this_thread
{

HAMON_NODISCARD	// nodiscard as an extension
inline thread::id get_id() noexcept
{
	// [thread.thread.this]/1
	return hamon::detail::thread_id_access::create(
		hamon::detail::thread_get_current_id());
}

inline void yield() noexcept
{
	// [thread.thread.this]/2
	hamon::detail::thread_yield();
}

template <typename Rep, typename Period>
void sleep_for(chrono::duration<Rep, Period> const& rel_time)
{
	if (rel_time <= rel_time.zero())
	{
		return;
	}

	// [thread.thread.this]/7
	auto ns = chrono::ceil<chrono::nanoseconds>(rel_time);
	hamon::detail::thread_sleep_for(static_cast<hamon::uint64_t>(ns.count()));
}

template <typename Clock, typename Duration>
void sleep_until(chrono::time_point<Clock, Duration> const& abs_time)
{
	// [thread.req.paramname]/1
	static_assert(chrono::is_clock_v<Clock>, "");

	// [thread.thread.this]/4
	auto now = Clock::now();
	if (Clock::is_steady)
	{
		if (now < abs_time)
		{
			hamon::this_thread::sleep_for(abs_time - now);
		}
	}
	else
	{
		while (now < abs_time)
		{
			hamon::this_thread::sleep_for(abs_time - now);
			now = Clock::now();
		}
	}
}

}	// namespace this_thread

}	// namespace hamon

#endif // HAMON_THREAD_THIS_THREAD_HPP
