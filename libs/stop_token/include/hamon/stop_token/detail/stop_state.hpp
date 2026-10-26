/**
 *	@file	stop_state.hpp
 *
 *	@brief	stop_state の定義
 */

#ifndef HAMON_STOP_TOKEN_DETAIL_STOP_STATE_HPP
#define HAMON_STOP_TOKEN_DETAIL_STOP_STATE_HPP

#include <hamon/stop_token/detail/atomic_unique_lock.hpp>
#include <hamon/stop_token/detail/stop_callback_base.hpp>
#include <hamon/atomic/atomic.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/list.hpp>
#include <hamon/thread/thread.hpp>
#include <hamon/thread/this_thread.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace detail
{

class stop_state
{
	static constexpr hamon::uint32_t stop_requested_bit       = (1 << 0);
	static constexpr hamon::uint32_t callback_list_locked_bit = (1 << 1);
	static constexpr hamon::uint32_t stop_source_counter_shift = 2;

	using state_t = hamon::uint32_t;
	using callback_list_lock_t = hamon::detail::atomic_unique_lock<state_t, callback_list_locked_bit>;
	using callback_list_t = hamon::list<stop_callback_base*>;

	// The "stop_source counter" is not used for lifetime reference counting.
	// When the number of stop_source reaches 0, the remaining stop_tokens's
	// stop_possible will return false. We need this counter to track this.
	//
	// The "callback list locked" bit implements the atomic_unique_lock to
	// guard the operations on the callback list
	//
	//       31 - 2          |  1                   |    0           |
	//  stop_source counter  | callback list locked | stop_requested |
	hamon::atomic<hamon::uint32_t> m_state{0};
	callback_list_t m_callback_list;
	hamon::thread::id m_requesting_thread;

public:
	stop_state() noexcept = default;

	void increment_stop_source_counter() noexcept
	{
		HAMON_ASSERT(m_state.load(hamon::memory_order::relaxed) <= static_cast<state_t>(~(1 << stop_source_counter_shift)));
		m_state.fetch_add(1 << stop_source_counter_shift, hamon::memory_order::relaxed);
	}

	// We are not destroying the object after counter decrements to zero, nor do we have
	// operations depend on the ordering of decrementing the counter. relaxed is enough.
	void decrement_stop_source_counter() noexcept
	{
		HAMON_ASSERT(m_state.load(hamon::memory_order::relaxed) >= static_cast<state_t>(1 << stop_source_counter_shift));
		m_state.fetch_sub(1 << stop_source_counter_shift, hamon::memory_order::relaxed);
	}

	bool stop_requested() const noexcept
	{
		// acquire because [thread.stoptoken.intro] A call to request_stop that returns true
		// synchronizes with a call to stop_requested on an associated stop_token or stop_source
		// object that returns true.
		// request_stop's compare_exchange_weak has release which syncs with this acquire
		return (m_state.load(hamon::memory_order::acquire) & stop_requested_bit) != 0;
	}

	bool stop_possible() const noexcept
	{
		// [stoptoken.mem] false if "a stop request was not made and there are no associated stop_source objects"
		// Todo: Can this be hamon::memory_order::relaxed as the standard does not say anything except not to introduce data
		// race?
		state_t curent_state = m_state.load(hamon::memory_order::acquire);
		return ((curent_state & stop_requested_bit) != 0) || ((curent_state >> stop_source_counter_shift) != 0);
	}

	bool request_stop() noexcept
	{
#if !defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)
		const auto lock_fail_condition = [](state_t st) { return (st & stop_requested_bit) != 0; };
		const auto after_lock_state = [](state_t st) { return st | callback_list_locked_bit | stop_requested_bit; };
		const auto locked_ordering = hamon::memory_order::acq_rel;
		callback_list_lock_t cb_list_lock(m_state, lock_fail_condition, after_lock_state, locked_ordering);
#else
		auto cb_list_lock = this->try_lock_for_request_stop();
#endif
		if (!cb_list_lock.owns_lock())
		{
			return false;
		}

		m_requesting_thread = hamon::this_thread::get_id();

		while (!m_callback_list.empty())
		{
			auto cb = m_callback_list.front();
			m_callback_list.pop_front();

			// allow other callbacks to be removed while invoking the current callback
			cb_list_lock.unlock();

			bool destroyed = false;
			cb->m_destroyed = &destroyed;

			cb->invoke();

			// cb's invoke function could potentially delete itself. We need to check before accessing cb's member
			if (!destroyed)
			{
				// needs to set m_destroyed pointer to nullptr, otherwise it points to a local variable
				// which is to be destroyed at the end of the loop
				cb->m_destroyed = nullptr;

				// [stopcallback.cons] If callback is concurrently executing on another thread, then the return
				// from the invocation of callback strongly happens before ([intro.races]) callback is destroyed.
				// this release syncs with the acquire in the remove_callback
				cb->m_completed.store(true, hamon::memory_order::release);
				cb->m_completed.notify_all();
			}

			cb_list_lock.lock();
		}

		return true;
	}

	bool add_callback(stop_callback_base* cb) noexcept
	{
		// If it is already stop_requested. Do not try to request it again.
		const auto give_up_trying_to_lock_condition = [cb](state_t st) {
			if ((st & stop_requested_bit) != 0)
			{
				// already stop requested, synchronously run the callback and no need to lock the list again
				cb->invoke();
				return true;
			}
			// no stop source. no need to lock the list to add the callback as it can never be invoked
			return (st >> stop_source_counter_shift) == 0;
		};

		callback_list_lock_t cb_list_lock(m_state, give_up_trying_to_lock_condition);

		if (!cb_list_lock.owns_lock())
		{
			return false;
		}

		m_callback_list.push_front(cb);

		return true;
		// unlock here: [thread.stoptoken.intro] Registration of a callback synchronizes with the invocation of
		// that callback.
		// Note: this release sync with the acquire in the request_stop' try_lock_for_request_stop
	}

	// called by the destructor of stop_callback
	void remove_callback(stop_callback_base* cb) noexcept
	{
		callback_list_lock_t cb_list_lock(m_state);

		auto const removed_count = m_callback_list.remove(cb);

		if (removed_count == 0)
		{
			auto requested_thread = m_requesting_thread;
			cb_list_lock.unlock();

			if (hamon::this_thread::get_id() != requested_thread)
			{
				// [stopcallback.cons] If callback is concurrently executing on another thread, then the return
				// from the invocation of callback strongly happens before ([intro.races]) callback is destroyed.
				cb->m_completed.wait(false, hamon::memory_order::acquire);
			}
			else
			{
				// The destructor of stop_callback runs on the same thread of the thread that invokes the callback.
				// The callback is potentially invoking its own destuctor. Set the flag to avoid accessing destroyed
				// members on the invoking side
				if (cb->m_destroyed != nullptr)
				{
					*cb->m_destroyed = true;
				}
			}
		}
	}
#if defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)
private:
	callback_list_lock_t try_lock_for_request_stop() noexcept
	{
		// If it is already stop_requested, do not try to request stop or lock the list again.
		const auto lock_fail_condition = [](state_t st) { return (st & stop_requested_bit) != 0; };

		// set locked and requested bit at the same time
		const auto after_lock_state = [](state_t st) { return st | callback_list_locked_bit | stop_requested_bit; };

		// acq because [thread.stoptoken.intro] Registration of a callback synchronizes with the invocation of that
		//     callback. We are going to invoke the callback after getting the lock, acquire so that we can see the
		//     registration of a callback (and other writes that happens-before the add_callback)
		//     Note: the rel (unlock) in the add_callback syncs with this acq
		// rel because [thread.stoptoken.intro] A call to request_stop that returns true synchronizes with a call
		//     to stop_requested on an associated stop_token or stop_source object that returns true.
		//     We need to make sure that all writes (including user code) before request_stop will be made visible
		//     to the threads that waiting for `stop_requested == true`
		//     Note: this rel syncs with the acq in `stop_requested`
		const auto locked_ordering = hamon::memory_order::acq_rel;

		return callback_list_lock_t(m_state, lock_fail_condition, after_lock_state, locked_ordering);
	}
#endif
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_STOP_TOKEN_DETAIL_STOP_STATE_HPP
