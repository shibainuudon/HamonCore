/**
 *	@file	recursive_mutex.hpp
 *
 *	@brief	recursive_mutex の定義
 */

#ifndef HAMON_MUTEX_RECURSIVE_MUTEX_HPP
#define HAMON_MUTEX_RECURSIVE_MUTEX_HPP

#include <hamon/mutex/detail/mutex_impl.hpp>
#include <hamon/system_error.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

// 32.6.4.2.3 Class recursive_mutex[thread.mutex.recursive]

class recursive_mutex
{
public:
	recursive_mutex()
	{
		int ec = hamon::detail::recursive_mutex_init(&m_mut);
		if (ec)
		{
			hamon::detail::throw_system_error(ec, hamon::generic_category());
		}
	}

	~recursive_mutex()
	{
		int e = hamon::detail::recursive_mutex_destroy(&m_mut);
		(void)e;
		HAMON_ASSERT(e == 0);
	}

	recursive_mutex(const recursive_mutex&) = delete;
	recursive_mutex& operator=(const recursive_mutex&) = delete;

	void lock()
	{
		int ec = hamon::detail::recursive_mutex_lock(&m_mut);
		if (ec)
		{
			hamon::detail::throw_system_error(ec, hamon::generic_category());
		}
	}

	bool try_lock() noexcept
	{
		return hamon::detail::recursive_mutex_trylock(&m_mut);
	}

	void unlock()
	{
		int e = hamon::detail::recursive_mutex_unlock(&m_mut);
		(void)e;
		HAMON_ASSERT(e == 0);
	}

	using native_handle_type = hamon::detail::recursive_mutex_t*;	// see [thread.req.native]

	native_handle_type native_handle()	// see [thread.req.native]
	{
		return &m_mut;
	}

private:
	hamon::detail::recursive_mutex_t m_mut;
};

}	// namespace hamon

#endif // HAMON_MUTEX_RECURSIVE_MUTEX_HPP
