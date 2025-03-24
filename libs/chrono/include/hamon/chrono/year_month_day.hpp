/**
 *	@file	year_month_day.hpp
 *
 *	@brief	year_month_day の定義
 */

#ifndef HAMON_CHRONO_YEAR_MONTH_DAY_HPP
#define HAMON_CHRONO_YEAR_MONTH_DAY_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::year_month_day;
using std::chrono::year_month_day_last;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/year.hpp>
#include <hamon/chrono/month.hpp>
#include <hamon/chrono/day.hpp>
#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/local_days.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/year_month.hpp>
#include <hamon/chrono/month_day.hpp>
#include <hamon/chrono/last_spec.hpp>
#include <hamon/chrono/detail/civil.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// [time.cal.ymdlast], class year_month_day_last
class year_month_day_last;

// 30.8.14 Class year_month_day[time.cal.ymd]

class year_month_day
{
	chrono::year  y_;
	chrono::month m_;
	chrono::day   d_;

public:
	year_month_day() = default;

	HAMON_CXX11_CONSTEXPR
	year_month_day(
		chrono::year const& y,
		chrono::month const& m,
		chrono::day const& d) HAMON_NOEXCEPT
		// [time.cal.ymd.members]/1
		: y_(y), m_(m), d_(d)
	{}

	HAMON_CXX11_CONSTEXPR
	year_month_day(year_month_day_last const& ymdl) HAMON_NOEXCEPT;

private:
	HAMON_CXX11_CONSTEXPR
	year_month_day(hamon::chrono::detail::civil const& c) HAMON_NOEXCEPT
		: y_(c.year), m_(c.month), d_(c.day)
	{}

public:
	HAMON_CXX11_CONSTEXPR
	year_month_day(sys_days const& dp) HAMON_NOEXCEPT
		// [time.cal.ymd.members]/3
		: year_month_day(hamon::chrono::detail::civil_from_days(
			dp.time_since_epoch().count()))
	{}

	HAMON_CXX11_CONSTEXPR explicit
	year_month_day(local_days const& dp) HAMON_NOEXCEPT
		// [time.cal.ymd.members]/5
		: year_month_day(sys_days{dp.time_since_epoch()})
	{}

	template <typename = void>	// [time.cal.ymd.members]/6
	HAMON_CXX14_CONSTEXPR year_month_day&
	operator+=(months const& m) HAMON_NOEXCEPT;

	template <typename = void>	// [time.cal.ymd.members]/9
	HAMON_CXX14_CONSTEXPR year_month_day&
	operator-=(months const& m) HAMON_NOEXCEPT;

	HAMON_CXX14_CONSTEXPR year_month_day&
	operator+=(years const& y) HAMON_NOEXCEPT;

