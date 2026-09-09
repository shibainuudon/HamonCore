/**
 *	@file	condition_variable.hpp
 *
 *	@brief	condition_variable の定義
 */

#ifndef HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_HPP
#define HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_HPP

#include <hamon/condition_variable/cv_status.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/unique_lock.hpp>

namespace hamon
{

// 32.7.4 Class condition_variable[thread.condition.condvar]

class condition_variable
{
public:
	condition_variable();
	~condition_variable();

	condition_variable(condition_variable const&) = delete;
	condition_variable& operator=(condition_variable const&) = delete;

	void notify_one() noexcept;
	void notify_all() noexcept;

	void wait(hamon::unique_lock<hamon::mutex>& lock);

	template <typename Predicate>
	void wait(hamon::unique_lock<hamon::mutex>& lock, Predicate pred);

	template <typename Clock, typename Duration>
	hamon::cv_status wait_until(hamon::unique_lock<hamon::mutex>& lock, chrono::time_point<Clock, Duration> abs_time);

	template <typename Clock, typename Duration, typename Predicate>
	bool wait_until(hamon::unique_lock<hamon::mutex>& lock, chrono::time_point<Clock, Duration> abs_time, Predicate pred);

	template <typename Rep, typename Period>
	hamon::cv_status wait_for(hamon::unique_lock<hamon::mutex>& lock, chrono::duration<Rep, Period> rel_time);

	template <typename Rep, typename Period, typename Predicate>
	bool wait_for(hamon::unique_lock<hamon::mutex>& lock, chrono::duration<Rep, Period> rel_time, Predicate pred);

//	using native_handle_type = implementation-defined;          // see [thread.req.native]
//	native_handle_type native_handle();                         // see [thread.req.native]
};

}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_CONDITION_VARIABLE_HPP
