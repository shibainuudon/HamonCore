/**
 *	@file	try_lock.hpp
 *
 *	@brief	try_lock の定義
 */

#ifndef HAMON_MUTEX_TRY_LOCK_HPP
#define HAMON_MUTEX_TRY_LOCK_HPP

#include <mutex>

namespace hamon
{

using std::try_lock;

#if 0	// TODO

// 32.6.6 Generic locking algorithms[thread.lock.algorithm]

template<class L1, class L2, class... L3> int try_lock(L1&, L2&, L3&...);

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_TRY_LOCK_HPP
