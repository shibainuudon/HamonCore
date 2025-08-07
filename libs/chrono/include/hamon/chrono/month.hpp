/**
 *	@file	month.hpp
 *
 *	@brief	month の定義
 */

#ifndef HAMON_CHRONO_MONTH_HPP
#define HAMON_CHRONO_MONTH_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::month;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/detail/modulo.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

class month;

HAMON_CXX11_CONSTEXPR month
operator+(month const& x, months const& y) HAMON_NOEXCEPT;
HAMON_CXX11_CONSTEXPR month
operator-(month const& x, months const& y) HAMON_NOEXCEPT;

// 30.8.4 Class month[time.cal.month]

class month
{
	unsigned char m_;

public:
	month() = default;

	HAMON_CXX11_CONSTEXPR explicit
	month(unsigned m) HAMON_NOEXCEPT
		// [time.cal.month.members]/1
		: m_(static_cast<unsigned char>(m))
	{}

	HAMON_CXX14_CONSTEXPR month& operator++() HAMON_NOEXCEPT
	{
		// [time.cal.month.members]/2
		*this += months{1};

		// [time.cal.month.members]/3
		return *this;
	}

	HAMON_CXX14_CONSTEXPR month operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;

		// [time.cal.month.members]/4
		++(*this);

		// [time.cal.month.members]/5
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR month& operator--() HAMON_NOEXCEPT
	{
		// [time.cal.month.members]/6
		*this -= months{1};

		// [time.cal.month.members]/7
		return *this;
	}

	HAMON_CXX14_CONSTEXPR month operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;

		// [time.cal.month.members]/8
		--(*this);

		// [time.cal.month.members]/9
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR month& operator+=(months const& m) HAMON_NOEXCEPT
	{
		// [time.cal.month.members]/10
		*this = *this + m;

		// [time.cal.month.members]/11
		return *this;
	}

	HAMON_CXX14_CONSTEXPR month& operator-=(months const& m) HAMON_NOEXCEPT
	{
		// [time.cal.month.members]/12
		*this = *this - m;

		// [time.cal.month.members]/13
		return *this;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR explicit operator unsigned() const HAMON_NOEXCEPT
	{
		// [time.cal.month.members]/14
		return m_;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool ok() const HAMON_NOEXCEPT
	{
		// [time.cal.month.members]/15
		return 1 <= m_ && m_ <= 12;
	}
};

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(month const& x, month const& y) HAMON_NOEXCEPT
{
	// [time.cal.month.nonmembers]/1
	return unsigned{x} == unsigned{y};
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR hamon::strong_ordering
operator<=>(month const& x, month const& y) HAMON_NOEXCEPT
{
	// [time.cal.month.nonmembers]/2
	return unsigned{x} <=> unsigned{y};
}

#else

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(month const& x, month const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(month const& x, month const& y) HAMON_NOEXCEPT
{
	return unsigned{x} < unsigned{y};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(month const& x, month const& y) HAMON_NOEXCEPT
{
	return y < x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(month const& x, month const& y) HAMON_NOEXCEPT
{
	return !(x > y);
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(month const& x, month const& y) HAMON_NOEXCEPT
{
	return !(x < y);
}

#endif

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month
operator+(month const& x, months const& y) HAMON_NOEXCEPT
{
	// [time.cal.month.nonmembers]/3
	return month{static_cast<unsigned>(hamon::chrono::detail::modulo(
		static_cast<long long>(unsigned{x}) + (y.count() - 1), 12) + 1)};
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month
operator+(months const& x, month const& y) HAMON_NOEXCEPT
{
	// [time.cal.month.nonmembers]/4
	return y + x;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR month
operator-(month const& x, months const& y) HAMON_NOEXCEPT
{
	// [time.cal.month.nonmembers]/5
	return x + -y;
}

HAMON_NODISCARD	// nodiscard as an extension
inline HAMON_CXX11_CONSTEXPR months
operator-(month const& x, month const& y) HAMON_NOEXCEPT
{
	// [time.cal.month.nonmembers]/6
	return months{hamon::chrono::detail::modulo(int(unsigned{x}) - int(unsigned{y}), 12)};
}

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, month const& m)
{
	// [time.cal.month.nonmembers]/7
	return os << (m.ok() ?
		format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{:L%b}"), m) :
		format(os.getloc(), HAMON_STATICALLY_WIDEN(charT, "{} is not a valid month"),
		static_cast<unsigned>(m)));
}

template <typename charT, typename traits, typename Alloc = hamon::allocator<charT>>
std::basic_istream<charT, traits>&
from_stream(
	std::basic_istream<charT, traits>& is,
	charT const* fmt,
	month& m,
	hamon::basic_string<charT, traits, Alloc>* abbrev = nullptr,
	minutes* offset = nullptr)
{
	// [time.cal.month.nonmembers]/8
	// TODO

	// [time.cal.month.nonmembers]/9
	return is;
}
#endif

// calendrical constants
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month January{1};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month February{2};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month March{3};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month April{4};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month May{5};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month June{6};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month July{7};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month August{8};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month September{9};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month October{10};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month November{11};
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR month December{12};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_MONTH_HPP
