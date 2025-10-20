/**
 *	@file	tzdb.hpp
 *
 *	@brief	tzdb の定義
 */

#ifndef HAMON_CHRONO_TZDB_HPP
#define HAMON_CHRONO_TZDB_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::tzdb;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/time_zone.hpp>
#include <hamon/chrono/time_zone_link.hpp>
#include <hamon/chrono/leap_second.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/vector.hpp>

namespace hamon {
namespace chrono {

// 30.11.2.1 Class tzdb[time.zone.db.tzdb]

struct tzdb
{
	hamon::string                                version;
	hamon::vector<hamon::chrono::time_zone>      zones;
	hamon::vector<hamon::chrono::time_zone_link> links;
	hamon::vector<hamon::chrono::leap_second>    leap_seconds;

	const hamon::chrono::time_zone* locate_zone(hamon::string_view tz_name) const;
	const hamon::chrono::time_zone* current_zone() const;
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TZDB_HPP
