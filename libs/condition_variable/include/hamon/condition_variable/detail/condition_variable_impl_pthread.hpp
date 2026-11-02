/**
 *	@file	condition_variable_impl_pthread.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONDITION_VARIABLE_DETAIL_CONDITION_VARIABLE_IMPL_PTHREAD_HPP
#define HAMON_CONDITION_VARIABLE_DETAIL_CONDITION_VARIABLE_IMPL_PTHREAD_HPP

#include <hamon/mutex/detail/mutex_impl.hpp>

#include <pthread.h>
#include <sched.h>

namespace hamon
{
namespace detail
{

using timespec_t = ::timespec;

//
// Condition Variable
//
using condvar_t = ::pthread_cond_t;
#define HAMON_CONDVAR_INITIALIZER PTHREAD_COND_INITIALIZER

inline int condvar_signal(condvar_t* cv)
{
	return ::pthread_cond_signal(cv);
}

inline int condvar_broadcast(condvar_t* cv)
{
	return ::pthread_cond_broadcast(cv);
}

inline int condvar_wait(condvar_t* cv, mutex_t* m)
{
	return ::pthread_cond_wait(cv, m);
}

inline int condvar_timedwait(condvar_t* cv, mutex_t* m, timespec_t* ts)
{
	return ::pthread_cond_timedwait(cv, m, ts);
}

inline int condvar_destroy(condvar_t* cv)
{
	return ::pthread_cond_destroy(cv);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_DETAIL_CONDITION_VARIABLE_IMPL_PTHREAD_HPP
