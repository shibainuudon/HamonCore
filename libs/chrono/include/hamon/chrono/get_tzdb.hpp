/**
 *	@file	get_tzdb.hpp
 *
 *	@brief	get_tzdb の定義
 */

#ifndef HAMON_CHRONO_GET_TZDB_HPP
#define HAMON_CHRONO_GET_TZDB_HPP

#include <hamon/chrono/tzdb.hpp>
#include <hamon/chrono/get_tzdb_list.hpp>

namespace hamon {
namespace chrono {

// 30.11.2.3 Time zone database access[time.zone.db.access]

inline const hamon::chrono::tzdb& get_tzdb()
{
	// [time.zone.db.access]/5
	return hamon::chrono::get_tzdb_list().front();
}

}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_GET_TZDB_HPP
