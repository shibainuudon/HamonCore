/**
 *	@file	mutex.hpp
 *
 *	@brief	mutex の定義
 */

#ifndef HAMON_MUTEX_MUTEX_HPP
#define HAMON_MUTEX_MUTEX_HPP

#include <hamon/mutex/detail/mutex_impl.hpp>
#include <hamon/system_error.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

// 32.6.4.2.2 Class mutex[thread.mutex.class]

class mutex
{
public:
	constexpr mutex() noexcept
		: m_mut(HAMON_MUTEX_INITIALIZER)
	{
	}

	~mutex()
	{
		hamon::detail::mutex_destroy(&m_mut);
	}

	mutex(mutex const&) = delete;
	mutex& operator=(mutex const&) = delete;

	void lock()
	{
		int ec = hamon::detail::mutex_lock(&m_mut);
		if (ec)
		{
			hamon::detail::throw_system_error(ec, hamon::generic_category());
		}
	}

	bool try_lock()
	{
		return hamon::detail::mutex_trylock(&m_mut);
	}

	void unlock()
	{
		int ec = hamon::detail::mutex_unlock(&m_mut);
		(void)ec;
		HAMON_ASSERT(ec == 0);

	}

	using native_handle_type = hamon::detail::mutex_t*;	// see [thread.req.native]

	native_handle_type native_handle()	// see [thread.req.native]
	{
		return &m_mut;
	}

private:
	hamon::detail::mutex_t m_mut;
};

}	// namespace hamon

#endif // HAMON_MUTEX_MUTEX_HPP
