/**
 *	@file	lock.hpp
 *
 *	@brief	lock の定義
 */

#ifndef HAMON_MUTEX_LOCK_HPP
#define HAMON_MUTEX_LOCK_HPP

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/mutex/try_lock.hpp>
#include <hamon/thread/this_thread.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.6.6 Generic locking algorithms[thread.lock.algorithm]
template <typename L1, typename L2, typename... L3>
void lock(L1&, L2&, L3&...);

template <typename L0, typename L1>
void lock(L0& l0, L1& l1)
{
	while (true)
	{
		{
			hamon::unique_lock<L0> u0(l0);
			if (l1.try_lock())
			{
				u0.release();
				break;
			}
		}
		hamon::this_thread::yield();

		{
			hamon::unique_lock<L1> u1(l1);
			if (l0.try_lock())
			{
				u1.release();
				break;
			}
		}
		hamon::this_thread::yield();
	}
}

namespace detail
{

HAMON_WARNING_PUSH()
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000)
HAMON_WARNING_DISABLE_GCC("-Winfinite-recursion")
#endif

template <typename L0, typename L1, typename L2, typename... L3>
void lock_impl(int i, L0& l0, L1& l1, L2& l2, L3&... l3)
{
	while (true)
	{
		switch (i)
		{
		case 0:
			{
				hamon::unique_lock<L0> u0(l0);
				i = hamon::try_lock(l1, l2, l3...);
				if (i == -1)
				{
					u0.release();
					return;
				}
			}
			++i;
			hamon::this_thread::yield();
			break;

		case 1:
			{
				hamon::unique_lock<L1> u1(l1);
				i = hamon::try_lock(l2, l3..., l0);
				if (i == -1)
				{
					u1.release();
					return;
				}
			}
			if (i == sizeof...(L3) + 1)
			{
				i = 0;
			}
			else
			{
				i += 2;
			}
			hamon::this_thread::yield();
			break;

		default:
			hamon::detail::lock_impl(i - 2, l2, l3..., l0, l1);
			return;
		}
	}
}

HAMON_WARNING_POP()

}	// namespace detail

template <typename L0, typename L1, typename L2, typename... L3>
inline void lock(L0& l0, L1& l1, L2& l2, L3&... l3)
{
	hamon::detail::lock_impl(0, l0, l1, l2, l3...);
}

}	// namespace hamon

#endif // HAMON_MUTEX_LOCK_HPP
