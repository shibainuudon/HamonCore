/**
 *	@file	condition_variable.hpp
 *
 *	@brief	condition_variable の定義
 */

#ifndef HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_HPP
#define HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_HPP

#include <hamon/condition_variable/cv_status.hpp>
#include <hamon/condition_variable/detail/condition_variable_impl.hpp>
#include <hamon/condition_variable/detail/safe_nanosecond_cast.hpp>
#include <hamon/condition_variable/detail/rel_to_abs.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono.hpp>
#include <hamon/limits.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/unique_lock.hpp>
#include <hamon/system_error.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.7.4 Class condition_variable[thread.condition.condvar]

class condition_variable
{
public:
	condition_variable()
		: m_cv(HAMON_CONDVAR_INITIALIZER)
	{}

	~condition_variable()
	{
		hamon::detail::condvar_destroy(&m_cv);
	}

	condition_variable(condition_variable const&) = delete;
	condition_variable& operator=(condition_variable const&) = delete;

	void notify_one() noexcept
	{
		// [thread.condition.condvar]/5
		hamon::detail::condvar_signal(&m_cv);
	}

	void notify_all() noexcept
	{
		// [thread.condition.condvar]/6
		hamon::detail::condvar_broadcast(&m_cv);
	}

	void wait(hamon::unique_lock<hamon::mutex>& lock)
	{
		if (!lock.owns_lock())
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		int ec = hamon::detail::condvar_wait(&m_cv, lock.mutex()->native_handle());
		if (ec)
		{
			hamon::detail::throw_system_error(ec, hamon::generic_category());
		}
	}

	template <typename Predicate>
	void wait(hamon::unique_lock<hamon::mutex>& lock, Predicate pred)
	{
		// [thread.condition.condvar]/13
		while (!pred())
		{
			wait(lock);
		}
	}

	template <typename Clock, typename Duration>
	hamon::cv_status wait_until(hamon::unique_lock<hamon::mutex>& lock, chrono::time_point<Clock, Duration> abs_time)
	{
		using clock_tp_ns = chrono::time_point<Clock, chrono::nanoseconds>;

		typename Clock::time_point now = Clock::now();
		if (abs_time <= now)
		{
			return cv_status::timeout;
		}

		clock_tp_ns t_ns = clock_tp_ns(hamon::detail::safe_nanosecond_cast(abs_time.time_since_epoch()));

		do_timed_wait(lock, t_ns);

		// [thread.condition.condvar]/20
		return Clock::now() < abs_time ? cv_status::no_timeout : cv_status::timeout;
	}

	template <typename Clock, typename Duration, typename Predicate>
	bool wait_until(hamon::unique_lock<hamon::mutex>& lock, chrono::time_point<Clock, Duration> abs_time, Predicate pred)
	{
		// [thread.condition.condvar]/30
		while (!pred())
		{
			if (wait_until(lock, abs_time) == cv_status::timeout)
			{
				return pred();
			}
		}
		return true;
	}

	template <typename Rep, typename Period>
	hamon::cv_status wait_for(hamon::unique_lock<hamon::mutex>& lock, chrono::duration<Rep, Period> rel_time)
	{
		// [thread.condition.condvar]/24
		return wait_until(lock, hamon::detail::rel_to_abs(rel_time));
	}

	template <typename Rep, typename Period, typename Predicate>
	bool wait_for(hamon::unique_lock<hamon::mutex>& lock, chrono::duration<Rep, Period> rel_time, Predicate pred)
	{
		// [thread.condition.condvar]/36
		return wait_until(lock, hamon::detail::rel_to_abs(rel_time), hamon::move(pred));
	}

	using native_handle_type = hamon::detail::condvar_t*;	// see [thread.req.native]

	native_handle_type native_handle()	// see [thread.req.native]
	{
		return &m_cv;
	}

private:
	template <class Clock>
	void do_timed_wait(unique_lock<mutex>& lock, chrono::time_point<Clock, chrono::nanoseconds> tp) HAMON_NOEXCEPT
	{
		chrono::nanoseconds d = tp - Clock::now();
		if (d <= d.zero())
		{
			return;
		}

		using ns_rep = chrono::nanoseconds::rep;

		using clock_tp_ns = chrono::time_point<chrono::system_clock, chrono::nanoseconds>;
		ns_rep now_ns_count = hamon::detail::safe_nanosecond_cast(chrono::system_clock::now().time_since_epoch()).count();
		ns_rep d_ns_count = hamon::detail::safe_nanosecond_cast(d).count();

		if (now_ns_count > hamon::numeric_limits<ns_rep>::max() - d_ns_count)
		{
			do_timed_wait(lock, clock_tp_ns::max());
		}
		else
		{
			do_timed_wait(lock, clock_tp_ns(chrono::nanoseconds(now_ns_count + d_ns_count)));
		}
	}

	void do_timed_wait(unique_lock<mutex>& lock, chrono::time_point<chrono::system_clock, chrono::nanoseconds> tp) HAMON_NOEXCEPT
	{
		if (!lock.owns_lock())
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		chrono::nanoseconds d = tp.time_since_epoch();
		if (d > chrono::nanoseconds(0x59682F000000E941))
		{
			d = chrono::nanoseconds(0x59682F000000E941);
		}

		hamon::detail::timespec_t ts;
		chrono::seconds s = chrono::duration_cast<chrono::seconds>(d);
		using ts_sec_t = decltype(ts.tv_sec);
		using ts_nsec_t = decltype(ts.tv_nsec);
		constexpr ts_sec_t ts_sec_max = hamon::numeric_limits<ts_sec_t>::max();
		if (s.count() < ts_sec_max)
		{
			ts.tv_sec = static_cast<ts_sec_t>(s.count());
			ts.tv_nsec = static_cast<ts_nsec_t>((d - s).count());
		}
		else
		{
			ts.tv_sec = ts_sec_max;
			ts.tv_nsec = hamon::giga::num - 1;
		}

		int ec = hamon::detail::condvar_timedwait(&m_cv, lock.mutex()->native_handle(), &ts);
		if (ec != 0 && ec != ETIMEDOUT)
		{
			hamon::detail::throw_system_error(ec, hamon::generic_category());
		}
	}

private:
	hamon::detail::condvar_t m_cv;
};

}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_HPP
