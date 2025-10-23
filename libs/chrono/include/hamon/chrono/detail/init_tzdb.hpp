/**
 *	@file	init_tzdb.hpp
 *
 *	@brief	init_tzdb の定義
 */

#ifndef HAMON_CHRONO_DETAIL_INIT_TZDB_HPP
#define HAMON_CHRONO_DETAIL_INIT_TZDB_HPP

#include <hamon/chrono/detail/tz.hpp>
#include <hamon/chrono/detail/parse_tzdata.hpp>
#include <hamon/chrono/detail/parse_leap_seconds.hpp>
#include <hamon/chrono/tzdb.hpp>
#include <hamon/algorithm/ranges/sort.hpp>
#include <sstream>

namespace hamon {
namespace chrono {
namespace detail {

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Woverlength-strings")

inline void init_tzdb(hamon::chrono::tzdb& tzdb, tz::rules_storage_type& rules)
{
	{
		const char* s =
#include <hamon/chrono/detail/tzdata.zi>
		;
		std::istringstream tzdata(s);

		parse_tzdata(tzdb, rules, tzdata);

		hamon::ranges::sort(tzdb.zones);
		hamon::ranges::sort(tzdb.links);
		hamon::ranges::sort(rules, {}, [](tz::rules_storage_type::const_reference p) { return p.first; });
	}
	{
		const char* s =
#include <hamon/chrono/detail/leap-seconds.list>
		;
		std::istringstream leap_seconds_data(s);
		parse_leap_seconds(tzdb.leap_seconds, leap_seconds_data);
	}
}

HAMON_WARNING_POP()

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_INIT_TZDB_HPP
