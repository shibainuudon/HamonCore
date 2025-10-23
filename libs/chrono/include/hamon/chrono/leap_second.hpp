/**
 *	@file	leap_second.hpp
 *
 *	@brief	leap_second の定義
 */

#ifndef HAMON_CHRONO_LEAP_SECOND_HPP
#define HAMON_CHRONO_LEAP_SECOND_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::leap_second;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/sys_seconds.hpp>
#include <hamon/chrono/sys_time.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/detail/private_ctor_tag.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.11.8 Class leap_second[time.zone.leap]

class leap_second
{
public:
	leap_second(leap_second const&) = default;
	leap_second& operator=(leap_second const&) = default;

	// unspecified additional constructors
	explicit constexpr
	leap_second(hamon::chrono::detail::private_ctor_tag,
		sys_seconds date, seconds value)
		: m_date(date), m_value(value)
	{}

	HAMON_NODISCARD constexpr sys_seconds date() const noexcept
	{
		// [time.zone.leap.members]/1
		return m_date;
	}

	HAMON_NODISCARD constexpr seconds value() const noexcept
	{
		// [time.zone.leap.members]/2
		return m_value;
	}

private:
	sys_seconds m_date;
	seconds m_value;
};

// 30.11.8.3 Non-member functions[time.zone.leap.nonmembers]

HAMON_NODISCARD inline constexpr bool
operator==(leap_second const& x, leap_second const& y) noexcept
{
	// [time.zone.leap.nonmembers]/1
	return x.date() == y.date();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD inline constexpr hamon::strong_ordering
operator<=>(leap_second const& x, leap_second const& y) noexcept
{
	// [time.zone.leap.nonmembers]/2
	return x.date() <=> y.date();
}

#else

HAMON_NODISCARD inline bool
operator!=(leap_second const& x, leap_second const& y) noexcept
{
	return !(x == y);
}

HAMON_NODISCARD inline bool
operator<(leap_second const& x, leap_second const& y) noexcept
{
	return x.date() < y.date();
}

HAMON_NODISCARD inline bool
operator>(leap_second const& x, leap_second const& y) noexcept
{
	return y < x;
}

HAMON_NODISCARD inline bool
operator<=(leap_second const& x, leap_second const& y) noexcept
{
	return !(x > y);
}

HAMON_NODISCARD inline bool
operator>=(leap_second const& x, leap_second const& y) noexcept
{
	return !(x < y);
}

#endif

template <typename Duration>
HAMON_NODISCARD constexpr bool
operator==(leap_second const& x, sys_time<Duration> const& y) noexcept
{
	// [time.zone.leap.nonmembers]/3
	return x.date() == y;
}

template <typename Duration>
HAMON_NODISCARD constexpr bool
operator<(leap_second const& x, sys_time<Duration> const& y) noexcept
{
	// [time.zone.leap.nonmembers]/4
	return x.date() < y;
}

template <typename Duration>
HAMON_NODISCARD constexpr bool
operator<(sys_time<Duration> const& x, leap_second const& y) noexcept
{
	// [time.zone.leap.nonmembers]/5
	return x < y.date();
}

template <typename Duration>
HAMON_NODISCARD constexpr bool
operator>(leap_second const& x, sys_time<Duration> const& y) noexcept
{
	// [time.zone.leap.nonmembers]/6
	return y < x;
}

template <typename Duration>
HAMON_NODISCARD constexpr bool
operator>(sys_time<Duration> const& x, leap_second const& y) noexcept
{
	// [time.zone.leap.nonmembers]/7
	return y < x;
}

template <typename Duration>
HAMON_NODISCARD constexpr bool
operator<=(leap_second const& x, sys_time<Duration> const& y) noexcept
{
	// [time.zone.leap.nonmembers]/8
	return !(y < x);
}

template <typename Duration>
HAMON_NODISCARD constexpr bool
operator<=(sys_time<Duration> const& x, leap_second const& y) noexcept
{
	// [time.zone.leap.nonmembers]/9
	return !(y < x);
}

template <typename Duration>
HAMON_NODISCARD constexpr bool
operator>=(leap_second const& x, sys_time<Duration> const& y) noexcept
{
	// [time.zone.leap.nonmembers]/10
	return !(x < y);
}

template <typename Duration>
HAMON_NODISCARD constexpr bool
operator>=(sys_time<Duration> const& x, leap_second const& y) noexcept
{
	// [time.zone.leap.nonmembers]/11
	return !(x < y);
}

// TODO
//#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
//template <typename Duration>
//requires hamon::three_way_comparable_with<sys_seconds, sys_time<Duration>>
//HAMON_NODISCARD constexpr auto
//operator<=>(leap_second const& x, sys_time<Duration> const& y) noexcept
//{
//	// [time.zone.leap.nonmembers]/12
//	return x.date() <=> y;
//}
//#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_LEAP_SECOND_HPP
