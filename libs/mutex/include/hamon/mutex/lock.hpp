/**
 *	@file	lock.hpp
 *
 *	@brief	lock の定義
 */

#ifndef HAMON_MUTEX_LOCK_HPP
#define HAMON_MUTEX_LOCK_HPP

#include <mutex>

namespace hamon
{

using std::lock;

#if 0	// TODO

// 32.6.6 Generic locking algorithms[thread.lock.algorithm]

template<class L1, class L2, class... L3> void lock(L1&, L2&, L3&...);

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_LOCK_HPP
