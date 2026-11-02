/**
 *	@file	condition_variable_impl_win32.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONDITION_VARIABLE_DETAIL_CONDITION_VARIABLE_IMPL_WIN32_HPP
#define HAMON_CONDITION_VARIABLE_DETAIL_CONDITION_VARIABLE_IMPL_WIN32_HPP

#include <hamon/mutex/detail/mutex_impl.hpp>
#include <hamon/chrono.hpp>

#include <hamon/detail/windows.hpp>
#include <process.h>
#include <fibersapi.h>

namespace hamon
{
namespace detail
{

using timespec_t = ::timespec;

//
// Condition variable
//
using condvar_t = void*;
#define HAMON_CONDVAR_INITIALIZER 0

inline int condvar_signal(condvar_t* cv)
{
	::WakeConditionVariable((PCONDITION_VARIABLE)cv);
	return 0;
}

inline int condvar_broadcast(condvar_t* cv)
{
	::WakeAllConditionVariable((PCONDITION_VARIABLE)cv);
	return 0;
}

inline int condvar_wait(condvar_t* cv, mutex_t* m)
{
	::SleepConditionVariableSRW((PCONDITION_VARIABLE)cv, (PSRWLOCK)m, INFINITE, 0);
	return 0;
}

inline int condvar_timedwait(condvar_t* cv, mutex_t* m, timespec_t* ts)
{
	using namespace hamon::chrono;

	auto duration = seconds(ts->tv_sec) + nanoseconds(ts->tv_nsec);
	auto abstime = system_clock::time_point(duration_cast<system_clock::duration>(duration));
	auto timeout_ms = duration_cast<milliseconds>(abstime - system_clock::now());
	auto count = timeout_ms.count() > 0 ? timeout_ms.count() : 0;

	if (!::SleepConditionVariableSRW((PCONDITION_VARIABLE)cv, (PSRWLOCK)m, (DWORD)count, 0))
	{
		auto ec = ::GetLastError();
		return ec == ERROR_TIMEOUT ? ETIMEDOUT : ec;
	}

	return 0;
}

inline int condvar_destroy(condvar_t* cv)
{
	static_cast<void>(cv);
	return 0;
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_DETAIL_CONDITION_VARIABLE_IMPL_WIN32_HPP
