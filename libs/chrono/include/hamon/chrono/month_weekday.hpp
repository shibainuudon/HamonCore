/**
 *	@file	month_weekday.hpp
 *
 *	@brief	month_weekday の定義
 */

#ifndef HAMON_CHRONO_MONTH_WEEKDAY_HPP
#define HAMON_CHRONO_MONTH_WEEKDAY_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::month_weekday;
using std::chrono::month_weekday_last;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/month.hpp>
#include <hamon/chrono/weekday.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.8.11 Class month_weekday[time.cal.mwd]

class month_weekday
{
	chrono::month m_;
	chrono::weekday_indexed wdi_;

public:
	HAMON_CXX11_CONSTEXPR
	month_weekday(chrono::month const& m, chrono::weekday_indexed const& wdi) HAMON_NOEXCEPT
		// [time.cal.mwd.members]/1
		: m_(m), wdi_(wdi)
	{}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::month
	month() const HAMON_NOEXCEPT
	{
		// [time.cal.mwd.members]/2
		return m_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::weekday_indexed
	weekday_indexed() const HAMON_NOEXCEPT
	{
		// [time.cal.mwd.members]/3
		return wdi_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	ok() const HAMON_NOEXCEPT
	{
		// [time.cal.mwd.members]/4
		return m_.ok() && wdi_.ok();
	}
};

// 30.8.11.3 Non-member functions[time.cal.mwd.nonmembers]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(month_weekday const& x, month_weekday const& y) HAMON_NOEXCEPT
{
	// [time.cal.mwd.nonmembers]/1
	return x.month() == y.month() && x.weekday_indexed() == y.weekday_indexed();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(month_weekday const& x, month_weekday const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}
#endif

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, month_weekday const& mwd)
{
	// [time.cal.mwd.nonmembers]/2
	return os << hamon::format(os.getloc(),
		HAMON_STATICALLY_WIDEN(charT, "{:L}/{:L}"), mwd.month(), mwd.weekday_indexed());
}
#endif

// 30.8.12 Class month_weekday_last[time.cal.mwdlast]

class month_weekday_last
{
	chrono::month m_;
	chrono::weekday_last wdl_;

public:
	HAMON_CXX11_CONSTEXPR
	month_weekday_last(
		chrono::month const& m,
		chrono::weekday_last const& wdl) HAMON_NOEXCEPT
		// [time.cal.mwdlast.members]/1
		: m_(m), wdl_(wdl)
	{}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::month
	month() const HAMON_NOEXCEPT
	{
		// [time.cal.mwdlast.members]/2
		return m_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::weekday_last
	weekday_last() const HAMON_NOEXCEPT
	{
		// [time.cal.mwdlast.members]/3
		return wdl_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	ok() const HAMON_NOEXCEPT
	{
		// [time.cal.mwdlast.members]/4
		return m_.ok() && wdl_.ok();
	}
};

// 30.8.12.3 Non-member functions[time.cal.mwdlast.nonmembers]
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(month_weekday_last const& x, month_weekday_last const& y) HAMON_NOEXCEPT
{
	// [time.cal.mwdlast.nonmembers]/1
	return x.month() == y.month() && x.weekday_last() == y.weekday_last();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(month_weekday_last const& x, month_weekday_last const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}
#endif

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, month_weekday_last const& mwdl)
{
	// [time.cal.mwdlast.nonmembers]/2
	return os << hamon::format(os.getloc(),
		HAMON_STATICALLY_WIDEN(charT, "{:L}/{:L}"), mwdl.month(), mwdl.weekday_last());
}
#endif

// 30.8.18 Conventional syntax operators[time.cal.operators]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_weekday
operator/(month const& m, weekday_indexed const& wdi) HAMON_NOEXCEPT
{
	// [time.cal.operators]/16
	return {m, wdi};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_weekday
operator/(int m, weekday_indexed const& wdi) HAMON_NOEXCEPT
{
	// [time.cal.operators]/17
	return month(static_cast<unsigned>(m)) / wdi;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_weekday
operator/(weekday_indexed const& wdi, month const& m) HAMON_NOEXCEPT
{
	// [time.cal.operators]/18
	return m / wdi;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_weekday
operator/(weekday_indexed const& wdi, int m) HAMON_NOEXCEPT
{
	// [time.cal.operators]/19
	return month(static_cast<unsigned>(m)) / wdi;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_weekday_last
operator/(month const& m, weekday_last const& wdl) HAMON_NOEXCEPT
{
	// [time.cal.operators]/20
	return {m, wdl};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_weekday_last
operator/(int m, weekday_last const& wdl) HAMON_NOEXCEPT
{
	// [time.cal.operators]/21
	return month(static_cast<unsigned>(m)) / wdl;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_weekday_last
operator/(weekday_last const& wdl, month const& m) HAMON_NOEXCEPT
{
	// [time.cal.operators]/22
	return m / wdl;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month_weekday_last
operator/(weekday_last const& wdl, int m) HAMON_NOEXCEPT
{
	// [time.cal.operators]/23
	return month(static_cast<unsigned>(m)) / wdl;
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_MONTH_WEEKDAY_HPP
