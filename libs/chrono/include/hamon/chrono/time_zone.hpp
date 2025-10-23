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
#include <hamon/chrono/detail/tz.hpp>
#include <hamon/chrono/detail/private_ctor_tag.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.11.5 Class time_zone[time.zone.timezone]

class time_zone
{
public:
	time_zone(time_zone&&) = default;
	time_zone& operator=(time_zone&&) = default;

	// unspecified additional constructors
	explicit
	time_zone(hamon::chrono::detail::private_ctor_tag,
		hamon::string name,
		hamon::vector<detail::tz::continuation_t> continuations,
		detail::tz::rules_storage_type const& rules_db)
		: m_name(hamon::move(name))
		, m_continuations(hamon::move(continuations))
		, m_rules_db(hamon::addressof(rules_db)) {}

	hamon::string_view name() const noexcept
	{
		return m_name;
	}

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

private:
	hamon::string m_name;
	// Note the first line has a name + continuation_t, the other lines
	// are just __continuations. So there is always at least one item in
	// the vector.
	hamon::vector<detail::tz::continuation_t> m_continuations;

	// Continuations often depend on a set of rules. The rules are stored in
	// parallel data structurs in tzdb_list. From the time_zone it's not possible
	// to find its associated tzdb entry and thus not possible to find its
	// associated rules. Therefore a link to the rules in stored in this class.
	detail::tz::rules_storage_type const* m_rules_db;
};

// 30.11.5.3 Non-member functions[time.zone.nonmembers]

HAMON_NODISCARD inline bool
operator==(time_zone const& x, time_zone const& y) noexcept
{
	// [time.zone.nonmembers]/1
	return x.name() == y.name();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD inline hamon::strong_ordering
operator<=>(time_zone const& x, time_zone const& y) noexcept
{
	// [time.zone.nonmembers]/2
	return x.name() <=> y.name();
}

#else

HAMON_NODISCARD inline bool
operator!=(time_zone const& x, time_zone const& y) noexcept
{
	return !(x == y);
}

HAMON_NODISCARD inline bool
operator<(time_zone const& x, time_zone const& y) noexcept
{
	return x.name() < y.name();
}

HAMON_NODISCARD inline bool
operator>(time_zone const& x, time_zone const& y) noexcept
{
	return y < x;
}

HAMON_NODISCARD inline bool
operator<=(time_zone const& x, time_zone const& y) noexcept
{
	return !(x > y);
}

HAMON_NODISCARD inline bool
operator>=(time_zone const& x, time_zone const& y) noexcept
{
	return !(x < y);
}

#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TIME_ZONE_HPP
