/**
 *	@file	year_month_weekday.hpp
 *
 *	@brief	year_month_weekday の定義
 */

#ifndef HAMON_CHRONO_YEAR_MONTH_WEEKDAY_HPP
#define HAMON_CHRONO_YEAR_MONTH_WEEKDAY_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::year_month_weekday;
using std::chrono::year_month_weekday_last;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/year.hpp>
#include <hamon/chrono/month.hpp>
#include <hamon/chrono/weekday.hpp>
#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/local_days.hpp>
#include <hamon/chrono/year_month_day.hpp>
#include <hamon/chrono/year_month.hpp>
#include <hamon/chrono/month_weekday.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.8.16 Class year_month_weekday[time.cal.ymwd]

class year_month_weekday
{
	chrono::year y_;
	chrono::month m_;
	chrono::weekday_indexed wdi_;

public:
	year_month_weekday() = default;

	HAMON_CXX11_CONSTEXPR
	year_month_weekday(
		chrono::year const& y,
		chrono::month const& m,
		chrono::weekday_indexed const& wdi) HAMON_NOEXCEPT
		// [time.cal.ymwd.members]/1
		: y_(y), m_(m), wdi_(wdi)
	{}

private:
	static HAMON_CXX11_CONSTEXPR year_month_weekday
	from_sys_days_impl(year_month_day ymd, chrono::weekday wd) HAMON_NOEXCEPT
	{
		return year_month_weekday{ymd.year(), ymd.month(),
			wd[(static_cast<unsigned>(ymd.day()) - 1) / 7 + 1]};
	}

	static HAMON_CXX11_CONSTEXPR year_month_weekday
	from_sys_days(sys_days const& sysd) HAMON_NOEXCEPT
	{
		return from_sys_days_impl(year_month_day{sysd}, chrono::weekday{sysd});
	}

	static HAMON_CXX11_CONSTEXPR sys_days
	to_sys_days_impl(year_month_weekday const& ymwd, sys_days const& sysd) HAMON_NOEXCEPT
	{
		return sysd + (ymwd.wdi_.weekday() - chrono::weekday(sysd) + days{(ymwd.wdi_.index() - 1) * 7});
	}

	static HAMON_CXX11_CONSTEXPR sys_days
	to_sys_days(year_month_weekday const& ymwd) HAMON_NOEXCEPT
	{
		return to_sys_days_impl(ymwd, sys_days(ymwd.y_ / ymwd.m_ / 1));
	}

public:
	HAMON_CXX11_CONSTEXPR
	year_month_weekday(sys_days const& dp) HAMON_NOEXCEPT
		// [time.cal.ymwd.members]/2
		: year_month_weekday(from_sys_days(dp))
	{}

	HAMON_CXX11_CONSTEXPR explicit
	year_month_weekday(local_days const& dp) HAMON_NOEXCEPT
		// [time.cal.ymwd.members]/4
		: year_month_weekday(sys_days{dp.time_since_epoch()})
	{}

	template <typename = void>	// [time.cal.ymwd.members]/5
	HAMON_CXX14_CONSTEXPR year_month_weekday&
	operator+=(months const& m) HAMON_NOEXCEPT;

	template <typename = void>	// [time.cal.ymwd.members]/8
	HAMON_CXX14_CONSTEXPR year_month_weekday&
	operator-=(months const& m) HAMON_NOEXCEPT;

	HAMON_CXX14_CONSTEXPR year_month_weekday&
	operator+=(years const& y) HAMON_NOEXCEPT;

	HAMON_CXX14_CONSTEXPR year_month_weekday&
	operator-=(years const& y) HAMON_NOEXCEPT;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::year
	year() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwd.members]/15
		return y_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::month
	month() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwd.members]/16
		return m_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::weekday
	weekday() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwd.members]/17
		return wdi_.weekday();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR unsigned
	index() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwd.members]/18
		return wdi_.index();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::weekday_indexed
	weekday_indexed() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwd.members]/19
		return wdi_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR
	operator sys_days() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwd.members]/20
		return to_sys_days(*this);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR explicit
	operator local_days() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwd.members]/21
		return local_days{sys_days{*this}.time_since_epoch()};
	}

private:
	HAMON_CXX11_CONSTEXPR bool
	ok_impl(days const& nth_weekday_day) const HAMON_NOEXCEPT
	{
		return static_cast<unsigned>(nth_weekday_day.count()) <= static_cast<unsigned>((y_ / m_ / last).day());
	}

public:
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	ok() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwd.members]/22
		return
			(!y_.ok() || !m_.ok() || !wdi_.ok()) ? false :
			(wdi_.index() <= 4) ? true :
			ok_impl(
				wdi_.weekday() -
				chrono::weekday{static_cast<sys_days>(y_ / m_ / 1)} +
				chrono::days{(wdi_.index() - 1) * 7 + 1});
	}
};

