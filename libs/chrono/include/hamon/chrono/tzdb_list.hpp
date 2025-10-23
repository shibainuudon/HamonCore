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
#include <hamon/chrono/detail/tz.hpp>
#include <hamon/chrono/detail/private_ctor_tag.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/next.hpp>
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
	explicit tzdb_list(hamon::chrono::detail::private_ctor_tag)
	{
		chrono::detail::init_tzdb(m_tzdb.emplace_front(), m_rules.emplace_front());
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
		m_rules.erase_after(hamon::next(m_rules.cbegin(), hamon::distance(m_tzdb.cbegin(), p)));
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
	hamon::forward_list<detail::tz::rules_storage_type> m_rules;
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TZDB_LIST_HPP
