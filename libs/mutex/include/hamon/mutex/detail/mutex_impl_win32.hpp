/**
 *	@file	mutex_impl_win32.hpp
 *
 *	@brief
 */

#ifndef HAMON_MUTEX_DETAIL_MUTEX_IMPL_WIN32_HPP
#define HAMON_MUTEX_DETAIL_MUTEX_IMPL_WIN32_HPP

#include <hamon/detail/windows.hpp>
#include <process.h>
#include <fibersapi.h>

namespace hamon
{
namespace detail
{

//
// Mutex
//
using mutex_t = void*;
#define HAMON_MUTEX_INITIALIZER 0

inline int mutex_lock(mutex_t* m)
{
	::AcquireSRWLockExclusive((::PSRWLOCK)m);
	return 0;
}

inline bool mutex_trylock(mutex_t* m)
{
	return ::TryAcquireSRWLockExclusive((::PSRWLOCK)m) != 0;
}

inline int mutex_unlock(mutex_t* m)
{
	::ReleaseSRWLockExclusive((::PSRWLOCK)m);
	return 0;
}

inline int mutex_destroy(mutex_t* m)
{
	static_cast<void>(m);
	return 0;
}

//
// Recursive Mutex
//
#if defined(_WIN64)
using recursive_mutex_t = void*[5];
#else
using recursive_mutex_t = void*[6];
#endif

inline int recursive_mutex_init(recursive_mutex_t* m)
{
	::InitializeCriticalSection((::LPCRITICAL_SECTION)m);
	return 0;
}

inline int recursive_mutex_lock(recursive_mutex_t* m)
{
	::EnterCriticalSection((::LPCRITICAL_SECTION)m);
	return 0;
}

inline bool recursive_mutex_trylock(recursive_mutex_t* m)
{
	return ::TryEnterCriticalSection((::LPCRITICAL_SECTION)m) != 0;
}

inline int recursive_mutex_unlock(recursive_mutex_t* m)
{
	::LeaveCriticalSection((::LPCRITICAL_SECTION)m);
	return 0;
}

inline int recursive_mutex_destroy(recursive_mutex_t* m)
{
	::DeleteCriticalSection((::LPCRITICAL_SECTION)m);
	return 0;
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_MUTEX_DETAIL_MUTEX_IMPL_WIN32_HPP
