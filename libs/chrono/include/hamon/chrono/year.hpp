/**
 *	@file	year.hpp
 *
 *	@brief	year の定義
 */

#ifndef HAMON_CHRONO_YEAR_HPP
#define HAMON_CHRONO_YEAR_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::year;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/compare/strong_ordering.hpp>

namespace hamon {
namespace chrono {

class year;

HAMON_CXX11_CONSTEXPR year
operator+(year const& x, years const& y) HAMON_NOEXCEPT;
HAMON_CXX11_CONSTEXPR year
operator-(year const& x, years const& y) HAMON_NOEXCEPT;

// 30.8.5 Class year[time.cal.year]

class year
{
	short y_;

public:
	year() = default;

	HAMON_CXX11_CONSTEXPR explicit
	year(int y) HAMON_NOEXCEPT
		// [time.cal.year.members]/1
		: y_(static_cast<short>(y))
	{}

	HAMON_CXX14_CONSTEXPR year& operator++() HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/2
		++y_;

		// [time.cal.year.members]/3
		return *this;
	}

	HAMON_CXX14_CONSTEXPR year operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;

		// [time.cal.year.members]/4
		++(*this);

		// [time.cal.year.members]/5
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR year& operator--() HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/6
		--y_;

		// [time.cal.year.members]/7
		return *this;
	}

	HAMON_CXX14_CONSTEXPR year operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;

		// [time.cal.year.members]/8
		--(*this);

		// [time.cal.year.members]/9
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR year& operator+=(years const& y) HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/10
		*this = *this + y;

		// [time.cal.year.members]/11
		return *this;
	}

	HAMON_CXX14_CONSTEXPR year& operator-=(years const& y) HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/12
		*this = *this - y;

		// [time.cal.year.members]/13
		return *this;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR year operator+() const HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/14
		return *this;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR year operator-() const HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/15
		return year{-y_};
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool is_leap() const HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/16
		return y_ % 4 == 0 && (y_ % 100 != 0 || y_ % 400 == 0);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR explicit operator int() const HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/17
		return y_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool ok() const HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/18
		return min().y_ <= y_ && y_ <= max().y_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	static HAMON_CXX11_CONSTEXPR year min() HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/19
		return year{-32767};
	}

	HAMON_NODISCARD	// nodiscard as an extension
	static HAMON_CXX11_CONSTEXPR year max() HAMON_NOEXCEPT
	{
		// [time.cal.year.members]/20
		return year{32767};
	}
};

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(year const& x, year const& y) HAMON_NOEXCEPT
{
	// [time.cal.year.nonmembers]/1
	return int{x} == int{y};
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR strong_ordering
operator<=>(year const& x, year const& y) HAMON_NOEXCEPT
{
	// [time.cal.year.nonmembers]/2
	return int{x} <=> int{y};
}

#else

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(year const& x, year const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(year const& x, year const& y) HAMON_NOEXCEPT
{
	return int{x} < int{y};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(year const& x, year const& y) HAMON_NOEXCEPT
{
	return y < x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(year const& x, year const& y) HAMON_NOEXCEPT
{
	return !(x > y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(year const& x, year const& y) HAMON_NOEXCEPT
{
	return !(x < y);
}

#endif

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year
operator+(year const& x, years const& y) HAMON_NOEXCEPT
{
	// [time.cal.year.nonmembers]/3
	return year{int{x} + static_cast<int>(y.count())};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year
operator+(years const& x, year const& y) HAMON_NOEXCEPT
{
	// [time.cal.year.nonmembers]/4
	return y + x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR year
operator-(year const& x, years const& y) HAMON_NOEXCEPT
{
	// [time.cal.year.nonmembers]/5
	return x + -y;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR years
operator-(year const& x, year const& y) HAMON_NOEXCEPT
{
	// [time.cal.year.nonmembers]/6
	return years{int{x} - int{y}};
}

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, year const& y)
{
	// [time.cal.year.nonmembers]/7
	return os << (y.ok() ?
		format(HAMON_STATICALLY_WIDEN(charT, "{:%Y}"), y) :
		format(HAMON_STATICALLY_WIDEN(charT, "{:%Y} is not a valid year"), y));
}

template <typename charT, typename traits, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	charT const* fmt,
	year& y,
	hamon::basic_string<charT, traits, Alloc>* abbrev = nullptr,
	minutes* offset = nullptr)
{
	// [time.cal.year.nonmembers]/8
	// TODO

	// [time.cal.year.nonmembers]/9
	return is;
}
#endif

}	// namespace chrono

inline namespace literals {
inline namespace chrono_literals {

// アンダースコアで始まらないユーザー定義リテラルのサフィックス名は、
// 標準C++の将来の拡張のために予約されているため、アンダースコアから始まる名前に変更した。

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::year operator"" _y(unsigned long long y) HAMON_NOEXCEPT
{
	// [time.cal.year.nonmembers]/10
	return chrono::year{static_cast<int>(y)};
}

}	// inline namespace chrono_literals
}	// inline namespace literals

namespace chrono {
using namespace literals::chrono_literals;
}

}	// namespace hamon

#endif

#endif // HAMON_CHRONO_YEAR_HPP
