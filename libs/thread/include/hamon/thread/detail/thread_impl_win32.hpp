/**
 *	@file	thread_impl_win32.hpp
 *
 *	@brief
 */

#ifndef HAMON_THREAD_DETAIL_THREAD_IMPL_WIN32_HPP
#define HAMON_THREAD_DETAIL_THREAD_IMPL_WIN32_HPP

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <process.h>
#include <fibersapi.h>

namespace hamon
{
namespace detail
{

using __libcpp_timespec_t = ::timespec;

//
// Mutex
//
typedef void* __libcpp_mutex_t;
#define _LIBCPP_MUTEX_INITIALIZER 0

#if defined(_WIN64)
typedef void* __libcpp_recursive_mutex_t[5];
#else
typedef void* __libcpp_recursive_mutex_t[6];
#endif

inline int __libcpp_recursive_mutex_init(__libcpp_recursive_mutex_t* __m)
{
	InitializeCriticalSection((LPCRITICAL_SECTION)__m);
	return 0;
}

inline int __libcpp_recursive_mutex_lock(__libcpp_recursive_mutex_t* __m)
{
	EnterCriticalSection((LPCRITICAL_SECTION)__m);
	return 0;
}

inline bool __libcpp_recursive_mutex_trylock(__libcpp_recursive_mutex_t* __m)
{
	return TryEnterCriticalSection((LPCRITICAL_SECTION)__m) != 0;
}

inline int __libcpp_recursive_mutex_unlock(__libcpp_recursive_mutex_t* __m)
{
	LeaveCriticalSection((LPCRITICAL_SECTION)__m);
	return 0;
}

inline int __libcpp_recursive_mutex_destroy(__libcpp_recursive_mutex_t* __m)
{
	DeleteCriticalSection((LPCRITICAL_SECTION)__m);
	return 0;
}

inline int __libcpp_mutex_lock(__libcpp_mutex_t* __m)
{
	AcquireSRWLockExclusive((PSRWLOCK)__m);
	return 0;
}

inline bool __libcpp_mutex_trylock(__libcpp_mutex_t* __m)
{
	return TryAcquireSRWLockExclusive((PSRWLOCK)__m) != 0;
}

inline int __libcpp_mutex_unlock(__libcpp_mutex_t* __m)
{
	ReleaseSRWLockExclusive((PSRWLOCK)__m);
	return 0;
}

inline int __libcpp_mutex_destroy(__libcpp_mutex_t* __m)
{
	static_cast<void>(__m);
	return 0;
}

//
// Condition variable
//
typedef void* __libcpp_condvar_t;
#define _LIBCPP_CONDVAR_INITIALIZER 0

inline int __libcpp_condvar_signal(__libcpp_condvar_t* __cv)
{
	WakeConditionVariable((PCONDITION_VARIABLE)__cv);
	return 0;
}

inline int __libcpp_condvar_broadcast(__libcpp_condvar_t* __cv)
{
	WakeAllConditionVariable((PCONDITION_VARIABLE)__cv);
	return 0;
}

inline int __libcpp_condvar_wait(__libcpp_condvar_t* __cv, __libcpp_mutex_t* __m)
{
	SleepConditionVariableSRW((PCONDITION_VARIABLE)__cv, (PSRWLOCK)__m, INFINITE, 0);
	return 0;
}

#if 0
inline int __libcpp_condvar_timedwait(__libcpp_condvar_t* __cv, __libcpp_mutex_t* __m, __libcpp_timespec_t* __ts)
{
	using namespace std::chrono;

	auto duration = seconds(__ts->tv_sec) + nanoseconds(__ts->tv_nsec);
	auto abstime = system_clock::time_point(duration_cast<system_clock::duration>(duration));
	auto timeout_ms = duration_cast<milliseconds>(abstime - system_clock::now());

	if (!SleepConditionVariableSRW(
		(PCONDITION_VARIABLE)__cv, (PSRWLOCK)__m, timeout_ms.count() > 0 ? timeout_ms.count() : 0, 0))
	{
		auto __ec = GetLastError();
		return __ec == ERROR_TIMEOUT ? ETIMEDOUT : __ec;
	}
	return 0;
}
#endif

inline int __libcpp_condvar_destroy(__libcpp_condvar_t* __cv)
{
	static_cast<void>(__cv);
	return 0;
}

//
// Execute once
//
typedef void* __libcpp_exec_once_flag;
#define _LIBCPP_EXEC_ONCE_INITIALIZER 0

int __libcpp_execute_once(__libcpp_exec_once_flag* __flag, void (*__init_routine)());

//
// Thread id
//
typedef long thread_id;

inline bool __libcpp_thread_id_equal(thread_id __lhs, thread_id __rhs)
{
	return __lhs == __rhs;
}

inline bool __libcpp_thread_id_less(thread_id __lhs, thread_id __rhs)
{
	return __lhs < __rhs;
}

//
// Thread
//
#define _LIBCPP_NULL_THREAD 0U
typedef void* thread_t;

inline bool __libcpp_thread_isnull(const thread_t* __t)
{
	return *__t == 0;
}

using thread_proc_return_type = unsigned int;
#define HAMON_THREAD_PROC_RETURN()	return 0u

inline int thread_create(thread_t* __t, unsigned int (WINAPI*__func)(void*), void* __arg)
{
	*__t = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, __func, __arg, 0, nullptr));

	if (*__t)
	{
		//SetThreadDescription(*__t, L"test");
		return 0;
	}

	return GetLastError();
}

inline thread_id __libcpp_thread_get_current_id()
{
	return GetCurrentThreadId();
}

inline thread_id thread_get_id(const thread_t* __t)
{
	return GetThreadId(*__t);
}

inline int thread_join(thread_t* __t)
{
	if (WaitForSingleObjectEx(*__t, INFINITE, FALSE) == WAIT_FAILED)
	{
		return GetLastError();
	}

	if (!CloseHandle(*__t))
	{
		return GetLastError();
	}

	return 0;
}

inline int __libcpp_thread_detach(thread_t* __t)
{
	if (!CloseHandle(*__t))
	{
		return GetLastError();
	}

	return 0;
}

inline void __libcpp_thread_yield()
{
	SwitchToThread();
}

//void __libcpp_thread_sleep_for(const chrono::nanoseconds& __ns);

//
// Thread local storage
//
typedef long __libcpp_tls_key;

#define _LIBCPP_TLS_DESTRUCTOR_CC __stdcall

int __libcpp_tls_create(__libcpp_tls_key* __key, void(_LIBCPP_TLS_DESTRUCTOR_CC* __at_exit)(void*));

void* __libcpp_tls_get(__libcpp_tls_key __key);

int __libcpp_tls_set(__libcpp_tls_key __key, void* __p);


}	// namespace detail
}	// namespace hamon

#endif // HAMON_THREAD_DETAIL_THREAD_IMPL_WIN32_HPP
