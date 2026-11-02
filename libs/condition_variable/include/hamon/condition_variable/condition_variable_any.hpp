/**
 *	@file	condition_variable_any.hpp
 *
 *	@brief	condition_variable_any の定義
 */

#ifndef HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_ANY_HPP
#define HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_ANY_HPP

#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/condition_variable/cv_status.hpp>
#include <hamon/condition_variable/detail/rel_to_abs.hpp>
#include <hamon/condition_variable/detail/unlock_guard.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/memory/make_shared.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/mutex/adopt_lock_t.hpp>
#include <hamon/mutex/lock_guard.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/unique_lock.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/stop_callback.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

// 32.7.5 Class condition_variable_any[thread.condition.condvarany]

class condition_variable_any
{
public:
	condition_variable_any()
		: m_mut(hamon::make_shared<hamon::mutex>())
	{}

	~condition_variable_any() = default;

	condition_variable_any(condition_variable_any const&) = delete;
	condition_variable_any& operator=(condition_variable_any const&) = delete;

	void notify_one() noexcept
	{
		// [thread.condition.condvarany.general]/5
		{
			hamon::lock_guard<hamon::mutex> lx(*m_mut);
		}
		m_cv.notify_one();
	}

	void notify_all() noexcept
	{
		// [thread.condition.condvarany.general]/6
		{
			hamon::lock_guard<hamon::mutex> lx(*m_mut);
		}
		m_cv.notify_all();
	}

	// [thread.condvarany.wait], noninterruptible waits
	template <typename Lock>
	void wait(Lock& lock)
	{
		// [thread.condvarany.wait]/1
		hamon::shared_ptr<hamon::mutex> mut = m_mut;
		hamon::unique_lock<hamon::mutex> lk(*mut);
		hamon::detail::unlock_guard<Lock> unlock(lock);
		hamon::lock_guard<hamon::unique_lock<hamon::mutex> > lx(lk, hamon::adopt_lock);
		m_cv.wait(lk);
	}

	template <typename Lock, typename Predicate>
	void wait(Lock& lock, Predicate pred)
	{
		// [thread.condvarany.wait]/5
		while (!pred())
		{
			wait(lock);
		}
	}

	template <typename Lock, typename Clock, typename Duration>
	hamon::cv_status wait_until(Lock& lock, chrono::time_point<Clock, Duration> abs_time)
	{
		// [thread.condvarany.wait]/6
		hamon::shared_ptr<hamon::mutex> mut = m_mut;
		hamon::unique_lock<hamon::mutex> lk(*mut);
		hamon::detail::unlock_guard<Lock> unlock(lock);
		hamon::lock_guard<hamon::unique_lock<hamon::mutex> > lx(lk, hamon::adopt_lock);
		return m_cv.wait_until(lk, abs_time);
	}

	template <typename Lock, typename Clock, typename Duration, typename Predicate>
	bool wait_until(Lock& lock, chrono::time_point<Clock, Duration> abs_time, Predicate pred)
	{
		// [thread.condvarany.wait]/16
		while (!pred())
		{
			if (wait_until(lock, abs_time) == cv_status::timeout)
			{
				return pred();
			}
		}
		return true;
	}

	template <typename Lock, typename Rep, typename Period>
	hamon::cv_status wait_for(Lock& lock, chrono::duration<Rep, Period> rel_time)
	{
		// [thread.condvarany.wait]/11
		return wait_until(lock, hamon::detail::rel_to_abs(rel_time));
	}

	template <typename Lock, typename Rep, typename Period, typename Predicate>
	bool wait_for(Lock& lock, chrono::duration<Rep, Period> rel_time, Predicate pred)
	{
		// [thread.condvarany.wait]/19
		return wait_until(lock, hamon::detail::rel_to_abs(rel_time), hamon::move(pred));
	}

	// [thread.condvarany.intwait], interruptible waits
	template <typename Lock, typename Predicate>
	bool wait(Lock& lock, hamon::stop_token stoken, Predicate pred)
	{
		if (stoken.stop_requested())
		{
			return pred();
		}

		// Per https://eel.is/c++draft/thread.condition.condvarany#general-note-2,
		// we do need to take a copy of the shared pointer m_mut
		// This ensures that a thread can call the destructor immediately after calling
		// notify_all, without waiting all the wait calls.
		// A thread can also safely call the destructor immediately after calling
		// request_stop, as the call to request_stop would evaluate the callback,
		// which accesses the internal condition variable, immediately on the same thread.
		// In this situation, it is OK even without copying a shared ownership the internal
		// condition variable. However, this needs the evaluation of stop_callback to
		// happen-before the destruction.
		// The spec only says "Only the notification to unblock the wait needs to happen
		// before destruction". To make this work, we need to copy the shared ownership of
		// the internal condition variable inside this function, which is not possible
		// with the current ABI.
		hamon::shared_ptr<hamon::mutex> mut = m_mut;

		auto f = [this] { notify_all(); };
		hamon::stop_callback<decltype(f)> cb(stoken, f);

		while (true)
		{
			if (pred())
			{
				return true;
			}

			// We need to take the internal lock before checking stop_requested,
			// so that the notification cannot come in between the stop_requested
			// check and entering the wait.
			// Note that the stop_callback takes the same internal lock before notifying
			hamon::unique_lock<hamon::mutex> internal_lock(*mut);
			if (stoken.stop_requested())
			{
				break;
			}

			hamon::detail::unlock_guard<Lock> unlock(lock);
			hamon::unique_lock<hamon::mutex> internal_lock2(hamon::move(internal_lock)); // switch unlock order between internal_lock and lock
			m_cv.wait(internal_lock2);
		} // internal_lock2.unlock(), lock.lock()

		return pred();
	}

	template <typename Lock, typename Clock, typename Duration, typename Predicate>
	bool wait_until(Lock& lock, hamon::stop_token stoken, chrono::time_point<Clock, Duration> abs_time, Predicate pred)
	{
		if (stoken.stop_requested())
		{
			return pred();
		}

		hamon::shared_ptr<hamon::mutex> mut = m_mut;
		auto f = [this] { notify_all(); };
		hamon::stop_callback<decltype(f)> cb(stoken, f);

		while (true)
		{
			if (pred())
			{
				return true;
			}

			hamon::unique_lock<hamon::mutex> internal_lock(*mut);
			if (stoken.stop_requested())
			{
				break;
			}

			hamon::detail::unlock_guard<Lock> unlock(lock);
			hamon::unique_lock<hamon::mutex> internal_lock2(hamon::move(internal_lock)); // switch unlock order between internal_lock and lock

			if (m_cv.wait_until(internal_lock2, abs_time) == cv_status::timeout)
			{
				break;
			}
		} // internal_lock2.unlock(), lock.lock()

		return pred();
	}

	template <typename Lock, typename Rep, typename Period, typename Predicate>
	bool wait_for(Lock & lock, hamon::stop_token stoken, chrono::duration<Rep, Period> rel_time, Predicate pred)
	{
		// [thread.condvarany.intwait]/13
		return wait_until(lock, hamon::move(stoken), hamon::detail::rel_to_abs(rel_time), hamon::move(pred));
	}

private:
	condition_variable m_cv;
	hamon::shared_ptr<hamon::mutex> m_mut;
};

}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_ANY_HPP
