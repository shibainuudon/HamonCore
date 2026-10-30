/**
 *	@file	unique_lock.hpp
 *
 *	@brief	unique_lock の定義
 */

#ifndef HAMON_MUTEX_UNIQUE_LOCK_HPP
#define HAMON_MUTEX_UNIQUE_LOCK_HPP

#include <hamon/mutex/adopt_lock_t.hpp>
#include <hamon/mutex/defer_lock_t.hpp>
#include <hamon/mutex/try_to_lock_t.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/system_error/system_error.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/system_error/make_error_code.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon
{

// 32.6.5.4 Class template unique_lock[thread.lock.unique]

template <typename Mutex>
class unique_lock
{
public:
	using mutex_type = Mutex;

	// [thread.lock.unique.cons], construct/copy/destroy
	unique_lock() noexcept
		// [thread.lock.unique.cons]/1
		: pm(nullptr)
		, owns(false)
	{}

	explicit
	unique_lock(mutex_type& m)
		// [thread.lock.unique.cons]/3
		: pm(hamon::addressof(m))
		, owns(true)
	{
		// [thread.lock.unique.cons]/2
		pm->lock();
	}

	unique_lock(mutex_type& m, hamon::defer_lock_t) noexcept
		// [thread.lock.unique.cons]/4
		: pm(hamon::addressof(m))
		, owns(false)
	{}

	unique_lock(mutex_type& m, hamon::try_to_lock_t)
		// [thread.lock.unique.cons]/7
		: pm(hamon::addressof(m))
		, owns(m.try_lock())	// [thread.lock.unique.cons]/6
	{}

	unique_lock(mutex_type& m, hamon::adopt_lock_t)
		// [thread.lock.unique.cons]/9
		: pm(hamon::addressof(m))
		, owns(true)
	{}

	template <typename Clock, typename Duration>
	unique_lock(mutex_type& m, hamon::chrono::time_point<Clock, Duration> const& abs_time)
		// [thread.lock.unique.cons]/13
		: pm(hamon::addressof(m))
		, owns(m.try_lock_until(abs_time))	// [thread.lock.unique.cons]/12
	{}

	template <typename Rep, typename Period>
	unique_lock(mutex_type& m, hamon::chrono::duration<Rep, Period> const& rel_time)
		// [thread.lock.unique.cons]/16
		: pm(hamon::addressof(m))
		, owns(m.try_lock_for(rel_time))	// [thread.lock.unique.cons]/15
	{}

	~unique_lock()
	{
		// [thread.lock.unique.cons]/20
		if (owns)
		{
			pm->unlock();
		}
	}

	unique_lock(unique_lock const&) = delete;
	unique_lock& operator=(unique_lock const&) = delete;

	unique_lock(unique_lock&& u) noexcept
		// [thread.lock.unique.cons]/17
		: pm(hamon::exchange(u.pm, nullptr))
		, owns(hamon::exchange(u.owns, false))
	{}

	unique_lock& operator=(unique_lock&& u) noexcept
	{
		if (this != hamon::addressof(u))
		{
			// [thread.lock.unique.cons]/18
			unique_lock(hamon::move(u)).swap(*this);
		}
		// [thread.lock.unique.cons]/19
		return *this;
	}

	// [thread.lock.unique.locking], locking
	void lock()
	{
		// [thread.lock.unique.locking]/4.1
		if (pm == nullptr)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		// [thread.lock.unique.locking]/4.2
		if (owns)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::resource_deadlock_would_occur));
		}

		// [thread.lock.unique.locking]/1
		pm->lock();

		// [thread.lock.unique.locking]/2
		owns = true;
	}

	bool try_lock()
	{
		// [thread.lock.unique.locking]/10.1
		if (pm == nullptr)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		// [thread.lock.unique.locking]/10.2
		if (owns)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::resource_deadlock_would_occur));
		}

		// [thread.lock.unique.locking]/6,7
		owns = pm->try_lock();

		// [thread.lock.unique.locking]/8
		return owns;
	}

	template <typename Rep, typename Period>
	bool try_lock_for(hamon::chrono::duration<Rep, Period> const& rel_time)
	{
		// [thread.lock.unique.locking]/22.1
		if (pm == nullptr)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		// [thread.lock.unique.locking]/22.2
		if (owns)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::resource_deadlock_would_occur));
		}

		// [thread.lock.unique.locking]/18,19
		owns = pm->try_lock_for(rel_time);

		// [thread.lock.unique.locking]/20
		return owns;
	}

	template <typename Clock, typename Duration>
	bool try_lock_until(hamon::chrono::time_point<Clock, Duration> const& abs_time)
	{
		// [thread.lock.unique.locking]/16.1
		if (pm == nullptr)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		// [thread.lock.unique.locking]/16.2
		if (owns)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::resource_deadlock_would_occur));
		}

		// [thread.lock.unique.locking]/12,13
		owns = pm->try_lock_until(abs_time);

		// [thread.lock.unique.locking]/14
		return owns;
	}

	void unlock()
	{
		// [thread.lock.unique.locking]/26.1
		if (!owns)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		// [thread.lock.unique.locking]/23
		pm->unlock();

		// [thread.lock.unique.locking]/24
		owns = false;
	}

	// [thread.lock.unique.mod], modifiers
	void swap(unique_lock& u) noexcept
	{
		// [thread.lock.unique.mod]/1
		hamon::swap(pm, u.pm);
		hamon::swap(owns, u.owns);
	}

	mutex_type* release() noexcept
	{
		// [thread.lock.unique.mod]/2
		owns = false;
		// [thread.lock.unique.mod]/3
		return hamon::exchange(pm, nullptr);
	}

	// [thread.lock.unique.obs], observers
	bool owns_lock() const noexcept
	{
		// [thread.lock.unique.obs]/1
		return owns;
	}

	explicit operator bool() const noexcept
	{
		// [thread.lock.unique.obs]/2
		return owns;
	}

	mutex_type* mutex() const noexcept
	{
		// [thread.lock.unique.obs]/3
		return pm;
	}

private:
	mutex_type* pm;             // exposition only
	bool owns;                  // exposition only
};

template <typename Mutex>
void swap(unique_lock<Mutex>& x, unique_lock<Mutex>& y) noexcept
{
	// [thread.lock.unique.mod]/4
	x.swap(y);
}

}	// namespace hamon

HAMON_WARNING_POP()

#endif // HAMON_MUTEX_UNIQUE_LOCK_HPP
