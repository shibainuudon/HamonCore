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
#include <hamon/algorithm/ranges/lower_bound.hpp>
#include <hamon/stdexcept/runtime_error.hpp>
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

	hamon::chrono::time_zone const*
	locate_zone(hamon::string_view tz_name) const
	{
		auto result = locate_zone_impl(tz_name);
		if (result == nullptr)
		{
			// [time.zone.db.tzdb]/3
			hamon::detail::throw_runtime_error("tzdb: requested time zone not found");
		}
		return result;
	}

	hamon::chrono::time_zone const*
	current_zone() const;
	// TODO

private:
	hamon::chrono::time_zone const*
	find_in_zones(string_view tz_name) const noexcept
	{
		// [time.zone.db.tzdb]/1 より、zones はソート済み
		auto it = hamon::ranges::lower_bound(zones, tz_name, {}, &time_zone::name);
		if (it != zones.end() && it->name() == tz_name)
		{
			return hamon::addressof(*it);
		}

		return nullptr;
	}

	hamon::chrono::time_zone_link const*
	find_in_links(string_view tz_name) const noexcept
	{
		// [time.zone.db.tzdb]/1 より、links はソート済み
		auto it = hamon::ranges::lower_bound(links, tz_name, {}, &time_zone_link::name);
		if (it != links.end() && it->name() == tz_name)
		{
			return hamon::addressof(*it);
		}

		return nullptr;
	}

	hamon::chrono::time_zone const*
	locate_zone_impl(hamon::string_view tz_name) const
	{
		// [time.zone.db.tzdb]/2.1
		auto const* tz = find_in_zones(tz_name);
		if (tz != nullptr)
		{
			return tz;
		}

		// [time.zone.db.tzdb]/2.2
		auto const* tz_l = find_in_links(tz_name);
		if (tz_l != nullptr)
		{
			return find_in_zones(tz_l->target());
		}

		return nullptr;
	}

};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TZDB_HPP
