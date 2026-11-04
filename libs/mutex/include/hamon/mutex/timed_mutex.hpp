/**
 *	@file	timed_mutex.hpp
 *
 *	@brief	timed_mutex の定義
 */

#ifndef HAMON_MUTEX_TIMED_MUTEX_HPP
#define HAMON_MUTEX_TIMED_MUTEX_HPP

#include <hamon/mutex/lock_guard.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/try_to_lock_t.hpp>
#include <hamon/mutex/unique_lock.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/steady_clock.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/condition_variable/cv_status.hpp>

namespace hamon
{

// 32.6.4.3.2 Class timed_mutex[thread.timedmutex.class]

class timed_mutex
{
public:
	timed_mutex()
		: m_locked(false)
	{
	}

	~timed_mutex()
	{
		hamon::lock_guard<hamon::mutex> lk(m_mut);
	}

	timed_mutex(timed_mutex const&) = delete;
	timed_mutex& operator=(timed_mutex const&) = delete;

	void lock()	// blocking
	{
		hamon::unique_lock<hamon::mutex> lk(m_mut);
		while (m_locked)
		{
			m_cv.wait(lk);
		}

		m_locked = true;
	}

	bool try_lock()
	{
		hamon::unique_lock<hamon::mutex> lk(m_mut, hamon::try_to_lock);
		if (lk.owns_lock() && !m_locked)
		{
			m_locked = true;
			return true;
		}

		return false;
	}

	template <typename Rep, typename Period>
	bool try_lock_for(chrono::duration<Rep, Period> const& rel_time)
	{
		return try_lock_until(chrono::steady_clock::now() + rel_time);
	}

	template <typename Clock, typename Duration>
	bool try_lock_until(chrono::time_point<Clock, Duration> const& abs_time)
	{
		hamon::unique_lock<hamon::mutex> lk(m_mut);
		bool no_timeout = Clock::now() < abs_time;
		while (no_timeout && m_locked)
		{
			no_timeout = m_cv.wait_until(lk, abs_time) == hamon::cv_status::no_timeout;
		}

		if (!m_locked)
		{
			m_locked = true;
			return true;
		}

		return false;
	}

	void unlock()
	{
		hamon::lock_guard<hamon::mutex> lk(m_mut);
		m_locked = false;
		m_cv.notify_one();
	}

	using native_handle_type = hamon::mutex::native_handle_type;	// see [thread.req.native]

	native_handle_type native_handle()	// see [thread.req.native]
	{
		return m_mut.native_handle();
	}

private:
	hamon::mutex m_mut;
	hamon::condition_variable m_cv;
	bool m_locked;
};

}	// namespace hamon

#endif // HAMON_MUTEX_TIMED_MUTEX_HPP
