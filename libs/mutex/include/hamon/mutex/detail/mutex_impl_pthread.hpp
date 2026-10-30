/**
 *	@file	mutex_impl_pthread.hpp
 *
 *	@brief
 */

#ifndef HAMON_MUTEX_DETAIL_MUTEX_IMPL_PTHREAD_HPP
#define HAMON_MUTEX_DETAIL_MUTEX_IMPL_PTHREAD_HPP

#include <pthread.h>
#include <sched.h>

namespace hamon
{
namespace detail
{

//
// Mutex
//
using mutex_t = ::pthread_mutex_t;
#define HAMON_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

inline int mutex_lock(mutex_t* m)
{
	return ::pthread_mutex_lock(m);
}

inline bool mutex_trylock(mutex_t* m)
{
	return ::pthread_mutex_trylock(m) == 0;
}

inline int mutex_unlock(mutex_t* m)
{
	return ::pthread_mutex_unlock(m);
}

inline int mutex_destroy(mutex_t* m)
{
	return ::pthread_mutex_destroy(m);
}

//
// Recursive Mutex
//
using recursive_mutex_t = ::pthread_mutex_t;

inline int recursive_mutex_init(recursive_mutex_t* m)
{
	::pthread_mutexattr_t attr;
	int ec = ::pthread_mutexattr_init(&attr);
	if (ec)
	{
		return ec;
	}
	ec = ::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	if (ec)
	{
		::pthread_mutexattr_destroy(&attr);
		return ec;
	}
	ec = ::pthread_mutex_init(m, &attr);
	if (ec)
	{
		::pthread_mutexattr_destroy(&attr);
		return ec;
	}
	ec = ::pthread_mutexattr_destroy(&attr);
	if (ec)
	{
		::pthread_mutex_destroy(m);
		return ec;
	}
	return 0;
}

inline int recursive_mutex_lock(recursive_mutex_t* m)
{
	return ::pthread_mutex_lock(m);
}

inline bool recursive_mutex_trylock(recursive_mutex_t* m)
{
	return ::pthread_mutex_trylock(m) == 0;
}

inline int recursive_mutex_unlock(recursive_mutex_t* m)
{
	return ::pthread_mutex_unlock(m);
}

inline int recursive_mutex_destroy(recursive_mutex_t* m)
{
	return ::pthread_mutex_destroy(m);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_MUTEX_DETAIL_MUTEX_IMPL_PTHREAD_HPP
