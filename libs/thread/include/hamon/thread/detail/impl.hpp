/**
 *	@file	impl.hpp
 *
 *	@brief
 */

#ifndef HAMON_THREAD_DETAIL_IMPL_HPP
#define HAMON_THREAD_DETAIL_IMPL_HPP

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

int __libcpp_recursive_mutex_init(__libcpp_recursive_mutex_t* __m);

int __libcpp_recursive_mutex_lock(__libcpp_recursive_mutex_t* __m);

bool __libcpp_recursive_mutex_trylock(__libcpp_recursive_mutex_t* __m);

int __libcpp_recursive_mutex_unlock(__libcpp_recursive_mutex_t* __m);

int __libcpp_recursive_mutex_destroy(__libcpp_recursive_mutex_t* __m);

int __libcpp_mutex_lock(__libcpp_mutex_t* __m);

bool __libcpp_mutex_trylock(__libcpp_mutex_t* __m);

int __libcpp_mutex_unlock(__libcpp_mutex_t* __m);

int __libcpp_mutex_destroy(__libcpp_mutex_t* __m);

//
// Condition variable
//
typedef void* __libcpp_condvar_t;
#define _LIBCPP_CONDVAR_INITIALIZER 0

int __libcpp_condvar_signal(__libcpp_condvar_t* __cv);

int __libcpp_condvar_broadcast(__libcpp_condvar_t* __cv);

int __libcpp_condvar_wait(__libcpp_condvar_t* __cv, __libcpp_mutex_t* __m);

int __libcpp_condvar_timedwait(__libcpp_condvar_t* __cv, __libcpp_mutex_t* __m, __libcpp_timespec_t* __ts);

int __libcpp_condvar_destroy(__libcpp_condvar_t* __cv);

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

bool __libcpp_thread_id_equal(thread_id __t1, thread_id __t2);

bool __libcpp_thread_id_less(thread_id __t1, thread_id __t2);

//
// Thread
//
#define _LIBCPP_NULL_THREAD 0U
typedef void* thread_t;

bool __libcpp_thread_isnull(const thread_t* __t);

inline int thread_create(thread_t* __t, unsigned (*__func)(void*), void* __arg)
{
	*__t = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, __func, __arg, 0, nullptr));

	if (*__t)
	{
		return 0;
	}
	return GetLastError();
}

thread_id __libcpp_thread_get_current_id();

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

int __libcpp_thread_detach(thread_t* __t);

void __libcpp_thread_yield();

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

#endif // HAMON_THREAD_DETAIL_IMPL_HPP
