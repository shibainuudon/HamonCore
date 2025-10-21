/**
 *	@file	get_tzdb_list.hpp
 *
 *	@brief	get_tzdb_list の定義
 */

#ifndef HAMON_CHRONO_GET_TZDB_LIST_HPP
#define HAMON_CHRONO_GET_TZDB_LIST_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::get_tzdb_list;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/tzdb_list.hpp>

namespace hamon {
namespace chrono {

// 30.11.2.3 Time zone database access[time.zone.db.access]

inline hamon::chrono::tzdb_list& get_tzdb_list()
{
	static hamon::chrono::tzdb_list result;

	// [time.zone.db.access]/3
	return result;
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_GET_TZDB_LIST_HPP
