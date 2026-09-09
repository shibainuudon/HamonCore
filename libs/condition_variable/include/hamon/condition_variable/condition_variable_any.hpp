/**
 *	@file	condition_variable_any.hpp
 *
 *	@brief	condition_variable_any の定義
 */

#ifndef HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_ANY_HPP
#define HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_ANY_HPP

#include <hamon/condition_variable/cv_status.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/stop_token/stop_token.hpp>

namespace hamon
{

// 32.7.5 Class condition_variable_any[thread.condition.condvarany]

class condition_variable_any
{
public:
	condition_variable_any();
	~condition_variable_any();

	condition_variable_any(condition_variable_any const&) = delete;
	condition_variable_any& operator=(condition_variable_any const&) = delete;

	void notify_one() noexcept;
	void notify_all() noexcept;

	// [thread.condvarany.wait], noninterruptible waits
	template <typename Lock>
	void wait(Lock& lock);

	template <typename Lock, typename Predicate>
	void wait(Lock& lock, Predicate pred);

	template <typename Lock, typename Clock, typename Duration>
	hamon::cv_status wait_until(Lock& lock, chrono::time_point<Clock, Duration> abs_time);

	template <typename Lock, typename Clock, typename Duration, typename Predicate>
	bool wait_until(Lock& lock, chrono::time_point<Clock, Duration> abs_time, Predicate pred);

	template <typename Lock, typename Rep, typename Period>
	hamon::cv_status wait_for(Lock& lock, chrono::duration<Rep, Period> rel_time);

	template <typename Lock, typename Rep, typename Period, typename Predicate>
	bool wait_for(Lock& lock, chrono::duration<Rep, Period> rel_time, Predicate pred);

	// [thread.condvarany.intwait], interruptible waits
	template <typename Lock, typename Predicate>
	bool wait(Lock& lock, hamon::stop_token stoken, Predicate pred);

	template <typename Lock, typename Clock, typename Duration, typename Predicate>
	bool wait_until(Lock& lock, hamon::stop_token stoken, chrono::time_point<Clock, Duration> abs_time, Predicate pred);

	template <typename Lock, typename Rep, typename Period, typename Predicate>
	bool wait_for(Lock& lock, hamon::stop_token stoken, chrono::duration<Rep, Period> rel_time, Predicate pred);
};

}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_ANY_HPP
