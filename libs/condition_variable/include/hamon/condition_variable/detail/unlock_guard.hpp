/**
 *	@file	unlock_guard.hpp
 *
 *	@brief	unlock_guard の定義
 */

#ifndef HAMON_CONDITION_VARIABLE_DETAIL_UNLOCK_GUARD_HPP
#define HAMON_CONDITION_VARIABLE_DETAIL_UNLOCK_GUARD_HPP

#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Lock>
struct unlock_guard
{
	Lock& m_lock;

	unlock_guard(Lock& lock)
		: m_lock(lock)
	{
		m_lock.unlock();
	}

	~unlock_guard() HAMON_NOEXCEPT // turns exception to std::terminate
	{
		m_lock.lock();
	}

	unlock_guard(unlock_guard const&) = delete;
	unlock_guard& operator=(unlock_guard const&) = delete;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_DETAIL_UNLOCK_GUARD_HPP
