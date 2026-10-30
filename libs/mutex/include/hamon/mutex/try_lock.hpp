/**
 *	@file	try_lock.hpp
 *
 *	@brief	try_lock の定義
 */

#ifndef HAMON_MUTEX_TRY_LOCK_HPP
#define HAMON_MUTEX_TRY_LOCK_HPP

#include <hamon/mutex/try_to_lock_t.hpp>
#include <hamon/mutex/unique_lock.hpp>

namespace hamon
{

// 32.6.6 Generic locking algorithms[thread.lock.algorithm]
template <typename L1, typename L2, typename... L3>
int try_lock(L1&, L2&, L3&...);

template <typename L0, typename L1>
int try_lock(L0& l0, L1& l1)
{
	hamon::unique_lock<L0> u0(l0, hamon::try_to_lock);
	if (u0.owns_lock())
	{
		if (l1.try_lock())
		{
			u0.release();
			return -1;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

template <typename L0, typename L1, typename L2, typename... L3>
int try_lock(L0& l0, L1& l1, L2& l2, L3&... l3)
{
	int r = 0;
	hamon::unique_lock<L0> u0(l0, hamon::try_to_lock);
	if (u0.owns_lock())
	{
		r = hamon::try_lock(l1, l2, l3...);
		if (r == -1)
		{
			u0.release();
		}
		else
		{
			++r;
		}
	}
	return r;
}

}	// namespace hamon

#endif // HAMON_MUTEX_TRY_LOCK_HPP
