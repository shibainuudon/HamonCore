/**
 *	@file	recursive_timed_mutex.hpp
 *
 *	@brief	recursive_timed_mutex の定義
 */

#ifndef HAMON_MUTEX_RECURSIVE_TIMED_MUTEX_HPP
#define HAMON_MUTEX_RECURSIVE_TIMED_MUTEX_HPP

#include <mutex>

namespace hamon
{

using std::recursive_timed_mutex;

#if 0	// TODO

// 32.6.4.3.3 Class recursive_timed_mutex[thread.timedmutex.recursive]

class recursive_timed_mutex
{
public:
	recursive_timed_mutex();
	~recursive_timed_mutex();

	recursive_timed_mutex(const recursive_timed_mutex&) = delete;
	recursive_timed_mutex& operator=(const recursive_timed_mutex&) = delete;

	void lock();    // blocking
	bool try_lock() noexcept;
	template<class Rep, class Period>
	bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
	template<class Clock, class Duration>
	bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);
	void unlock();

	using native_handle_type = implementation-defined;          // see [thread.req.native]
	native_handle_type native_handle();                         // see [thread.req.native]
};

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_RECURSIVE_TIMED_MUTEX_HPP
