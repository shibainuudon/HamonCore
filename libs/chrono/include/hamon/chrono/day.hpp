﻿/**
 *	@file	day.hpp
 *
 *	@brief	day の定義
 */

#ifndef HAMON_CHRONO_DAY_HPP
#define HAMON_CHRONO_DAY_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::day;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/compare/strong_ordering.hpp>

namespace hamon {
namespace chrono {

// 30.8.3 Class day[time.cal.day]

class day
{
	unsigned char d_;

public:
	day() = default;

	HAMON_CXX11_CONSTEXPR explicit
	day(unsigned d) HAMON_NOEXCEPT
		// [time.cal.day.members]/1
		: d_(static_cast<unsigned char>(d))
	{}

	HAMON_CXX14_CONSTEXPR day& operator++() HAMON_NOEXCEPT
	{
		// [time.cal.day.members]/2
		++d_;

		// [time.cal.day.members]/3
		return *this;
	}

	HAMON_CXX14_CONSTEXPR day operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;

		// [time.cal.day.members]/4
		++(*this);

		// [time.cal.day.members]/5
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR day& operator--() HAMON_NOEXCEPT
	{
		// [time.cal.day.members]/6
		--d_;

		// [time.cal.day.members]/7
		return *this;
	}

	HAMON_CXX14_CONSTEXPR day operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;

		// [time.cal.day.members]/8
		--(*this);

		// [time.cal.day.members]/9
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR day& operator+=(days const& d) HAMON_NOEXCEPT
	{
		// [time.cal.day.members]/10
		*this = day(d_ + d.count());

		// [time.cal.day.members]/11
		return *this;
	}

	HAMON_CXX14_CONSTEXPR day& operator-=(days const& d) HAMON_NOEXCEPT
	{
		// [time.cal.day.members]/12
		*this = day(d_ - d.count());

		// [time.cal.day.members]/13
		return *this;
	}

	HAMON_CXX11_CONSTEXPR explicit operator unsigned() const HAMON_NOEXCEPT
	{
		// [time.cal.day.members]/14
		return d_;
	}

	HAMON_CXX11_CONSTEXPR bool ok() const HAMON_NOEXCEPT
	{
		// [time.cal.day.members]/15
		return 1 <= d_ && d_ <= 31;
	}
};

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(day const& x, day const& y) HAMON_NOEXCEPT
{
	// [time.cal.day.nonmembers]/1
	return unsigned{x} == unsigned{y};
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR hamon::strong_ordering
operator<=>(day const& x, day const& y) HAMON_NOEXCEPT
{
	// [time.cal.day.nonmembers]/2
	return unsigned{x} <=> unsigned{y};
}

#else

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(day const& x, day const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(day const& x, day const& y) HAMON_NOEXCEPT
{
	return unsigned{x} < unsigned{y};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(day const& x, day const& y) HAMON_NOEXCEPT
{
	return y < x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(day const& x, day const& y) HAMON_NOEXCEPT
{
	return !(x > y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(day const& x, day const& y) HAMON_NOEXCEPT
{
	return !(x < y);
}

#endif

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR day
operator+(day const& x, days const& y) HAMON_NOEXCEPT
{
	// [time.cal.day.nonmembers]/3
	return day(unsigned{x} + y.count());
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR day
operator+(days const& x, day const& y) HAMON_NOEXCEPT
{
	// [time.cal.day.nonmembers]/4
	return y + x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR day
operator-(day const& x, days const& y) HAMON_NOEXCEPT
{
	// [time.cal.day.nonmembers]/5
	return day(unsigned{x} - y.count());
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR days
operator-(day const& x, day const& y) HAMON_NOEXCEPT
{
	// [time.cal.day.nonmembers]/6
	return days{int(unsigned{x}) - int(unsigned{y})};
}

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, day const& d)
{
	// [time.cal.day.nonmembers]/7
	return os << (d.ok() ?
		format(HAMON_STATICALLY_WIDEN(charT, "{:%d}"), d) :
		format(HAMON_STATICALLY_WIDEN(charT, "{:%d} is not a valid day"), d));
}

template <typename charT, typename traits, typename Alloc = allocator<charT>>
basic_istream<charT, traits>&
from_stream(basic_istream<charT, traits>& is, charT const* fmt,
			day& d, basic_string<charT, traits, Alloc>* abbrev = nullptr,
			minutes* offset = nullptr)
{
	// [time.cal.day.nonmembers]/8

	// [time.cal.day.nonmembers]/9
	return is;
}
#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_DAY_HPP
