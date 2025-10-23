/**
 *	@file	locate_zone.hpp
 *
 *	@brief	locate_zone の定義
 */

#ifndef HAMON_CHRONO_LOCATE_ZONE_HPP
#define HAMON_CHRONO_LOCATE_ZONE_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::locate_zone;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/time_zone.hpp>
#include <hamon/chrono/get_tzdb.hpp>
#include <hamon/string_view.hpp>

namespace hamon {
namespace chrono {

// 30.11.2.3 Time zone database access[time.zone.db.access]

inline hamon::chrono::time_zone const*
locate_zone(hamon::string_view tz_name)
{
	// [time.zone.db.access]/6
	return hamon::chrono::get_tzdb().locate_zone(tz_name);
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_LOCATE_ZONE_HPP
