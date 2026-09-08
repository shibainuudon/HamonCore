/**
 *	@file	timed_mutex.hpp
 *
 *	@brief	timed_mutex の定義
 */

#ifndef HAMON_MUTEX_TIMED_MUTEX_HPP
#define HAMON_MUTEX_TIMED_MUTEX_HPP

#include <mutex>

namespace hamon
{

using std::timed_mutex;

#if 0	// TODO

// 32.6.4.3.2 Class timed_mutex[thread.timedmutex.class]

class timed_mutex
{
public:
	timed_mutex();
	~timed_mutex();

	timed_mutex(const timed_mutex&) = delete;
	timed_mutex& operator=(const timed_mutex&) = delete;

	void lock();    // blocking
	bool try_lock();
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

#endif // HAMON_MUTEX_TIMED_MUTEX_HPP
