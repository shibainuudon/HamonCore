/**
 *	@file	tzdb_list.hpp
 *
 *	@brief	tzdb_list の定義
 */

#ifndef HAMON_CHRONO_TZDB_LIST_HPP
#define HAMON_CHRONO_TZDB_LIST_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::tzdb_list;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/tzdb.hpp>
#include <hamon/chrono/detail/init_tzdb.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/config.hpp>
#include <mutex>

namespace hamon {
namespace chrono {

// 30.11.2.2 Class tzdb_list[time.zone.db.list]

class tzdb_list
{
public:
	tzdb_list(tzdb_list const&) = delete;
	tzdb_list& operator=(tzdb_list const&) = delete;

	// unspecified additional constructors
	tzdb_list()
	{
		chrono::detail::init_tzdb(m_tzdb.emplace_front());
	}

	using const_iterator = hamon::forward_list<hamon::chrono::tzdb>::const_iterator;

	hamon::chrono::tzdb const& front() const noexcept
	{
#if !defined(HAMON_NO_THREADS)
		std::unique_lock<std::mutex> lk{ m_mutex };
#endif
		return m_tzdb.front();
	}

	const_iterator erase_after(const_iterator p)
	{
#if !defined(HAMON_NO_THREADS)
		std::unique_lock<std::mutex> lk{ m_mutex };
#endif
		return m_tzdb.erase_after(p);
	}

	const_iterator begin() const noexcept
	{
#if !defined(HAMON_NO_THREADS)
		std::unique_lock<std::mutex> lk{ m_mutex };
#endif
		return m_tzdb.begin();
	}

	const_iterator end() const noexcept
	{
		//  forward_list<T>::end does not access the list, so no need to take a lock.
		return m_tzdb.end();
	}

	const_iterator cbegin() const noexcept
	{
		// [time.zone.db.list]/12
		return this->begin();
	}

	const_iterator cend() const noexcept
	{
		// [time.zone.db.list]/13
		return this->end();
	}

private:
#if !defined(HAMON_NO_THREADS)
	mutable std::mutex m_mutex;
#endif
	hamon::forward_list<hamon::chrono::tzdb> m_tzdb;
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TZDB_LIST_HPP
