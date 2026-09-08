/**
 *	@file	lock_guard.hpp
 *
 *	@brief	lock_guard の定義
 */

#ifndef HAMON_MUTEX_LOCK_GUARD_HPP
#define HAMON_MUTEX_LOCK_GUARD_HPP

#include <mutex>

namespace hamon
{

using std::lock_guard;

#if 0	// TODO

template<class Mutex>
class lock_guard
{
public:
	using mutex_type = Mutex;

	explicit lock_guard(mutex_type& m);
	lock_guard(mutex_type& m, adopt_lock_t);
	~lock_guard();

	lock_guard(const lock_guard&) = delete;
	lock_guard& operator=(const lock_guard&) = delete;

private:
	mutex_type& pm;             // exposition only
};

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_LOCK_GUARD_HPP
