/**
 *	@file	chars_format.hpp
 *
 *	@brief	chars_format の定義
 */

#ifndef HAMON_CHARCONV_CHARS_FORMAT_HPP
#define HAMON_CHARCONV_CHARS_FORMAT_HPP

#include <hamon/charconv/config.hpp>

#if defined(HAMON_USE_STD_CHARCONV)

#include <charconv>

namespace hamon
{

using std::chars_format;

}	// namespace hamon

#else

#include <hamon/utility/to_underlying.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 28.2.1 Header <charconv> synopsis[charconv.syn]

enum class chars_format
{
	scientific = 1 << 0,
	fixed      = 1 << 1,
	hex        = 1 << 2,
	general = fixed | scientific
};

// 16.3.3.3.3 Bitmask types[bitmask.types]

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR chars_format
operator&(chars_format X, chars_format Y) HAMON_NOEXCEPT
{
	return static_cast<chars_format>(
		hamon::to_underlying(X) & hamon::to_underlying(Y));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR chars_format
operator|(chars_format X, chars_format Y) HAMON_NOEXCEPT
{
	return static_cast<chars_format>(
		hamon::to_underlying(X) | hamon::to_underlying(Y));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR chars_format
operator^(chars_format X, chars_format Y) HAMON_NOEXCEPT
{
	return static_cast<chars_format>(
		hamon::to_underlying(X) ^ hamon::to_underlying(Y));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR chars_format
operator~(chars_format X) HAMON_NOEXCEPT
{
	return static_cast<chars_format>(~hamon::to_underlying(X));
}

inline HAMON_CXX14_CONSTEXPR chars_format&
operator&=(chars_format& X, chars_format Y) HAMON_NOEXCEPT
{
	X = X & Y;
	return X;
}

inline HAMON_CXX14_CONSTEXPR chars_format&
operator|=(chars_format& X, chars_format Y) HAMON_NOEXCEPT
{
	X = X | Y;
	return X;
}

inline HAMON_CXX14_CONSTEXPR chars_format&
operator^=(chars_format& X, chars_format Y) HAMON_NOEXCEPT
{
	X = X ^ Y;
	return X;
}

}	// namespace hamon

#endif

#endif // HAMON_CHARCONV_CHARS_FORMAT_HPP
