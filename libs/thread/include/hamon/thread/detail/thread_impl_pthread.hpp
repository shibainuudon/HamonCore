/**
 *	@file	thread_impl_pthread.hpp
 *
 *	@brief
 */

#ifndef HAMON_THREAD_DETAIL_THREAD_IMPL_PTHREAD_HPP
#define HAMON_THREAD_DETAIL_THREAD_IMPL_PTHREAD_HPP

#include <pthread.h>
#include <sched.h>

namespace hamon
{
namespace detail
{

using __libcpp_timespec_t = ::timespec;

//
// Mutex
//
typedef pthread_mutex_t __libcpp_mutex_t;
#define _LIBCPP_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

typedef pthread_mutex_t __libcpp_recursive_mutex_t;

inline int __libcpp_recursive_mutex_init(__libcpp_recursive_mutex_t* __m)
{
	pthread_mutexattr_t __attr;
	int __ec = pthread_mutexattr_init(&__attr);
	if (__ec)
	{
		return __ec;
	}

	__ec = pthread_mutexattr_settype(&__attr, PTHREAD_MUTEX_RECURSIVE);
	if (__ec)
	{
		pthread_mutexattr_destroy(&__attr);
		return __ec;
	}
	__ec = pthread_mutex_init(__m, &__attr);
	if (__ec)
	{
		pthread_mutexattr_destroy(&__attr);
		return __ec;
	}
	__ec = pthread_mutexattr_destroy(&__attr);
	if (__ec)
	{
		pthread_mutex_destroy(__m);
		return __ec;
	}
	return 0;
}

inline int __libcpp_recursive_mutex_lock(__libcpp_recursive_mutex_t* __m)
{
	return pthread_mutex_lock(__m);
}

inline bool __libcpp_recursive_mutex_trylock(__libcpp_recursive_mutex_t* __m)
{
	return pthread_mutex_trylock(__m) == 0;
}

inline int __libcpp_recursive_mutex_unlock(__libcpp_recursive_mutex_t* __m)
{
	return pthread_mutex_unlock(__m);
}

inline int __libcpp_recursive_mutex_destroy(__libcpp_recursive_mutex_t* __m)
{
	return pthread_mutex_destroy(__m);
}

inline int __libcpp_mutex_lock(__libcpp_mutex_t* __m)
{
	return pthread_mutex_lock(__m);
}

inline bool __libcpp_mutex_trylock(__libcpp_mutex_t* __m)
{
	return pthread_mutex_trylock(__m) == 0;
}

inline int __libcpp_mutex_unlock(__libcpp_mutex_t* __m)
{
	return pthread_mutex_unlock(__m);
}

inline int __libcpp_mutex_destroy(__libcpp_mutex_t* __m)
{
	return pthread_mutex_destroy(__m);
}

//
// Condition Variable
//
typedef pthread_cond_t __libcpp_condvar_t;
#define _LIBCPP_CONDVAR_INITIALIZER PTHREAD_COND_INITIALIZER

inline int __libcpp_condvar_signal(__libcpp_condvar_t* __cv)
{
	return pthread_cond_signal(__cv);
}

inline int __libcpp_condvar_broadcast(__libcpp_condvar_t* __cv)
{
	return pthread_cond_broadcast(__cv);
}

inline int __libcpp_condvar_wait(__libcpp_condvar_t* __cv, __libcpp_mutex_t* __m)
{
	return pthread_cond_wait(__cv, __m);
}

inline int __libcpp_condvar_timedwait(__libcpp_condvar_t* __cv, __libcpp_mutex_t* __m, __libcpp_timespec_t* __ts)
{
	return pthread_cond_timedwait(__cv, __m, __ts);
}

inline int __libcpp_condvar_destroy(__libcpp_condvar_t* __cv)
{
	return pthread_cond_destroy(__cv);
}

//
// Execute once
//
typedef pthread_once_t __libcpp_exec_once_flag;
#define _LIBCPP_EXEC_ONCE_INITIALIZER PTHREAD_ONCE_INIT

inline int __libcpp_execute_once(__libcpp_exec_once_flag* __flag, void (*__init_routine)())
{
	return pthread_once(__flag, __init_routine);
}

//
// Thread id
//
#if _LIBCPP_LIBC_LLVM_LIBC
typedef pthread_id_np_t thread_id;
#elif defined(__MVS__)
typedef unsigned long long thread_id;
#else
typedef pthread_t thread_id;
#endif

inline bool __libcpp_thread_id_equal(thread_id __t1, thread_id __t2)
{
	return __t1 == __t2;
}

inline bool __libcpp_thread_id_less(thread_id __t1, thread_id __t2)
{
	return __t1 < __t2;
}

//
// Thread attribute
//
using thread_attr_t = pthread_attr_t;

inline int thread_attr_init(thread_attr_t* attr)
{
	return pthread_attr_init(attr);
}

inline int thread_attr_setstacksize(thread_attr_t* attr, int stacksize)
{
	return pthread_attr_setstacksize(attr, stacksize);
}

//
// Thread
//
#if defined(PTHREAD_NULL)
#  define _LIBCPP_NULL_THREAD PTHREAD_NULL
#else
#  define _LIBCPP_NULL_THREAD ((thread_t()))
#endif
typedef pthread_t thread_t;

inline thread_id thread_get_id(const thread_t* __t)
{
#if _LIBCPP_LIBC_LLVM_LIBC
	thread_id __id;
	return pthread_getunique_np(__t, &__id) ? 0 : __id;
#elif defined(__MVS__)
	return __t->__;
#else
	return *__t;
#endif
}

inline bool thread_isnull(const thread_t* __t)
{
	return thread_get_id(__t) == 0;
}

using thread_proc_return_type = void*;
#define HAMON_THREAD_PROC_RETURN()	return nullptr
#define HAMON_THREAD_PROC_CALLING_CONVENTION

inline int thread_create(thread_t* __t, thread_attr_t* attr, void* (*__func)(void*), void* __arg)
{
	return pthread_create(__t, attr, __func, __arg);
}

inline int thread_setname(thread_t* __t, const char* name)
{
	return pthread_setname_np(*__t, name);
}

inline thread_id __libcpp_thread_get_current_id()
{
#if _LIBCPP_LIBC_LLVM_LIBC
	return pthread_getthreadid_np();
#else
	const thread_t __current_thread = pthread_self();
	return thread_get_id(&__current_thread);
#endif
}

inline int thread_join(thread_t* __t)
{
	return pthread_join(*__t, nullptr);
}

inline int __libcpp_thread_detach(thread_t* __t)
{
	return pthread_detach(*__t);
}

inline void __libcpp_thread_yield()
{
	sched_yield();
}

//inline void __libcpp_thread_sleep_for(const chrono::nanoseconds& __ns)
//{
//	__libcpp_timespec_t __ts = std::__convert_to_timespec<__libcpp_timespec_t>(__ns);
//	while (nanosleep(&__ts, &__ts) == -1 && errno == EINTR)
//		;
//}

//
// Thread local storage
//
#define _LIBCPP_TLS_DESTRUCTOR_CC /* nothing */

typedef pthread_key_t __libcpp_tls_key;

inline int __libcpp_tls_create(__libcpp_tls_key* __key, void (*__at_exit)(void*))
{
	return pthread_key_create(__key, __at_exit);
}

inline void* __libcpp_tls_get(__libcpp_tls_key __key)
{
	return pthread_getspecific(__key);
}

inline int __libcpp_tls_set(__libcpp_tls_key __key, void* __p)
{
	return pthread_setspecific(__key, __p);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_THREAD_DETAIL_THREAD_IMPL_PTHREAD_HPP
