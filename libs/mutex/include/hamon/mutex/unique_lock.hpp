/**
 *	@file	unique_lock.hpp
 *
 *	@brief	unique_lock の定義
 */

#ifndef HAMON_MUTEX_UNIQUE_LOCK_HPP
#define HAMON_MUTEX_UNIQUE_LOCK_HPP

#include <mutex>

namespace hamon
{

using std::unique_lock;

#if 0	// TODO

// 32.6.5.4 Class template unique_lock[thread.lock.unique]

template<class Mutex>
class unique_lock
{
public:
	using mutex_type = Mutex;

	// [thread.lock.unique.cons], construct/copy/destroy
	unique_lock() noexcept;
	explicit unique_lock(mutex_type& m);
	unique_lock(mutex_type& m, defer_lock_t) noexcept;
	unique_lock(mutex_type& m, try_to_lock_t);
	unique_lock(mutex_type& m, adopt_lock_t);
	template<class Clock, class Duration>
	unique_lock(mutex_type& m, const chrono::time_point<Clock, Duration>& abs_time);
	template<class Rep, class Period>
	unique_lock(mutex_type& m, const chrono::duration<Rep, Period>& rel_time);
	~unique_lock();

	unique_lock(const unique_lock&) = delete;
	unique_lock& operator=(const unique_lock&) = delete;

	unique_lock(unique_lock&& u) noexcept;
	unique_lock& operator=(unique_lock&& u) noexcept;

	// [thread.lock.unique.locking], locking
	void lock();
	bool try_lock();

	template<class Rep, class Period>
	bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
	template<class Clock, class Duration>
	bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);

	void unlock();

	// [thread.lock.unique.mod], modifiers
	void swap(unique_lock& u) noexcept;
	mutex_type* release() noexcept;

	// [thread.lock.unique.obs], observers
	bool owns_lock() const noexcept;
	explicit operator bool() const noexcept;
	mutex_type* mutex() const noexcept;

private:
	mutex_type* pm;             // exposition only
	bool owns;                  // exposition only
};

template<class Mutex>
void swap(unique_lock<Mutex>& x, unique_lock<Mutex>& y) noexcept;

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_UNIQUE_LOCK_HPP
