/**
 *	@file	weekday.hpp
 *
 *	@brief	weekday の定義
 */

#ifndef HAMON_CHRONO_WEEKDAY_HPP
#define HAMON_CHRONO_WEEKDAY_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::weekday;
using std::chrono::weekday_indexed;
using std::chrono::weekday_last;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/local_days.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/last_spec.hpp>
#include <hamon/chrono/detail/modulo.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

class weekday;

HAMON_CXX11_CONSTEXPR weekday
operator+(weekday const& x, days const& y) HAMON_NOEXCEPT;
HAMON_CXX11_CONSTEXPR weekday
operator-(weekday const& x, days const& y) HAMON_NOEXCEPT;

class weekday_indexed;
class weekday_last;

// 30.8.6 Class weekday[time.cal.wd]

class weekday
{
	unsigned char wd_;

	static HAMON_CXX11_CONSTEXPR unsigned char
	weekday_from_days(int d) HAMON_NOEXCEPT
	{
		// https://howardhinnant.github.io/date_algorithms.html#weekday_from_days
		return static_cast<unsigned char>(static_cast<unsigned>(d >= -4 ? (d + 4) % 7 : (d + 5) % 7 + 6));
	}

public:
	weekday() = default;

	HAMON_CXX11_CONSTEXPR explicit
	weekday(unsigned wd) HAMON_NOEXCEPT
		// [time.cal.wd.members]/1
		: wd_(static_cast<unsigned char>(wd == 7 ? 0 : wd))
	{}

	HAMON_CXX11_CONSTEXPR
	weekday(sys_days const& dp) HAMON_NOEXCEPT
		// [time.cal.wd.members]/2
		: wd_(weekday_from_days(dp.time_since_epoch().count()))
	{}

	HAMON_CXX11_CONSTEXPR explicit
	weekday(local_days const& dp) HAMON_NOEXCEPT
		// [time.cal.wd.members]/4
		: wd_(weekday_from_days(dp.time_since_epoch().count()))
	{}

	HAMON_CXX14_CONSTEXPR weekday&
	operator++() HAMON_NOEXCEPT
	{
		// [time.cal.wd.members]/6
		*this += days{1};

		// [time.cal.wd.members]/7
		return *this;
	}

	HAMON_CXX14_CONSTEXPR weekday
	operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;

		// [time.cal.wd.members]/8
		++(*this);

		// [time.cal.wd.members]/9
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR weekday&
	operator--() HAMON_NOEXCEPT
	{
		// [time.cal.wd.members]/10
		*this -= days{1};

		// [time.cal.wd.members]/11
		return *this;
	}

	HAMON_CXX14_CONSTEXPR weekday
	operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;

		// [time.cal.wd.members]/12
		--(*this);

		// [time.cal.wd.members]/13
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR weekday&
	operator+=(days const& d) HAMON_NOEXCEPT
	{
		// [time.cal.wd.members]/14
		*this = *this + d;

		// [time.cal.wd.members]/15
		return *this;
	}

