/**
 *	@file	shared_lock.hpp
 *
 *	@brief	shared_lock の定義
 */

#ifndef HAMON_SHARED_MUTEX_SHARED_LOCK_HPP
#define HAMON_SHARED_MUTEX_SHARED_LOCK_HPP

#include <hamon/shared_mutex/config.hpp>

#if defined(HAMON_USE_STD_SHARED_MUTEX)

#include <shared_mutex>

namespace hamon
{

using std::shared_lock;

}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/system_error/system_error.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/system_error/make_error_code.hpp>
#include <hamon/utility/swap.hpp>
#include <mutex>

namespace hamon
{

// 32.6.5.5 Class template shared_lock[thread.lock.shared]

template <typename Mutex>
class shared_lock
{
public:
	using mutex_type = Mutex;

	// [thread.lock.shared.cons], construct/copy/destroy
	shared_lock() noexcept
		// [thread.lock.shared.cons]/1
		: pm(nullptr), owns(false)
	{}

	explicit shared_lock(mutex_type& m)	// blocking
		// [thread.lock.shared.cons]/3
		: pm(hamon::addressof(m)), owns(true)
	{
		// [thread.lock.shared.cons]/2
		m.lock_shared();
	}

	shared_lock(mutex_type& m, std::defer_lock_t) noexcept
		// [thread.lock.shared.cons]/4
		: pm(hamon::addressof(m)), owns(false)
	{}

	shared_lock(mutex_type& m, std::try_to_lock_t)
		// [thread.lock.shared.cons]/5,6
		: pm(hamon::addressof(m)), owns(m.try_lock_shared())
	{}

	shared_lock(mutex_type& m, std::adopt_lock_t)
		// [thread.lock.shared.cons]/8
		: pm(hamon::addressof(m)), owns(true)
	{}

	template <typename Clock, typename Duration>
	shared_lock(mutex_type& m, hamon::chrono::time_point<Clock, Duration> const& abs_time)
		// [thread.lock.shared.cons]/10,11
		: pm(hamon::addressof(m))
		, owns(m.try_lock_shared_until(abs_time))
	{}

	template <typename Rep, typename Period>
	shared_lock(mutex_type& m, hamon::chrono::duration<Rep, Period> const& rel_time)
		// [thread.lock.shared.cons]/13,14
		: pm(hamon::addressof(m))
		, owns(m.try_lock_shared_for(rel_time))
	{}

	~shared_lock()
	{
		// [thread.lock.shared.cons]/15
		if (owns)
		{
			pm->unlock_shared();
		}
	}

	shared_lock(shared_lock const&) = delete;
	shared_lock& operator=(shared_lock const&) = delete;

	shared_lock(shared_lock&& u) noexcept
		// [thread.lock.shared.cons]/16
		: pm(u.pm), owns(u.owns)
	{
		u.pm    = nullptr;
		u.owns = false;
	}

	shared_lock& operator=(shared_lock&& u) noexcept
	{
		// [thread.lock.shared.cons]/17
		if (owns)
		{
			pm->unlock_shared();
		}

		// [thread.lock.shared.cons]/18
		pm     = u.pm;
		owns   = u.owns;
		u.pm   = nullptr;
		u.owns = false;

		return *this;
	}

	// [thread.lock.shared.locking], locking
	void lock()	// blocking
	{
		// [thread.lock.shared.locking]/4.1
		if (pm == nullptr)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		// [thread.lock.shared.locking]/4.2
		if (owns)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::resource_deadlock_would_occur));
		}

		// [thread.lock.shared.locking]/1
		pm->lock_shared();
		// [thread.lock.shared.locking]/2
		owns = true;
	}

	bool try_lock()
	{
		// [thread.lock.shared.locking]/9.1
		if (pm == nullptr)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		// [thread.lock.shared.locking]/9.2
		if (owns)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::resource_deadlock_would_occur));
		}

		// [thread.lock.shared.locking]/5,6
		owns = pm->try_lock_shared();

		// [thread.lock.shared.locking]/7
		return owns;
	}

	template <typename Clock, typename Duration>
	bool try_lock_until(hamon::chrono::time_point<Clock, Duration> const& abs_time)
	{
		// [thread.lock.shared.locking]/15.1
		if (pm == nullptr)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		// [thread.lock.shared.locking]/15.2
		if (owns)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::resource_deadlock_would_occur));
		}

		// [thread.lock.shared.locking]/11,12
		owns = pm->try_lock_shared_until(abs_time);

		// [thread.lock.shared.locking]/13
		return owns;
	}

	template <typename Rep, typename Period>
	bool try_lock_for(hamon::chrono::duration<Rep, Period> const& rel_time)
	{
		// [thread.lock.shared.locking]/21.1
		if (pm == nullptr)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		// [thread.lock.shared.locking]/21.2
		if (owns)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::resource_deadlock_would_occur));
		}

		// [thread.lock.shared.locking]/17,18
		owns = pm->try_lock_shared_for(rel_time);

		// [thread.lock.shared.locking]/19
		return owns;
	}

	void unlock()
	{
		// [thread.lock.shared.locking]/25
		if (!owns)
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::operation_not_permitted));
		}

		// [thread.lock.shared.locking]/22
		pm->unlock_shared();

		// [thread.lock.shared.locking]/23
		owns = false;
	}

	// [thread.lock.shared.mod], modifiers
	void swap(shared_lock& u) noexcept
	{
		// [thread.lock.shared.mod]/1
		hamon::swap(pm, u.pm);
		hamon::swap(owns, u.owns);
	}

	mutex_type* release() noexcept
	{
		mutex_type* m = pm;

		// [thread.lock.shared.mod]/2
		pm   = nullptr;
		owns = false;

		// [thread.lock.shared.mod]/3
		return m;
	}

	// [thread.lock.shared.obs], observers
	bool owns_lock() const noexcept
	{
		// [thread.lock.shared.obs]/1
		return owns;
	}

	explicit operator bool() const noexcept
	{
		// [thread.lock.shared.obs]/2
		return owns;
	}

	mutex_type* mutex() const noexcept
	{
		// [thread.lock.shared.obs]/3
		return pm;
	}

private:
	mutex_type* pm;
	bool        owns;
};

template <typename Mutex>
void swap(shared_lock<Mutex>& x, shared_lock<Mutex>& y) noexcept
{
	// [thread.lock.shared.mod]/4
	x.swap(y);
}

}	// namespace hamon

#endif

#endif // HAMON_SHARED_MUTEX_SHARED_LOCK_HPP
