/**
 *	@file	time_zone_link.hpp
 *
 *	@brief	time_zone_link の定義
 */

#ifndef HAMON_CHRONO_TIME_ZONE_LINK_HPP
#define HAMON_CHRONO_TIME_ZONE_LINK_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::time_zone_link;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/compare/strong_ordering.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.11.9 Class time_zone_link[time.zone.link]

class time_zone_link
{
public:
	time_zone_link(time_zone_link&&) = default;
	time_zone_link& operator=(time_zone_link&&) = default;

	// unspecified additional constructors
	explicit
	time_zone_link(hamon::string_view name, hamon::string_view target)
		: m_name{ name }, m_target{ target } {}

	HAMON_NODISCARD hamon::string_view name() const noexcept
	{
		// [time.zone.link.members]/1
		return m_name;
	}

	HAMON_NODISCARD hamon::string_view target() const noexcept
	{
		// [time.zone.link.members]/2
		return m_target;
	}

private:
	hamon::string m_name;
	// TODO TZDB instead of the name we can store the pointer to a zone. These
	// pointers are immutable. This makes it possible to directly return a
	// pointer in the time_zone in the 'locate_zone' function.
	hamon::string m_target;
};

// 30.11.9.3 Non-member functions[time.zone.link.nonmembers]

HAMON_NODISCARD inline bool
operator==(time_zone_link const& x, time_zone_link const& y)
{
	// [time.zone.link.nonmembers]/1
	return x.name() == y.name();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
HAMON_NODISCARD inline hamon::strong_ordering
operator<=>(time_zone_link const& x, time_zone_link const& y)
{
	// [time.zone.link.nonmembers]/2
	return x.name() <=> y.name();
}
#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TIME_ZONE_LINK_HPP
