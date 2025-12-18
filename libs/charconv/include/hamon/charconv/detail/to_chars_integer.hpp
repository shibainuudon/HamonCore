/**
 *	@file	to_chars_integer.hpp
 *
 *	@brief	to_chars_integer の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_TO_CHARS_INTEGER_HPP
#define HAMON_CHARCONV_DETAIL_TO_CHARS_INTEGER_HPP

#include <hamon/charconv/to_chars_result.hpp>
#include <hamon/charconv/detail/negate_unsigned.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR int
to_chars_integer_width(T value, T base)
{
	int result = 0;
	
	do
	{
		value = static_cast<T>(value / base);
		++result;
	}
	while (value != 0);

	return result;
}

template <typename T>
HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars_unsigned_integer(char* first, char* last, T value, T base)
{
	auto n = hamon::detail::to_chars_integer_width(value, base);
	if (n > (last - first))
	{
		return {last, hamon::errc::value_too_large};
	}

	last = first + n;
	auto p = last;
	do
	{
		auto c = value % base;
		value = static_cast<T>(value / base);
		*--p = "0123456789abcdefghijklmnopqrstuvwxyz"[c];
	}
	while (value != 0);

	return {last, hamon::errc{}};
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars_integer_impl(char* first, char* last, T value, int base, hamon::detail::overload_priority<1>)
{
	return hamon::detail::to_chars_unsigned_integer(first, last, value, static_cast<T>(base));
}

template <typename T>
HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars_integer_impl(char* first, char* last, T value, int base, hamon::detail::overload_priority<0>)
{
	using UT = hamon::make_unsigned_t<T>;
	auto x = static_cast<UT>(value);
	if (value < 0 && first != last)
	{
		*first++ = '-';
		x = hamon::detail::negate_unsigned(x);
	}
	return hamon::detail::to_chars_unsigned_integer(first, last, x, static_cast<UT>(base));
}

template <typename T>
HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars_integer(char* first, char* last, T value, int base)
{
	return hamon::detail::to_chars_integer_impl(
		first, last, value, base, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_TO_CHARS_INTEGER_HPP