// 30.8.18 Conventional syntax operators[time.cal.operators]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator/(year_month const& ym, weekday_indexed const& wdi) HAMON_NOEXCEPT
{
	// [time.cal.operators]/35
	return {ym.year(), ym.month(), wdi};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator/(year const& y, month_weekday const& mwd) HAMON_NOEXCEPT
{
	// [time.cal.operators]/36
	return {y, mwd.month(), mwd.weekday_indexed()};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator/(int y, month_weekday const& mwd) HAMON_NOEXCEPT
{
	// [time.cal.operators]/37
	return year(y) / mwd;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator/(month_weekday const& mwd, year const& y) HAMON_NOEXCEPT
{
	// [time.cal.operators]/38
	return y / mwd;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator/(month_weekday const& mwd, int y) HAMON_NOEXCEPT
{
	// [time.cal.operators]/39
	return year(y) / mwd;
}

// 30.8.16.3 Non-member functions[time.cal.ymwd.nonmembers]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(year_month_weekday const& x, year_month_weekday const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.nonmembers]/1
	return
		x.year() == y.year() &&
		x.month() == y.month() &&
		x.weekday_indexed() == y.weekday_indexed();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(year_month_weekday const& x, year_month_weekday const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}
#endif

template <typename = void>	// [time.cal.ymwd.nonmembers]/2
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator+(year_month_weekday const& ymwd, months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.nonmembers]/3
	return (ymwd.year() / ymwd.month() + dm) / ymwd.weekday_indexed();
}

template <typename = void>	// [time.cal.ymwd.nonmembers]/4
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator+(months const& dm, year_month_weekday const& ymwd) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.nonmembers]/5
	return ymwd + dm;
}

template <typename = void>	// [time.cal.ymwd.nonmembers]/6
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator-(year_month_weekday const& ymwd, months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.nonmembers]/7
	return ymwd + (-dm);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator+(year_month_weekday const& ymwd, years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.nonmembers]/8
	return {ymwd.year()+dy, ymwd.month(), ymwd.weekday_indexed()};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator+(years const& dy, year_month_weekday const& ymwd) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.nonmembers]/9
	return ymwd + dy;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday
operator-(year_month_weekday const& ymwd, years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.nonmembers]/10
	return ymwd + (-dy);
}

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, year_month_weekday const& ymwd)
{
	// [time.cal.ymwd.nonmembers]/11
	return os << format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{}/{:L}/{:L}"),
		ymwd.year(), ymwd.month(), ymwd.weekday_indexed());
}
#endif

// 30.8.16.2 Member functions[time.cal.ymwd.members]

template <typename>	// [time.cal.ymwd.members]/5
inline HAMON_CXX14_CONSTEXPR year_month_weekday&
year_month_weekday::operator+=(months const& m) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.members]/6
	*this = *this + m;

	// [time.cal.ymwd.members]/7
	return *this;
}

template <typename>	// [time.cal.ymwd.members]/8
inline HAMON_CXX14_CONSTEXPR year_month_weekday&
year_month_weekday::operator-=(months const& m) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.members]/9
	*this = *this - m;

	// [time.cal.ymwd.members]/10
	return *this;
}

inline HAMON_CXX14_CONSTEXPR year_month_weekday&
year_month_weekday::operator+=(years const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.members]/11
	*this = *this + y;

	// [time.cal.ymwd.members]/12
	return *this;
}

inline HAMON_CXX14_CONSTEXPR year_month_weekday&
year_month_weekday::operator-=(years const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymwd.members]/13
	*this = *this - y;

	// [time.cal.ymwd.members]/14
	return *this;
}

// 30.8.17 Class year_month_weekday_last[time.cal.ymwdlast]

class year_month_weekday_last
{
	chrono::year y_;
	chrono::month m_;
	chrono::weekday_last wdl_;

public:
	HAMON_CXX11_CONSTEXPR
	year_month_weekday_last(
		chrono::year const& y,
		chrono::month const& m,
		chrono::weekday_last const& wdl) HAMON_NOEXCEPT
		// [time.cal.ymwdlast.members]/1
		: y_(y), m_(m), wdl_(wdl)
	{}

	template <typename = void>	// [time.cal.ymwdlast.members]/2
	HAMON_CXX14_CONSTEXPR year_month_weekday_last&
	operator+=(months const& m) HAMON_NOEXCEPT;

	template <typename = void>	// [time.cal.ymwdlast.members]/5
	HAMON_CXX14_CONSTEXPR year_month_weekday_last&
	operator-=(months const& m) HAMON_NOEXCEPT;

	HAMON_CXX14_CONSTEXPR year_month_weekday_last&
	operator+=(years const& y) HAMON_NOEXCEPT;

	HAMON_CXX14_CONSTEXPR year_month_weekday_last&
	operator-=(years const& y) HAMON_NOEXCEPT;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::year
	year() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwdlast.members]/12
		return y_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::month
	month() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwdlast.members]/13
		return m_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::weekday
	weekday() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwdlast.members]/14
		return wdl_.weekday();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::weekday_last
	weekday_last() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwdlast.members]/15
		return wdl_;
	}

