/**
 *	@file	atomic_unique_lock.hpp
 *
 *	@brief	atomic_unique_lock の定義
 */

#ifndef HAMON_STOP_TOKEN_DETAIL_ATOMIC_UNIQUE_LOCK_HPP
#define HAMON_STOP_TOKEN_DETAIL_ATOMIC_UNIQUE_LOCK_HPP

#include <hamon/atomic.hpp>
#include <hamon/bit/has_single_bit.hpp>

namespace hamon
{
namespace detail
{

// This class implements an RAII unique_lock without a mutex.
// It uses hamon::atomic<State>,
// where State contains a lock bit and might contain other data,
// and LockedBit is the value of State when the lock bit is set, e.g  1 << 2
template <typename State, State LockedBit>
class atomic_unique_lock
{
	static_assert(hamon::has_single_bit(static_cast<unsigned long long>(LockedBit)),
		"LockedBit must be an integer where only one bit is set");

	hamon::atomic<State>& m_state;
	bool m_is_locked;

public:
	explicit atomic_unique_lock(hamon::atomic<State>& state) noexcept
		: m_state(state), m_is_locked(true)
	{
		this->lock();
	}

	template <typename Pred>
	atomic_unique_lock(hamon::atomic<State>& state, Pred&& give_up_locking) noexcept
		: m_state(state), m_is_locked(false)
	{
		auto const set_locked_bit = [](State st) { return st | LockedBit; };
		m_is_locked = this->lock_impl(give_up_locking, set_locked_bit, hamon::memory_order::acquire);
	}

	template <typename Pred, typename UnaryFunction>
	atomic_unique_lock(
		hamon::atomic<State>& state,
		Pred&& give_up_locking,
		UnaryFunction&& state_after_lock,
		hamon::memory_order locked_ordering) noexcept
		: m_state(state), m_is_locked(false)
	{
		m_is_locked = this->lock_impl(give_up_locking, state_after_lock, locked_ordering);
	}

	atomic_unique_lock(atomic_unique_lock const&)            = delete;
	atomic_unique_lock(atomic_unique_lock&&)                 = delete;
	atomic_unique_lock& operator=(atomic_unique_lock const&) = delete;
	atomic_unique_lock& operator=(atomic_unique_lock&&)      = delete;

	~atomic_unique_lock()
	{
		if (m_is_locked)
		{
			this->unlock();
		}
	}

	bool owns_lock() const noexcept
	{
		return m_is_locked;
	}

	void lock() noexcept
	{
		auto const never_give_up_locking = [](State) { return false; };
		auto const set_locked_bit = [](State st) { return st | LockedBit; };
		// hamon::memory_order::acquire because we'd like to make sure that all the read operations after the lock can read the
		// up-to-date values.
		this->lock_impl(never_give_up_locking, set_locked_bit, hamon::memory_order::acquire);
		m_is_locked = true;
	}

	void unlock() noexcept
	{
		// unset the LockedBit. `memory_order::release` because we need to make sure all the write operations before calling
		// `unlock` will be made visible to other threads
		m_state.fetch_and(static_cast<State>(~LockedBit), hamon::memory_order::release);
		m_state.notify_all();
		m_is_locked = false;
	}

private:
	template <typename Pred, typename UnaryFunction>
	bool lock_impl(
		Pred&& give_up_locking, // while trying to lock the state, if the predicate returns true, give up locking and return
		UnaryFunction&& state_after_lock,
		hamon::memory_order locked_ordering) noexcept
	{
		// At this stage, until we exit the inner while loop, other than the atomic state, we are not reading any order
		// dependent values that is written on other threads, or writing anything that needs to be seen on other threads.
		// Therefore `memory_order::relaxed` is enough.
		State current_state = m_state.load(hamon::memory_order::relaxed);
		do
		{
			while (true)
			{
				if (give_up_locking(current_state))
				{
					// user provided early return condition. fail to lock
					return false;
				}
				else if ((current_state & LockedBit) != 0)
				{
					// another thread has locked the state, we need to wait
					m_state.wait(current_state, hamon::memory_order::relaxed);
					// when it is woken up by notifyAll or spuriously, the m_state
					// might have changed. reload the state
					// Note that the new state's LockedBit may or may not equal to 0
					current_state = m_state.load(hamon::memory_order::relaxed);
				}
				else
				{
					// at least for now, it is not locked. we can try `compare_exchange_weak` to lock it.
					// Note that the variable `current_state`'s lock bit has to be 0 at this point.
					break;
				}
			}
		} while (!m_state.compare_exchange_weak(
			current_state, // if m_state has the same value of current_state, lock bit must be zero before exchange and
			// we are good to lock/exchange and return. If _state has a different value, because other
			// threads locked it between the `break` statement above and this statement, exchange will fail
			// and go back to the inner while loop above.
			state_after_lock(current_state), // state after lock. Usually it should be current_state | LockedBit.
			// Some use cases need to set other bits at the same time as an atomic
			// operation therefore we accept a function
			locked_ordering,        // sucessful exchange order. Usually it should be hamon::memory_order::acquire.
			// Some use cases need more strict ordering therefore we accept it as a parameter
			hamon::memory_order::relaxed // fail to exchange order. We don't need any ordering as we are going back to the
			// inner while loop
		));

		return true;
	}
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_STOP_TOKEN_DETAIL_ATOMIC_UNIQUE_LOCK_HPP
