/**
 *	@file	lock_guard.hpp
 *
 *	@brief	lock_guard の定義
 */

#ifndef HAMON_MUTEX_LOCK_GUARD_HPP
#define HAMON_MUTEX_LOCK_GUARD_HPP

#include <hamon/mutex/adopt_lock_t.hpp>

namespace hamon
{

// 32.6.5.2 Class template lock_guard[thread.lock.guard]

template <typename Mutex>
class lock_guard
{
public:
	using mutex_type = Mutex;

	explicit lock_guard(mutex_type& m)
		// [thread.lock.guard]/2
		: pm(m)
	{
		m.lock();
	}

	lock_guard(mutex_type& m, hamon::adopt_lock_t)
		// [thread.lock.guard]/4
		: pm(m)
	{}

	~lock_guard()
	{
		// [thread.lock.guard]/6
		pm.unlock();
	}

	lock_guard(lock_guard const&) = delete;
	lock_guard& operator=(lock_guard const&) = delete;

private:
	mutex_type& pm;             // exposition only
};

}	// namespace hamon

#endif // HAMON_MUTEX_LOCK_GUARD_HPP
