/**
 *	@file	month_day.hpp
 *
 *	@brief	month_day の定義
 */

#ifndef HAMON_CHRONO_MONTH_DAY_HPP
#define HAMON_CHRONO_MONTH_DAY_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::month_day;
using std::chrono::month_day_last;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/month.hpp>
#include <hamon/chrono/day.hpp>
#include <hamon/chrono/last_spec.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.8.9 Class month_day[time.cal.md]

class month_day
{
	chrono::month m_;
	chrono::day d_;

public:
	month_day() = default;

	HAMON_CXX11_CONSTEXPR
	month_day(chrono::month const& m, chrono::day const& d) HAMON_NOEXCEPT
		// [time.cal.md.members]/1
		: m_(m), d_(d)
	{}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::month
	month() const HAMON_NOEXCEPT
	{
		// [time.cal.md.members]/2
		return m_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::day
	day() const HAMON_NOEXCEPT
	{
		// [time.cal.md.members]/3
		return d_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	ok() const HAMON_NOEXCEPT
	{
		// [time.cal.md.members]/4
		// Returns: true if m_.ok() is true, 1d <= d_, and d_ is less than or equal to the number of days in month m_;
		// otherwise returns false. When m_ == February, the number of days is considered to be 29.

		return m_.ok() &&
			(chrono::day(1) <= d_ && d_ <= chrono::day(days_in_month(unsigned{m_})));
	}

private:
	static HAMON_CXX11_CONSTEXPR unsigned
	days_in_month(unsigned m)
	{
		return
			(m == 2) ?
				29 :
			(m == 4 || m == 6 || m == 9 || m == 11) ?
				30 :
				31;
	}
};

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(month_day const& x, month_day const& y) HAMON_NOEXCEPT
{
	// [time.cal.md.nonmembers]/1
	return x.month() == y.month() && x.day() == y.day();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR hamon::strong_ordering
operator<=>(month_day const& x, month_day const& y) HAMON_NOEXCEPT
{
	// [time.cal.md.nonmembers]/2
	if (auto c = x.month() <=> y.month(); c != 0)
	{
		return c;
	}

	return x.day() <=> y.day();
}

#else

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(month_day const& x, month_day const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(month_day const& x, month_day const& y) HAMON_NOEXCEPT
{
	return
		x.month() != y.month() ?
			x.month() < y.month() :
		x.day() < y.day();
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(month_day const& x, month_day const& y) HAMON_NOEXCEPT
{
	return y < x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(month_day const& x, month_day const& y) HAMON_NOEXCEPT
{
	return !(x > y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(month_day const& x, month_day const& y) HAMON_NOEXCEPT
{
	return !(x < y);
}

#endif

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, month_day const& md)
{
	// [time.cal.md.nonmembers]/3
	return os << format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{:L}/{}"), md.month(), md.day());
}

template <typename charT, typename traits, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	charT const* fmt,
	month_day& md,
	hamon::basic_string<charT, traits, Alloc>* abbrev = nullptr,
	minutes* offset = nullptr)
{
	// [time.cal.md.nonmembers]/4
	// TODO

	// [time.cal.md.nonmembers]/3
	return is;
}
#endif

// 30.8.10 Class month_day_last[time.cal.mdlast]

class month_day_last
{
	chrono::month m_;

public:
	HAMON_CXX11_CONSTEXPR explicit
	month_day_last(chrono::month const& m) HAMON_NOEXCEPT
		// [time.cal.mdlast]/4
		: m_(m)
	{}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::month
	month() const HAMON_NOEXCEPT
	{
		// [time.cal.mdlast]/5
		return m_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	ok() const HAMON_NOEXCEPT
	{
		// [time.cal.mdlast]/6
		return m_.ok();
	}
};

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(month_day_last const& x, month_day_last const& y) HAMON_NOEXCEPT
{
	// [time.cal.mdlast]/7
	return x.month() == y.month();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR hamon::strong_ordering
operator<=>(month_day_last const& x, month_day_last const& y) HAMON_NOEXCEPT
{
	// [time.cal.mdlast]/8
	return x.month() <=> y.month();
}

#else

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(month_day_last const& x, month_day_last const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(month_day_last const& x, month_day_last const& y) HAMON_NOEXCEPT
{
	return x.month() < y.month();
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(month_day_last const& x, month_day_last const& y) HAMON_NOEXCEPT
{
	return y < x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(month_day_last const& x, month_day_last const& y) HAMON_NOEXCEPT
{
	return !(x > y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(month_day_last const& x, month_day_last const& y) HAMON_NOEXCEPT
{
	return !(x < y);
}

#endif

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, month_day_last const& mdl)
{
	// [time.cal.mdlast]/9
	return os << format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{:L}/last"), mdl.month());
}
#endif

// 30.8.18 Conventional syntax operators[time.cal.operators]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_day
operator/(month const& m, day const& d) HAMON_NOEXCEPT
{
	// [time.cal.operators]/7
	return {m, d};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_day
operator/(month const& m, int d) HAMON_NOEXCEPT
{
	// [time.cal.operators]/8
	return m / day(static_cast<unsigned>(d));
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_day
operator/(int m, day const& d) HAMON_NOEXCEPT
{
	// [time.cal.operators]/9
	return month(static_cast<unsigned>(m)) / d;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_day
operator/(day const& d, month const& m) HAMON_NOEXCEPT
{
	// [time.cal.operators]/10
	return m / d;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_day
operator/(day const& d, int m) HAMON_NOEXCEPT
{
	// [time.cal.operators]/11
	return month(static_cast<unsigned>(m)) / d;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_day_last
operator/(month const& m, last_spec) HAMON_NOEXCEPT
{
	// [time.cal.operators]/12
	return month_day_last{m};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_day_last
operator/(int m, last_spec) HAMON_NOEXCEPT
{
	// [time.cal.operators]/13
	return month(static_cast<unsigned>(m)) / last;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_day_last
operator/(last_spec, month const& m) HAMON_NOEXCEPT
{
	// [time.cal.operators]/14
	return m / last;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_day_last
operator/(last_spec, int m) HAMON_NOEXCEPT
{
	// [time.cal.operators]/15
	return month(static_cast<unsigned>(m)) / last;
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_MONTH_DAY_HPP
