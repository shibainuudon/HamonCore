/**
 *	@file	time_zone.hpp
 *
 *	@brief	time_zone の定義
 */

#ifndef HAMON_CHRONO_TIME_ZONE_HPP
#define HAMON_CHRONO_TIME_ZONE_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::time_zone;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/sys_info.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/chrono/local_info.hpp>
#include <hamon/chrono/local_time.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/choose.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/common_type.hpp>

namespace hamon {
namespace chrono {

// 30.11.5 Class time_zone[time.zone.timezone]

class time_zone
{
public:
	time_zone(time_zone&&) = default;
	time_zone& operator=(time_zone&&) = default;

	// unspecified additional constructors

	hamon::string_view name() const noexcept;

	template <typename Duration>
	sys_info get_info(sys_time<Duration> const& st) const;

	template <typename Duration>
	local_info get_info(local_time<Duration> const& tp) const;

	template <typename Duration>
	sys_time<hamon::common_type_t<Duration, seconds>>
	to_sys(local_time<Duration> const& tp) const;

	template <typename Duration>
	sys_time<hamon::common_type_t<Duration, seconds>>
	to_sys(local_time<Duration> const& tp, choose z) const;

	template <typename Duration>
	local_time<hamon::common_type_t<Duration, seconds>>
	to_local(sys_time<Duration> const& tp) const;
};

// 30.11.5.3 Non-member functions[time.zone.nonmembers]

inline bool
operator==(time_zone const& x, time_zone const& y) noexcept
{
	// [time.zone.nonmembers]/1
	return x.name() == y.name();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
inline hamon::strong_ordering
operator<=>(time_zone const& x, time_zone const& y) noexcept
{
	// [time.zone.nonmembers]/2
	return x.name() <=> y.name();
}
#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TIME_ZONE_HPP
