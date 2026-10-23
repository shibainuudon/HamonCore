/**
 *	@file	thread_impl_pthread.hpp
 *
 *	@brief
 */

#ifndef HAMON_THREAD_DETAIL_THREAD_IMPL_PTHREAD_HPP
#define HAMON_THREAD_DETAIL_THREAD_IMPL_PTHREAD_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uint64_t.hpp>
#include <hamon/limits.hpp>

#include <pthread.h>
#include <sched.h>

namespace hamon
{
namespace detail
{

//
// Thread id
//
using thread_id = ::pthread_t;

inline bool thread_id_equal(thread_id lhs, thread_id rhs)
{
	return lhs == rhs;
}

inline bool thread_id_less(thread_id lhs, thread_id rhs)
{
	return lhs < rhs;
}

//
// Thread attribute
//
using thread_attr_t = ::pthread_attr_t;

inline int thread_attr_init(thread_attr_t* attr)
{
	return ::pthread_attr_init(attr);
}

inline int thread_attr_setstacksize(thread_attr_t* attr, hamon::size_t stacksize)
{
	return ::pthread_attr_setstacksize(attr, stacksize);
}

//
// Thread
//
using thread_t = ::pthread_t;

inline thread_id thread_get_id(thread_t const* t)
{
	return *t;
}

inline bool thread_isnull(thread_t const* t)
{
	return thread_get_id(t) == 0;
}

using thread_proc_return_type = void*;
#define HAMON_THREAD_PROC_RETURN()	return nullptr
#define HAMON_THREAD_PROC_CALLING_CONVENTION

inline int thread_create(thread_t* t, thread_attr_t* attr, void* (*func)(void*), void* arg)
{
	return ::pthread_create(t, attr, func, arg);
}

inline int thread_setname(thread_t* t, char const* name)
{
	return ::pthread_setname_np(*t, name);
}

inline thread_id thread_get_current_id()
{
	thread_t const current_thread = ::pthread_self();
	return thread_get_id(&current_thread);
}

inline int thread_join(thread_t* t)
{
	return ::pthread_join(*t, nullptr);
}

inline int thread_detach(thread_t* t)
{
	return ::pthread_detach(*t);
}

inline void thread_yield()
{
	::sched_yield();
}

inline void thread_sleep_for(hamon::uint64_t ns)
{
	::timespec ts;
	using tv_sec_t = decltype(ts.tv_sec);
	using tv_nsec_t = decltype(ts.tv_nsec);
	auto const tv_sec_max = hamon::numeric_limits<tv_sec_t>::max();

	hamon::uint64_t const giga = 1000 * 1000 * 1000;
	hamon::uint64_t s = ns / giga;
	if (s < tv_sec_max)
	{
		ts.tv_sec  = static_cast<tv_sec_t>(s);
		ts.tv_nsec = static_cast<tv_nsec_t>(ns - (s * giga));
	}
	else
	{
		ts.tv_sec  = tv_sec_max;
		ts.tv_nsec = giga - 1;
	}

	while (::nanosleep(&ts, &ts) == -1 && errno == EINTR)
	{
	}
}

inline unsigned int thread_hardware_concurrency()
{
#if defined(_SC_NPROCESSORS_ONLN)
	long result = ::sysconf(_SC_NPROCESSORS_ONLN);
	if (result < 0)
	{
		return 0;
	}
	return static_cast<unsigned>(result);
#else
	return 0;
#endif
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_THREAD_DETAIL_THREAD_IMPL_PTHREAD_HPP
