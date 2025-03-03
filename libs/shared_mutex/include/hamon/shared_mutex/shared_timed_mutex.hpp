/**
 *	@file	shared_timed_mutex.hpp
 *
 *	@brief	shared_timed_mutex の定義
 */

#ifndef HAMON_SHARED_MUTEX_SHARED_TIMED_MUTEX_HPP
#define HAMON_SHARED_MUTEX_SHARED_TIMED_MUTEX_HPP

#include <hamon/shared_mutex/config.hpp>

#if defined(HAMON_USE_STD_SHARED_MUTEX)

#include <shared_mutex>

namespace hamon
{

using std::shared_timed_mutex;

}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/shared_mutex/detail/shared_mutex_base.hpp>

namespace hamon
{

// 32.6.4.5.2 Class shared_timed_mutex[thread.sharedtimedmutex.class]

class shared_timed_mutex
{
	hamon::detail::shared_mutex_base m_base;
public:
	shared_timed_mutex(): m_base() {}

	~shared_timed_mutex() = default;

	shared_timed_mutex(shared_timed_mutex const&) = delete;
	shared_timed_mutex& operator=(shared_timed_mutex const&) = delete;

	// exclusive ownership
	void lock()	// blocking
	{
		return m_base.lock();
	}

	bool try_lock()
	{
		return m_base.try_lock();
	}

	template <typename Rep, typename Period>
	bool try_lock_for(hamon::chrono::duration<Rep, Period> const& rel_time)
	{
		return try_lock_until(hamon::chrono::system_clock::now() + rel_time);
	}

	template <typename Clock, typename Duration>
	bool try_lock_until(hamon::chrono::time_point<Clock, Duration> const& abs_time)
	{
		return m_base.try_lock_until(abs_time);
	}

	void unlock()
	{
		return m_base.unlock();
	}

	// shared ownership
	void lock_shared()	// blocking
	{
		return m_base.lock_shared();
	}

	bool try_lock_shared()
	{
		return m_base.try_lock_shared();
	}

	template <typename Rep, typename Period>
	bool try_lock_shared_for(hamon::chrono::duration<Rep, Period> const& rel_time)
	{
		return try_lock_shared_until(hamon::chrono::system_clock::now() + rel_time);
	}

	template <typename Clock, typename Duration>
	bool try_lock_shared_until(hamon::chrono::time_point<Clock, Duration> const& abs_time)
	{
		return m_base.try_lock_shared_until(abs_time);
	}

	void unlock_shared()
	{
		return m_base.unlock_shared();
	}
};

}	// namespace hamon

#endif

#endif // HAMON_SHARED_MUTEX_SHARED_TIMED_MUTEX_HPP