private:
	static HAMON_CXX11_CONSTEXPR sys_days
	to_sys_days_impl(year_month_weekday_last const& ymwdl, sys_days const& sysd) HAMON_NOEXCEPT
	{
		return sysd - (chrono::weekday{sysd} - ymwdl.wdl_.weekday());
	}

	static HAMON_CXX11_CONSTEXPR sys_days
	to_sys_days(year_month_weekday_last const& ymwdl) HAMON_NOEXCEPT
	{
		return to_sys_days_impl(ymwdl, sys_days{ymwdl.y_ / ymwdl.m_ / chrono::last});
	}

public:
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR
	operator sys_days() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwdlast.members]/16
		return to_sys_days(*this);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR explicit
	operator local_days() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwdlast.members]/17
		return local_days{sys_days{*this}.time_since_epoch()};
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	ok() const HAMON_NOEXCEPT
	{
		// [time.cal.ymwdlast.members]/18
		return y_.ok() && m_.ok() && wdl_.ok();
	}
};

// 30.8.18 Conventional syntax operators[time.cal.operators]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator/(year_month const& ym, weekday_last const& wdl) HAMON_NOEXCEPT
{
	// [time.cal.operators]/40
	return {ym.year(), ym.month(), wdl};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator/(year const& y, month_weekday_last const& mwdl) HAMON_NOEXCEPT
{
	// [time.cal.operators]/41
	return {y, mwdl.month(), mwdl.weekday_last()};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator/(int y, month_weekday_last const& mwdl) HAMON_NOEXCEPT
{
	// [time.cal.operators]/42
	return year(y) / mwdl;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator/(month_weekday_last const& mwdl, year const& y) HAMON_NOEXCEPT
{
	// [time.cal.operators]/43
	return y / mwdl;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator/(month_weekday_last const& mwdl, int y) HAMON_NOEXCEPT
{
	// [time.cal.operators]/44
	return year(y) / mwdl;
}

// 30.8.17.3 Non-member functions[time.cal.ymwdlast.nonmembers]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(year_month_weekday_last const& x, year_month_weekday_last const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.nonmembers]/1
	return
		x.year() == y.year() &&
		x.month() == y.month() &&
		x.weekday_last() == y.weekday_last();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(year_month_weekday_last const& x, year_month_weekday_last const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}
#endif

template <typename = void>	// [time.cal.ymwdlast.nonmembers]/2
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator+(year_month_weekday_last const& ymwdl, months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.nonmembers]/3
	return (ymwdl.year() / ymwdl.month() + dm) / ymwdl.weekday_last();
}

template <typename = void>	// [time.cal.ymwdlast.nonmembers]/4
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator+(months const& dm, year_month_weekday_last const& ymwdl) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.nonmembers]/5
	return ymwdl + dm;
}

template <typename = void>	// [time.cal.ymwdlast.nonmembers]/6
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator-(year_month_weekday_last const& ymwdl, months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.nonmembers]/7
	return ymwdl + (-dm);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator+(year_month_weekday_last const& ymwdl, years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.nonmembers]/8
	return {ymwdl.year()+dy, ymwdl.month(), ymwdl.weekday_last()};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator+(years const& dy, year_month_weekday_last const& ymwdl) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.nonmembers]/9
	return ymwdl + dy;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month_weekday_last
operator-(year_month_weekday_last const& ymwdl, years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.nonmembers]/10
	return ymwdl + (-dy);
}

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, year_month_weekday_last const& ymwdl)
{
	// [time.cal.ymwdlast.nonmembers]/11
	return os << format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{}/{:L}/{:L}"),
		ymwdl.year(), ymwdl.month(), ymwdl.weekday_last());
}
#endif

// 30.8.17.2 Member functions[time.cal.ymwdlast.members]

template <typename>	// [time.cal.ymwdlast.members]/2
inline HAMON_CXX14_CONSTEXPR year_month_weekday_last&
year_month_weekday_last::operator+=(months const& m) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.members]/3
	*this = *this + m;

	// [time.cal.ymwdlast.members]/4
	return *this;
}

template <typename>	// [time.cal.ymwdlast.members]/5
inline HAMON_CXX14_CONSTEXPR year_month_weekday_last&
year_month_weekday_last::operator-=(months const& m) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.members]/6
	*this = *this - m;

	// [time.cal.ymwdlast.members]/7
	return *this;
}

inline HAMON_CXX14_CONSTEXPR year_month_weekday_last&
year_month_weekday_last::operator+=(years const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.members]/8
	*this = *this + y;

	// [time.cal.ymwdlast.members]/9
	return *this;
}

inline HAMON_CXX14_CONSTEXPR year_month_weekday_last&
year_month_weekday_last::operator-=(years const& y) HAMON_NOEXCEPT
{
	// [time.cal.ymwdlast.members]/10
	*this = *this - y;

	// [time.cal.ymwdlast.members]/11
	return *this;
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_YEAR_MONTH_WEEKDAY_HPP
