/**
 *	@file	year_month.hpp
 *
 *	@brief	year_month の定義
 */

#ifndef HAMON_CHRONO_YEAR_MONTH_HPP
#define HAMON_CHRONO_YEAR_MONTH_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::year_month;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/year.hpp>
#include <hamon/chrono/month.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/detail/modulo.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.8.13 Class year_month[time.cal.ym]

class year_month
{
	chrono::year y_;
	chrono::month m_;

public:
	year_month() = default;

	HAMON_CXX11_CONSTEXPR
	year_month(chrono::year const& y, chrono::month const& m) HAMON_NOEXCEPT
		// [time.cal.ym.members]/1
		: y_(y), m_(m)
	{}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::year
	year() const HAMON_NOEXCEPT
	{
		// [time.cal.ym.members]/2
		return y_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::month
	month() const HAMON_NOEXCEPT
	{
		// [time.cal.ym.members]/3
		return m_;
	}

	template <typename = void>	// [time.cal.ym.members]/4
	HAMON_CXX14_CONSTEXPR year_month&
	operator+=(months const& dm) HAMON_NOEXCEPT;

	template <typename = void>	// [time.cal.ym.members]/7
	HAMON_CXX14_CONSTEXPR year_month&
	operator-=(months const& dm) HAMON_NOEXCEPT;

	HAMON_CXX14_CONSTEXPR year_month&
	operator+=(years const& dy) HAMON_NOEXCEPT;

	HAMON_CXX14_CONSTEXPR year_month&
	operator-=(years const& dy) HAMON_NOEXCEPT;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	ok() const HAMON_NOEXCEPT
	{
		// [time.cal.ym.members]/14
		return y_.ok() && m_.ok();
	}
};

// 30.8.18 Conventional syntax operators[time.cal.operators]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month
operator/(year const& y, month const& m) HAMON_NOEXCEPT
{
	// [time.cal.operators]/1
	return {y, m};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month
operator/(year const& y, int m) HAMON_NOEXCEPT
{
	// [time.cal.operators]/2
	return y / month(static_cast<unsigned>(m));
}

// 30.8.13.3 Non-member functions[time.cal.ym.nonmembers]

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(year_month const& x, year_month const& y) HAMON_NOEXCEPT
{
	// [time.cal.ym.nonmembers]/1
	return x.year() == y.year() && x.month() == y.month();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR hamon::strong_ordering
operator<=>(year_month const& x, year_month const& y) HAMON_NOEXCEPT
{
	// [time.cal.ym.nonmembers]/2
	if (auto c = x.year() <=> y.year(); c != 0)
	{
		return c;
	}

	return x.month() <=> y.month();
}

#else

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(year_month const& x, year_month const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(year_month const& x, year_month const& y) HAMON_NOEXCEPT
{
	return
		x.year() != y.year() ?
			x.year() < y.year() :
		x.month() < y.month();
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(year_month const& x, year_month const& y) HAMON_NOEXCEPT
{
	return y < x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(year_month const& x, year_month const& y) HAMON_NOEXCEPT
{
	return !(x > y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(year_month const& x, year_month const& y) HAMON_NOEXCEPT
{
	return !(x < y);
}

#endif

namespace detail
{

inline HAMON_CXX11_CONSTEXPR year_month
year_month_add_impl(year_month const& ym, div_mod_result const& t) HAMON_NOEXCEPT
{
	return (ym.year() + years(t.div)) / month(static_cast<unsigned>(t.mod + 1));
}

}	// namespace detail

template <typename = void>	// [time.cal.ym.nonmembers]/3
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month
operator+(year_month const& ym, months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ym.nonmembers]/4
	return hamon::chrono::detail::year_month_add_impl(ym,
		hamon::chrono::detail::div_mod(
			static_cast<long long>(static_cast<unsigned>(ym.month())) - 1 + dm.count(), 12));
}

template <typename = void>	// [time.cal.ym.nonmembers]/6
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month
operator+(months const& dm, year_month const& ym) HAMON_NOEXCEPT
{
	// [time.cal.ym.nonmembers]/7
	return ym + dm;
}

template <typename = void>	// [time.cal.ym.nonmembers]/8
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month
operator-(year_month const& ym, months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ym.nonmembers]/9
	return ym + -dm;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR months
operator-(year_month const& x, year_month const& y) HAMON_NOEXCEPT
{
	// [time.cal.ym.nonmembers]/10
	return x.year() - y.year() +
		months{static_cast<int>(unsigned{x.month()}) - static_cast<int>(unsigned{y.month()})};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month
operator+(year_month const& ym, years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ym.nonmembers]/11
	return (ym.year() + dy) / ym.month();
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month
operator+(years const& dy, year_month const& ym) HAMON_NOEXCEPT
{
	// [time.cal.ym.nonmembers]/12
	return ym + dy;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year_month
operator-(year_month const& ym, years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ym.nonmembers]/13
	return ym + -dy;
}

template <typename>
inline HAMON_CXX14_CONSTEXPR year_month&
year_month::operator+=(months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ym.members]/5
	*this = *this + dm;

	// [time.cal.ym.members]/6
	return *this;
}

template <typename>
inline HAMON_CXX14_CONSTEXPR year_month&
year_month::operator-=(months const& dm) HAMON_NOEXCEPT
{
	// [time.cal.ym.members]/8
	*this = *this - dm;

	// [time.cal.ym.members]/9
	return *this;
}

inline HAMON_CXX14_CONSTEXPR year_month&
year_month::operator+=(years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ym.members]/10
	*this = *this + dy;

	// [time.cal.ym.members]/11
	return *this;
}

inline HAMON_CXX14_CONSTEXPR year_month&
year_month::operator-=(years const& dy) HAMON_NOEXCEPT
{
	// [time.cal.ym.members]/12
	*this = *this - dy;

	// [time.cal.ym.members]/13
	return *this;
}

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, year_month const& ym)
{
	// [time.cal.ym.nonmembers]/14
	return os << format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{}/{:L}"), ym.year(), ym.month());
}

template <typename charT, typename traits, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	charT const* fmt,
	year_month& ym,
	hamon::basic_string<charT, traits, Alloc>* abbrev = nullptr,
	minutes* offset = nullptr)
{
	// [time.cal.ym.nonmembers]/15
	// TODO

	// [time.cal.ym.nonmembers]/16
	return is;
}
#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_YEAR_MONTH_HPP
