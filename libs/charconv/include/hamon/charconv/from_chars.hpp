﻿/**
 *	@file	from_chars.hpp
 *
 *	@brief	from_chars の定義
 */

#ifndef HAMON_CHARCONV_FROM_CHARS_HPP
#define HAMON_CHARCONV_FROM_CHARS_HPP

#include <hamon/charconv/config.hpp>

#if defined(HAMON_USE_STD_CHARCONV)

#include <charconv>

namespace hamon
{

using std::from_chars_result;
using std::from_chars;

}	// namespace hamon

#else

#include <hamon/charconv/detail/negate_unsigned.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/config.hpp>
#include <system_error>

namespace hamon
{

struct from_chars_result
{
	const char* ptr;
	std::errc ec;
#if defined(HAMON_HAS_CXX20_CONSISTENT_DEFAULTED_COMPARISONS)
	friend bool operator==(from_chars_result const&, from_chars_result const&) = default;
#else
	friend HAMON_CXX11_CONSTEXPR bool
	operator==(from_chars_result const& lhs, from_chars_result const& rhs)
	{
		return
			lhs.ptr == rhs.ptr &&
			lhs.ec  == rhs.ec;
	}
#endif
#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(from_chars_result const& lhs, from_chars_result const& rhs)
	{
		return !(lhs == rhs);
	}
#endif
};

namespace charconv_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR T
char_to_uint(char c)
{
	static_assert(hamon::is_unsigned<T>::value, "");

	if ('0' <= c && c <= '9')
	{
		return static_cast<T>(c - '0');
	}
	
	if ('a' <= c && c <= 'z')
	{
		return static_cast<T>(c - 'a' + 10);
	}

	// パターンにマッチしないときはとにかく大きな値を返す
	return static_cast<T>(-1);
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
overflowed_multiply(T& out, T lhs, T rhs)
{
	static_assert(hamon::is_unsigned<T>::value, "");

	out = static_cast<T>(lhs * rhs);
	return out < lhs;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
overflowed_add(T& out, T lhs, T rhs)
{
	static_assert(hamon::is_unsigned<T>::value, "");

	out = static_cast<T>(lhs + rhs);
	return out < lhs;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR from_chars_result
from_chars_unsigned_integral(char const* first, char const* last, T& value, T base)
{
	static_assert(hamon::is_unsigned<T>::value, "");

	bool overflowed = false;
	auto p = first;
	while (p != last)
	{
		auto n = char_to_uint<T>(*p);
		if (n >= base)
		{
			// パターンにマッチしなかった
			break;
		}
		++p;

		// value *= base
		if (overflowed_multiply(value, value, base))
		{
			overflowed = true;
		}
		// value += n
		if (overflowed_add(value, value, n))
		{
			overflowed = true;
		}
	}

	if (p == first)
	{
		return {first, std::errc::invalid_argument};
	}
	
	if (overflowed)
	{
		return {p, std::errc::result_out_of_range};
	}

	return {p, std::errc{}};
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
inline HAMON_CXX14_CONSTEXPR from_chars_result
from_chars_integral(char const* first, char const* last, T& value, int base, hamon::detail::overload_priority<1>)
{
	T x{};
	auto ret = from_chars_unsigned_integral(first, last, x, static_cast<T>(base));
	if (ret.ec == std::errc{})
	{
		value = x;
	}
	return ret;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR from_chars_result
from_chars_integral(char const* first, char const* last, T& value, int base, hamon::detail::overload_priority<0>)
{
	using UT = hamon::make_unsigned_t<T>;
	bool minus = false;
	if (first != last && *first == '-')
	{
		minus = true;
		++first;
	}

	UT x{};
	auto ret = from_chars_unsigned_integral(first, last, x, static_cast<UT>(base));
	if (ret.ec != std::errc{})
	{
		return ret;
	}

	if (minus)
	{
		if (x > negate_unsigned(static_cast<UT>(std::numeric_limits<T>::min())))
		{
			return {ret.ptr, std::errc::result_out_of_range};
		}

		x = negate_unsigned(x);
	}
	else
	{
		if (x > static_cast<UT>(std::numeric_limits<T>::max()))
		{
			return {ret.ptr, std::errc::result_out_of_range};
		}
	}

	value = static_cast<T>(x);
	return ret;
}

}	// namespace charconv_detail

template <typename T, typename = hamon::enable_if_t<hamon::is_integral<T>::value>>
inline HAMON_CXX14_CONSTEXPR from_chars_result
from_chars(char const* first, char const* last, T& value, int base = 10)
{
	return hamon::charconv_detail::from_chars_integral(
		first, last, value, base, hamon::detail::overload_priority<1>{});
}

from_chars_result from_chars(const char*, const char*, bool, int = 10) = delete;

}	// namespace hamon

#endif

#endif // HAMON_CHARCONV_FROM_CHARS_HPP
