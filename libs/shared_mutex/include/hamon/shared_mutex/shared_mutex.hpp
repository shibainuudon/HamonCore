/**
 *	@file	shared_mutex.hpp
 *
 *	@brief	shared_mutex の定義
 */

#ifndef HAMON_SHARED_MUTEX_SHARED_MUTEX_HPP
#define HAMON_SHARED_MUTEX_SHARED_MUTEX_HPP

#include <hamon/shared_mutex/config.hpp>

#if defined(HAMON_USE_STD_SHARED_MUTEX)

#include <shared_mutex>

namespace hamon
{

using std::shared_mutex;

}	// namespace hamon

#else

#include <hamon/shared_mutex/detail/shared_mutex_base.hpp>

namespace hamon
{

// 32.6.4.4.2 Class shared_mutex[thread.sharedmutex.class]

class shared_mutex
{
	hamon::detail::shared_mutex_base m_base;
public:
	shared_mutex() : m_base() {}
	~shared_mutex() = default;

	shared_mutex(shared_mutex const&) = delete;
	shared_mutex& operator=(shared_mutex const&) = delete;

	// exclusive ownership
	void lock()		// blocking
	{
		return m_base.lock();
	}

	bool try_lock()
	{
		return m_base.try_lock();
	}

	void unlock()
	{
		return m_base.unlock();
	}

	// shared ownership
	void lock_shared()	// blocking
	{
		return m_base.lock_shared();
	}

	bool try_lock_shared()
	{
		return m_base.try_lock_shared();
	}

	void unlock_shared()
	{
		return m_base.unlock_shared();
	}

//	using native_handle_type = implementation-defined;          // see [thread.req.native]
//	native_handle_type native_handle();                         // see [thread.req.native]
};

}	// namespace hamon

#endif

#endif // HAMON_SHARED_MUTEX_SHARED_MUTEX_HPP
