/**
 *	@file	from_chars_integer.hpp
 *
 *	@brief	from_chars_integer の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_FROM_CHARS_INTEGER_HPP
#define HAMON_CHARCONV_DETAIL_FROM_CHARS_INTEGER_HPP

#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/charconv/detail/negate_unsigned.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/limits.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

constexpr int digit_tbl[] =
{
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	  0,   1,   2,   3,   4,   5,   6,   7,   8,   9, 255, 255, 255, 255, 255, 255,
	255,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,
	 25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35, 255, 255, 255, 255, 255,
	255,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,
	 25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};

template <typename T>
inline HAMON_CXX14_CONSTEXPR T
char_to_uint(char c)
{
	static_assert(hamon::is_unsigned<T>::value, "");
#if 1
	return static_cast<T>(digit_tbl[static_cast<hamon::size_t>(c)]);
#else
	if ('0' <= c && c <= '9')
	{
		return static_cast<T>(c - '0');
	}
	
	if ('a' <= c && c <= 'z')
	{
		return static_cast<T>(c - 'a' + 10);
	}

	if ('A' <= c && c <= 'Z')
	{
		return static_cast<T>(c - 'A' + 10);
	}

	// パターンにマッチしないときはとにかく大きな値を返す
	return static_cast<T>(-1);
#endif
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_unsigned_integer(char const* first, char const* last, T& value, T base)
{
	static_assert(hamon::is_unsigned<T>::value, "");

	const T uint_max  = static_cast<T>(-1);
	const T max_value = static_cast<T>(uint_max / base);
	const T max_digit = static_cast<T>(uint_max % base);

	bool overflow = false;
	auto p = first;
	while (p != last)
	{
		auto digit = hamon::detail::char_to_uint<T>(*p);
		if (digit >= base)
		{
			// パターンにマッチしなかった
			break;
		}
		++p;

		if (value > max_value || (value == max_value && digit > max_digit))
		{
			overflow = true;
			// オーバーフローしても処理は続ける
		}

		value = static_cast<T>(value * base + digit);
	}

	if (p == first)
	{
		return {first, hamon::errc::invalid_argument};
	}
	
	if (overflow)
	{
		return {p, hamon::errc::result_out_of_range};
	}

	return {p, hamon::errc{}};
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_integer_impl(char const* first, char const* last, T& value, int base, bool allow_plus_sign, hamon::detail::overload_priority<1>)
{
	HAMON_ASSERT(first != last);

	if (allow_plus_sign)
	{
		if (*first == '+')
		{
			++first;
		}
	}

	T x{};
	auto ret = hamon::detail::from_chars_unsigned_integer(first, last, x, static_cast<T>(base));
	if (ret.ec == hamon::errc{})
	{
		value = x;
	}
	return ret;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_integer_impl(char const* first, char const* last, T& value, int base, bool allow_plus_sign, hamon::detail::overload_priority<0>)
{
	HAMON_ASSERT(first != last);

	using UT = hamon::make_unsigned_t<T>;
	bool minus = false;
	if (*first == '-')
	{
		minus = true;
		++first;
	}
	else if (allow_plus_sign && *first == '+')
	{
		++first;
	}

	UT x{};
	auto ret = hamon::detail::from_chars_unsigned_integer(first, last, x, static_cast<UT>(base));
	if (ret.ec != hamon::errc{})
	{
		return ret;
	}

	if (minus)
	{
		if (x > hamon::detail::negate_unsigned(static_cast<UT>(hamon::numeric_limits<T>::min())))
		{
			return {ret.ptr, hamon::errc::result_out_of_range};
		}

		x = hamon::detail::negate_unsigned(x);
	}
	else
	{
		if (x > static_cast<UT>(hamon::numeric_limits<T>::max()))
		{
			return {ret.ptr, hamon::errc::result_out_of_range};
		}
	}

	value = static_cast<T>(x);
	return ret;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_integer(char const* first, char const* last, T& value, int base, bool allow_plus_sign = false)
{
	if (first == last)
	{
		return {first, hamon::errc::invalid_argument};
	}

	return hamon::detail::from_chars_integer_impl(
		first, last, value, base, allow_plus_sign, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_INTEGER_HPP