	HAMON_CXX14_CONSTEXPR weekday&
	operator-=(days const& d) HAMON_NOEXCEPT
	{
		// [time.cal.wd.members]/16
		*this = *this - d;

		// [time.cal.wd.members]/17
		return *this;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR unsigned
	c_encoding() const HAMON_NOEXCEPT
	{
		// [time.cal.wd.members]/18
		return wd_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR unsigned
	iso_encoding() const HAMON_NOEXCEPT
	{
		// [time.cal.wd.members]/19
		return wd_ == 0u ? 7u : wd_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool ok() const HAMON_NOEXCEPT
	{
		// [time.cal.wd.members]/20
		return wd_ <= 6;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR weekday_indexed
	operator[](unsigned index) const HAMON_NOEXCEPT;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR weekday_last
	operator[](last_spec) const HAMON_NOEXCEPT;
};

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(weekday const& x, weekday const& y) HAMON_NOEXCEPT
{
	// [time.cal.wd.nonmembers]/1
	return x.c_encoding() == y.c_encoding();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(weekday const& x, weekday const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}
#endif

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR weekday
operator+(weekday const& x, days const& y) HAMON_NOEXCEPT
{
	// [time.cal.wd.nonmembers]/2
	return weekday{static_cast<unsigned>(hamon::chrono::detail::modulo(
		static_cast<long long>(x.c_encoding()) + y.count(), 7))};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR weekday
operator+(days const& x, weekday const& y) HAMON_NOEXCEPT
{
	// [time.cal.wd.nonmembers]/3
	return y + x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR weekday
operator-(weekday const& x, days const& y) HAMON_NOEXCEPT
{
	// [time.cal.wd.nonmembers]/4
	return x + -y;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR days
operator-(weekday const& x, weekday const& y) HAMON_NOEXCEPT
{
	// [time.cal.wd.nonmembers]/5
	return days{hamon::chrono::detail::modulo(
		static_cast<long long>(x.c_encoding()) - y.c_encoding(), 7)};
}

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, weekday const& wd)
{
	// [time.cal.wd.nonmembers]/6
	return os << (wd.ok() ?
		format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{:L%a}"), wd) :
		format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{} is not a valid weekday"),
			static_cast<unsigned>(wd.c_encoding())));
}

template <typename charT, typename traits, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	charT const* fmt,
	weekday& wd,
	basic_string<charT, traits, Alloc>* abbrev = nullptr,
	minutes* offset = nullptr)
{
	// [time.cal.wd.nonmembers]/7
	// TODO

	// [time.cal.wd.nonmembers]/8
	return is;
}
#endif

// calendrical constants
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR weekday Sunday{0};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR weekday Monday{1};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR weekday Tuesday{2};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR weekday Wednesday{3};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR weekday Thursday{4};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR weekday Friday{5};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR weekday Saturday{6};

// 30.8.7 Class weekday_indexed[time.cal.wdidx]

class weekday_indexed
{
	chrono::weekday wd_;
	unsigned char index_;

public:
	weekday_indexed() = default;

	HAMON_CXX11_CONSTEXPR
	weekday_indexed(chrono::weekday const& wd, unsigned index) HAMON_NOEXCEPT
		// [time.cal.wdidx.members]/1
		: wd_(wd), index_(static_cast<unsigned char>(index))
	{}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::weekday weekday() const HAMON_NOEXCEPT
	{
		// [time.cal.wdidx.members]/2
		return wd_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR unsigned index() const HAMON_NOEXCEPT
	{
		// [time.cal.wdidx.members]/3
		return index_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool ok() const HAMON_NOEXCEPT
	{
		// [time.cal.wdidx.members]/4
		return wd_.ok() && 1 <= index_ && index_ <= 5;
	}
};

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(weekday_indexed const& x, weekday_indexed const& y) HAMON_NOEXCEPT
{
	// [time.cal.wdidx.nonmembers]/1
	return x.weekday() == y.weekday() && x.index() == y.index();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(weekday_indexed const& x, weekday_indexed const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}
#endif

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, weekday_indexed const& wdi)
{
	// [time.cal.wdidx.nonmembers]/2
	auto i = wdi.index();
	return os << (i >= 1 && i <= 5 ?
		format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{:L}[{}]"), wdi.weekday(), i) :
		format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{:L}[{} is not a valid index]"), wdi.weekday(), i));
}
#endif

// 30.8.8 Class weekday_last[time.cal.wdlast]

class weekday_last
{
	chrono::weekday wd_;

public:
	HAMON_CXX11_CONSTEXPR explicit
	weekday_last(chrono::weekday const& wd) HAMON_NOEXCEPT
		// [time.cal.wdlast.members]/1
		: wd_(wd)
	{}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR chrono::weekday weekday() const HAMON_NOEXCEPT
	{
		// [time.cal.wdlast.members]/2
		return wd_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool ok() const HAMON_NOEXCEPT
	{
		// [time.cal.wdlast.members]/3
		return wd_.ok();
	}
};

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(weekday_last const& x, weekday_last const& y) HAMON_NOEXCEPT
{
	// [time.cal.wdlast.nonmembers]/1
	return x.weekday() == y.weekday();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(weekday_last const& x, weekday_last const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}
#endif

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, weekday_last const& wdl)
{
	// [time.cal.wdlast.nonmembers]/2
	return os << format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{:L}[last]"), wdl.weekday());
}
#endif

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR weekday_indexed
weekday::operator[](unsigned index) const HAMON_NOEXCEPT
{
	// [time.cal.wd.members]/21
	return {*this, index};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR weekday_last
weekday::operator[](last_spec) const HAMON_NOEXCEPT
{
	// [time.cal.wd.members]/22
	return weekday_last{*this};
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_WEEKDAY_HPP
