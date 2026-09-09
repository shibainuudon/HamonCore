/**
 *	@file	this_thread.hpp
 *
 *	@brief	this_thread の定義
 */

#ifndef HAMON_THREAD_THIS_THREAD_HPP
#define HAMON_THREAD_THIS_THREAD_HPP

#include <hamon/thread/thread.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>

namespace hamon
{

// 32.4.5 Namespace this_thread[thread.thread.this]

namespace this_thread
{

thread::id get_id() noexcept;

void yield() noexcept;

template <typename Clock, typename Duration>
void sleep_until(chrono::time_point<Clock, Duration> const& abs_time);

template <typename Rep, typename Period>
void sleep_for(chrono::duration<Rep, Period> const& rel_time);

}	// namespace this_thread

}	// namespace hamon

#endif // HAMON_THREAD_THIS_THREAD_HPP