	HAMON_CXX14_CONSTEXPR year_month_day&
	operator-=(years const& y) HAMON_NOEXCEPT;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::year
	year() const HAMON_NOEXCEPT
	{
		// [time.cal.ymd.members]/16
		return y_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::month
	month() const HAMON_NOEXCEPT
	{
		// [time.cal.ymd.members]/17
		return m_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::day
	day() const HAMON_NOEXCEPT
	{
		// [time.cal.ymd.members]/18
		return d_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR
	operator sys_days() const HAMON_NOEXCEPT
	{
		// [time.cal.ymd.members]/19
		return sys_days{days{hamon::chrono::detail::days_from_civil({
			static_cast<int>(year()),
			static_cast<unsigned>(month()),
			static_cast<unsigned>(day())})}};
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR explicit
	operator local_days() const HAMON_NOEXCEPT
	{
		// [time.cal.ymd.members]/22
		return local_days{sys_days{*this}.time_since_epoch()};
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool ok() const HAMON_NOEXCEPT;
};

// 30.8.18 Conventional syntax operators[time.cal.operators]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator/(year_month const& ym, day const& d) HAMON_NOEXCEPT
{
	// [time.cal.operators]/24
	return {ym.year(), ym.month(), d};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator/(year_month const& ym, int d) HAMON_NOEXCEPT
{
	// [time.cal.operators]/25
	return ym / day(static_cast<unsigned>(d));
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator/(year const& y, month_day const& md) HAMON_NOEXCEPT
{
	// [time.cal.operators]/26
	return y / md.month() / md.day();
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator/(int y, month_day const& md) HAMON_NOEXCEPT
{
	// [time.cal.operators]/27
	return year(y) / md;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator/(month_day const& md, year const& y) HAMON_NOEXCEPT
{
	// [time.cal.operators]/28
	return y / md;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator/(month_day const& md, int y) HAMON_NOEXCEPT
{
	// [time.cal.operators]/29
	return year(y) / md;
}

// 30.8.14.3 Non-member functions[time.cal.ymd.nonmembers]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(year_month_day const& x, year_month_day const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymd.nonmembers]/1
	return x.year() == y.year() && x.month() == y.month() && x.day() == y.day();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR hamon::strong_ordering
operator<=>(year_month_day const& x, year_month_day const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymd.nonmembers]/2
	if (auto c = x.year() <=> y.year(); c != 0)
	{
		return c;
	}

	if (auto c = x.month() <=> y.month(); c != 0)
	{
		return c;
	}

	return x.day() <=> y.day();
}

#else

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(year_month_day const& x, year_month_day const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(year_month_day const& x, year_month_day const& y) HAMON_NOEXCEPT
{
	return
		x.year() != y.year() ?
			x.year() < y.year() :
		x.month() != y.month() ?
			x.month() < y.month() :
		x.day() < y.day();
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(year_month_day const& x, year_month_day const& y) HAMON_NOEXCEPT
{
	return y < x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(year_month_day const& x, year_month_day const& y) HAMON_NOEXCEPT
{
	return !(x > y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(year_month_day const& x, year_month_day const& y) HAMON_NOEXCEPT
{
	return !(x < y);
}

#endif

template <typename = void>	// [time.cal.ymd.nonmembers]/3
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator+(year_month_day const& ymd, months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ymd.nonmembers]/4
	return (ymd.year() / ymd.month() + dm) / ymd.day();
}

template <typename = void>	// [time.cal.ymd.nonmembers]/6
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator+(months const& dm, year_month_day const& ymd) HAMON_NOEXCEPT
{
	// [time.cal.ymd.nonmembers]/7
	return ymd + dm;
}

template <typename = void>	// [time.cal.ymd.nonmembers]/8
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator-(year_month_day const& ymd, months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ymd.nonmembers]/9
	return ymd + (-dm);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator+(year_month_day const& ymd, years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ymd.nonmembers]/10
	return (ymd.year() + dy) / ymd.month() / ymd.day();
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator+(years const& dy, year_month_day const& ymd) HAMON_NOEXCEPT
{
	// [time.cal.ymd.nonmembers]/12
	return ymd + dy;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day
operator-(year_month_day const& ymd, years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ymd.nonmembers]/13
	return ymd + (-dy);
}

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, year_month_day const& ymd)
{
	// [time.cal.ymd.nonmembers]/14
	return os << (ymd.ok() ?
		format(HAMON_STATICALLY_WIDEN(charT, "{:%F}"), ymd) :
		format(HAMON_STATICALLY_WIDEN(charT, "{:%F} is not a valid date"), ymd));
}

template <typename charT, typename traits, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	charT const* fmt,
	year_month_day& ymd,
	hamon::basic_string<charT, traits, Alloc>* abbrev = nullptr,
	minutes* offset = nullptr)
{
	// [time.cal.ymd.nonmembers]/15
	// TODO

	// [time.cal.ymd.nonmembers]/16
	return is;
}
#endif

// 30.8.15 Class year_month_day_last[time.cal.ymdlast]

class year_month_day_last
{
	chrono::year y_;
	chrono::month_day_last mdl_;

public:
	HAMON_CXX11_CONSTEXPR
	year_month_day_last(
		chrono::year const& y,
		chrono::month_day_last const& mdl) HAMON_NOEXCEPT
		// [time.cal.ymdlast.members]/1
		: y_(y), mdl_(mdl)
	{}

	template <typename = void>	// [time.cal.ymdlast.members]/2
	HAMON_CXX14_CONSTEXPR year_month_day_last&
	operator+=(months const& m) HAMON_NOEXCEPT;

	template <typename = void>	// [time.cal.ymdlast.members]/5
	HAMON_CXX14_CONSTEXPR year_month_day_last&
	operator-=(months const& m) HAMON_NOEXCEPT;

	HAMON_CXX14_CONSTEXPR year_month_day_last&
	operator+=(years const& y) HAMON_NOEXCEPT;

	HAMON_CXX14_CONSTEXPR year_month_day_last&
	operator-=(years const& y) HAMON_NOEXCEPT;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::year
	year() const HAMON_NOEXCEPT
	{
		// [time.cal.ymdlast.members]/12
		return y_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::month
	month() const HAMON_NOEXCEPT
	{
		// [time.cal.ymdlast.members]/13
		return mdl_.month();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::month_day_last
	month_day_last() const HAMON_NOEXCEPT
	{
		// [time.cal.ymdlast.members]/14
		return mdl_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::day
	day() const HAMON_NOEXCEPT
	{
		// [time.cal.ymdlast.members]/15
		return
			month() == chrono::month{2} ?
				year().is_leap() ?
					chrono::day{29} :
					chrono::day{28} :
			month() == chrono::month{4} ||
			month() == chrono::month{6} ||
			month() == chrono::month{9} ||
			month() == chrono::month{11} ?
				chrono::day{30} :
				chrono::day{31};
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR
	operator sys_days() const HAMON_NOEXCEPT
	{
		// [time.cal.ymdlast.members]/17
		return sys_days{year()/month()/day()};
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR explicit
	operator local_days() const HAMON_NOEXCEPT
	{
		// [time.cal.ymdlast.members]/18
		return local_days{sys_days{*this}.time_since_epoch()};
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool ok() const HAMON_NOEXCEPT
	{
		// [time.cal.ymdlast.members]/19
		return y_.ok() && mdl_.ok();
	}
};

// 30.8.18 Conventional syntax operators[time.cal.operators]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator/(year_month const& ym, last_spec) HAMON_NOEXCEPT
{
	// [time.cal.operators]/30
	return {ym.year(), month_day_last{ym.month()}};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator/(year const& y, month_day_last const& mdl) HAMON_NOEXCEPT
{
	// [time.cal.operators]/31
	return {y, mdl};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator/(int y, month_day_last const& mdl) HAMON_NOEXCEPT
{
	// [time.cal.operators]/32
	return year(y) / mdl;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator/(month_day_last const& mdl, year const& y) HAMON_NOEXCEPT
{
	// [time.cal.operators]/33
	return y / mdl;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator/(month_day_last const& mdl, int y) HAMON_NOEXCEPT
{
	// [time.cal.operators]/34
	return year(y) / mdl;
}

// 30.8.15.3 Non-member functions[time.cal.ymdlast.nonmembers]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(year_month_day_last const& x, year_month_day_last const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.nonmembers]/1
	return x.year() == y.year() && x.month_day_last() == y.month_day_last();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR hamon::strong_ordering
operator<=>(year_month_day_last const& x, year_month_day_last const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.nonmembers]/2
	if (auto c = x.year() <=> y.year(); c != 0)
	{
		return c;
	}

	return x.month_day_last() <=> y.month_day_last();
}

#else

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(year_month_day_last const& x, year_month_day_last const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(year_month_day_last const& x, year_month_day_last const& y) HAMON_NOEXCEPT
{
	return
		x.year() != y.year() ?
			x.year() < y.year() :
		x.month_day_last() < y.month_day_last();
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(year_month_day_last const& x, year_month_day_last const& y) HAMON_NOEXCEPT
{
	return y < x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(year_month_day_last const& x, year_month_day_last const& y) HAMON_NOEXCEPT
{
	return !(x > y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(year_month_day_last const& x, year_month_day_last const& y) HAMON_NOEXCEPT
{
	return !(x < y);
}

#endif

template <typename = void>	// [time.cal.ymdlast.nonmembers]/3
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator+(year_month_day_last const& ymdl, months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.nonmembers]/4
	return (ymdl.year() / ymdl.month() + dm) / last;
}

template <typename = void>	// [time.cal.ymdlast.nonmembers]/5
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator+(months const& dm, year_month_day_last const& ymdl) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.nonmembers]/6
	return ymdl + dm;
}

template <typename = void>	// [time.cal.ymdlast.nonmembers]/7
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator-(year_month_day_last const& ymdl, months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.nonmembers]/8
	return ymdl + (-dm);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator+(year_month_day_last const& ymdl, years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.nonmembers]/9
	return {ymdl.year()+dy, ymdl.month_day_last()};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator+(years const& dy, year_month_day_last const& ymdl) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.nonmembers]/10
	return ymdl + dy;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_day_last
operator-(year_month_day_last const& ymdl, years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.nonmembers]/11
	return ymdl + (-dy);
}

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, year_month_day_last const& ymdl)
{
	return os << format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{}/{:L}"),
		ymdl.year(), ymdl.month_day_last());
}
#endif

// 30.8.14.2 Member functions[time.cal.ymd.members]

inline HAMON_CXX11_CONSTEXPR
year_month_day::year_month_day(year_month_day_last const& ymdl) HAMON_NOEXCEPT
	// [time.cal.ymd.members]/2
	: y_(ymdl.year()), m_(ymdl.month()), d_(ymdl.day())
{}

template <typename>	// [time.cal.ymd.members]/6
inline HAMON_CXX14_CONSTEXPR year_month_day&
year_month_day::operator+=(months const& m) HAMON_NOEXCEPT
{
	// [time.cal.ymd.members]/7
	*this = *this + m;

	// [time.cal.ymd.members]/8
	return *this;
}

template <typename>	// [time.cal.ymd.members]/9
inline HAMON_CXX14_CONSTEXPR year_month_day&
year_month_day::operator-=(months const& m) HAMON_NOEXCEPT
{
	// [time.cal.ymd.members]/10
	*this = *this - m;

	// [time.cal.ymd.members]/11
	return *this;
}

inline HAMON_CXX14_CONSTEXPR year_month_day&
year_month_day::operator+=(years const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymd.members]/12
	*this = *this + y;

	// [time.cal.ymd.members]/13
	return *this;
}

inline HAMON_CXX14_CONSTEXPR year_month_day&
year_month_day::operator-=(years const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymd.members]/14
	*this = *this - y;

	// [time.cal.ymd.members]/15
	return *this;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
year_month_day::ok() const HAMON_NOEXCEPT
{
	// [time.cal.ymd.members]/23
	return y_.ok() && m_.ok() &&
		1_d <= d_ && d_ <= (y_/m_/last).day();
}

// 30.8.15.2 Member functions[time.cal.ymdlast.members]

template <typename>	// [time.cal.ymdlast.members]/2
inline HAMON_CXX14_CONSTEXPR year_month_day_last&
year_month_day_last::operator+=(months const& m) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.members]/3
	*this = *this + m;

	// [time.cal.ymdlast.members]/4
	return *this;
}

template <typename>	// [time.cal.ymdlast.members]/5
inline HAMON_CXX14_CONSTEXPR year_month_day_last&
year_month_day_last::operator-=(months const& m) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.members]/6
	*this = *this - m;

	// [time.cal.ymdlast.members]/7
	return *this;
}

inline HAMON_CXX14_CONSTEXPR year_month_day_last&
year_month_day_last::operator+=(years const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.members]/8
	*this = *this + y;

	// [time.cal.ymdlast.members]/9
	return *this;
}

inline HAMON_CXX14_CONSTEXPR year_month_day_last&
year_month_day_last::operator-=(years const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymdlast.members]/10
	*this = *this - y;

	// [time.cal.ymdlast.members]/11
	return *this;
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_YEAR_MONTH_DAY_HPP
