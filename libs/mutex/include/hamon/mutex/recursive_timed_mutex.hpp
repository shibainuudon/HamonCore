/**
 *	@file	recursive_timed_mutex.hpp
 *
 *	@brief	recursive_timed_mutex の定義
 */

#ifndef HAMON_MUTEX_RECURSIVE_TIMED_MUTEX_HPP
#define HAMON_MUTEX_RECURSIVE_TIMED_MUTEX_HPP

#include <hamon/mutex/lock_guard.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/try_to_lock_t.hpp>
#include <hamon/mutex/unique_lock.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/steady_clock.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/condition_variable/cv_status.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/limits.hpp>
#include <hamon/system_error.hpp>
#include <hamon/thread/this_thread.hpp>
#include <hamon/thread/thread.hpp>

namespace hamon
{

// 32.6.4.3.3 Class recursive_timed_mutex[thread.timedmutex.recursive]

class recursive_timed_mutex
{
public:
	recursive_timed_mutex()
		: m_count(0)
		, m_id{}
	{
	}

	~recursive_timed_mutex()
	{
		hamon::lock_guard<hamon::mutex> lk(m_mut);
	}

	recursive_timed_mutex(recursive_timed_mutex const&) = delete;
	recursive_timed_mutex& operator=(recursive_timed_mutex const&) = delete;

	void lock()	// blocking
	{
		auto id = hamon::this_thread::get_id();
		hamon::unique_lock<hamon::mutex> lk(m_mut);
		if (id == m_id)
		{
			if (m_count == hamon::numeric_limits<hamon::size_t>::max())
			{
				hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::resource_unavailable_try_again));
			}

			++m_count;
			return;
		}

		while (m_count != 0)
		{
			m_cv.wait(lk);
		}

		m_count = 1;
		m_id = id;
	}

	bool try_lock() noexcept
	{
		auto id = hamon::this_thread::get_id();
		hamon::unique_lock<hamon::mutex> lk(m_mut, hamon::try_to_lock);
		if (lk.owns_lock() && (m_count == 0 || id == m_id))
		{
			if (m_count == hamon::numeric_limits<hamon::size_t>::max())
			{
				return false;
			}

			++m_count;
			m_id = id;
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
		auto id = hamon::this_thread::get_id();
		hamon::unique_lock<hamon::mutex> lk(m_mut);
		if (id == m_id)
		{
			if (m_count == hamon::numeric_limits<hamon::size_t>::max())
			{
				return false;
			}

			++m_count;
			return true;
		}

		bool no_timeout = Clock::now() < abs_time;
		while (no_timeout && m_count != 0)
		{
			no_timeout = m_cv.wait_until(lk, abs_time) == hamon::cv_status::no_timeout;
		}

		if (m_count == 0)
		{
			m_count = 1;
			m_id = id;
			return true;
		}

		return false;
	}

	void unlock()
	{
		hamon::unique_lock<hamon::mutex> lk(m_mut);
		if (--m_count == 0)
		{
			m_id = hamon::thread::id{};
			lk.unlock();
			m_cv.notify_one();
		}
	}

	using native_handle_type = hamon::mutex::native_handle_type;	// see [thread.req.native]

	native_handle_type native_handle()	// see [thread.req.native]
	{
		return m_mut.native_handle();
	}

private:
	hamon::mutex m_mut;
	hamon::condition_variable m_cv;
	hamon::size_t m_count;
	hamon::thread::id m_id;
};

}	// namespace hamon

#endif // HAMON_MUTEX_RECURSIVE_TIMED_MUTEX_HPP
