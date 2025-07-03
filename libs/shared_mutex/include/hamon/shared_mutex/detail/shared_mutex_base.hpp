/**
 *	@file	shared_mutex_base.hpp
 *
 *	@brief	shared_mutex_base の定義
 */

#ifndef HAMON_SHARED_MUTEX_DETAIL_SHARED_MUTEX_BASE_HPP
#define HAMON_SHARED_MUTEX_DETAIL_SHARED_MUTEX_BASE_HPP

#include <hamon/chrono/time_point.hpp>
#include <mutex>
#include <condition_variable>
#include <climits>

namespace hamon
{

namespace detail
{

struct shared_mutex_base
{
private:
	std::mutex m_mut;
	std::condition_variable m_gate1;
	std::condition_variable m_gate2;
	unsigned m_state;

	static unsigned const kWriteEntered = 1U << (sizeof(unsigned) * CHAR_BIT - 1);
	static unsigned const kNReaders     = ~kWriteEntered;

public:
	shared_mutex_base() : m_state(0) {}
	~shared_mutex_base() = default;

	shared_mutex_base(shared_mutex_base const&)            = delete;
	shared_mutex_base& operator=(shared_mutex_base const&) = delete;

	// Exclusive ownership
	void lock()	// blocking
	{
		std::unique_lock<std::mutex> lk(m_mut);

		while (m_state & kWriteEntered)
		{
			m_gate1.wait(lk);
		}

		m_state |= kWriteEntered;

		while (m_state & kNReaders)
		{
			m_gate2.wait(lk);
		}
	}

	bool try_lock()
	{
		std::unique_lock<std::mutex> lk(m_mut);

		if (m_state == 0)
		{
			m_state = kWriteEntered;
			return true;
		}

		return false;
	}

	template <typename Clock, typename Duration>
	bool try_lock_until(hamon::chrono::time_point<Clock, Duration> const& abs_time)
	{
		// TODO hamon::chrono::time_point から std::chrono::time_point への変換を簡単にする
		using std_period = std::ratio<Duration::period::num, Duration::period::den>;
		using std_duration = std::chrono::duration<typename Duration::rep, std_period>;
		using std_time_point = std::chrono::time_point<std::chrono::system_clock, std_duration>;
		auto const std_abs_time = std_time_point{std_duration{abs_time.time_since_epoch().count()}};

		std::unique_lock<std::mutex> lk(m_mut);
		if (m_state & kWriteEntered)
		{
			while (true)
			{
				std::cv_status status = m_gate1.wait_until(lk, std_abs_time);
				if ((m_state & kWriteEntered) == 0)
				{
					break;
				}

				if (status == std::cv_status::timeout)
				{
					return false;
				}
			}
		}

		m_state |= kWriteEntered;

		if (m_state & kNReaders)
		{
			while (true)
			{
				std::cv_status status = m_gate2.wait_until(lk, std_abs_time);
				if ((m_state & kNReaders) == 0)
				{
					break;
				}

				if (status == std::cv_status::timeout)
				{
					m_state &= ~kWriteEntered;
					m_gate1.notify_all();
					return false;
				}
			}
		}

		return true;
	}

	void unlock()
	{
		{
			std::lock_guard<std::mutex> _(m_mut);
			m_state = 0;
		}
		m_gate1.notify_all();
	}

	// Shared ownership
	void lock_shared() // blocking
	{
		std::unique_lock<std::mutex> lk(m_mut);

		while ((m_state & kWriteEntered) || (m_state & kNReaders) == kNReaders)
		{
			m_gate1.wait(lk);
		}

		unsigned num_readers = (m_state & kNReaders) + 1;
		m_state &= ~kNReaders;
		m_state |= num_readers;
	}

	bool try_lock_shared()
	{
		std::unique_lock<std::mutex> lk(m_mut);
		unsigned num_readers = m_state & kNReaders;

		if (!(m_state & kWriteEntered) && num_readers != kNReaders)
		{
			++num_readers;
			m_state &= ~kNReaders;
			m_state |= num_readers;
			return true;
		}

		return false;
	}

	template <typename Clock, typename Duration>
	bool try_lock_shared_until(hamon::chrono::time_point<Clock, Duration> const& abs_time)
	{
		// TODO hamon::chrono::time_point から std::chrono::time_point への変換を簡単にする
		using std_period = std::ratio<Duration::period::num, Duration::period::den>;
		using std_duration = std::chrono::duration<typename Duration::rep, std_period>;
		using std_time_point = std::chrono::time_point<std::chrono::system_clock, std_duration>;
		auto const std_abs_time = std_time_point{std_duration{abs_time.time_since_epoch().count()}};

		std::unique_lock<std::mutex> lk(m_mut);
		if ((m_state & kWriteEntered) ||
			(m_state & kNReaders) == kNReaders)
		{
			while (true)
			{
				std::cv_status status = m_gate1.wait_until(lk, std_abs_time);
				if ((m_state & kWriteEntered) == 0 &&
					(m_state & kNReaders) < kNReaders)
				{
					break;
				}

				if (status == std::cv_status::timeout)
				{
					return false;
				}
			}
		}

		unsigned num_readers = (m_state & kNReaders) + 1;
		m_state &= ~kNReaders;
		m_state |= num_readers;
		return true;
	}

	void unlock_shared()
	{
		std::unique_lock<std::mutex> lk(m_mut);
		unsigned num_readers = (m_state & kNReaders) - 1;
		m_state &= ~kNReaders;
		m_state |= num_readers;

		if (m_state & kWriteEntered)
		{
			if (num_readers == 0)
			{
				lk.unlock();
				m_gate2.notify_one();
			}
		}
		else
		{
			if (num_readers == kNReaders - 1)
			{
				lk.unlock();
				m_gate1.notify_one();
			}
		}
	}

	//     typedef implementation-defined native_handle_type; // See 30.2.3
	//     native_handle_type native_handle(); // See 30.2.3
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SHARED_MUTEX_DETAIL_SHARED_MUTEX_BASE_HPP
