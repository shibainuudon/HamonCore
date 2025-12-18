/**
 *	@file	to_chars.hpp
 *
 *	@brief	to_chars の定義
 */

#ifndef HAMON_CHARCONV_TO_CHARS_HPP
#define HAMON_CHARCONV_TO_CHARS_HPP

#include <hamon/charconv/chars_format.hpp>
#include <hamon/charconv/to_chars_result.hpp>
#include <hamon/charconv/config.hpp>

#if defined(HAMON_USE_STD_CHARCONV)

#include <charconv>

namespace hamon
{

using std::to_chars;

}	// namespace hamon

#else

#include <hamon/charconv/detail/to_chars_integer.hpp>
#include <hamon/charconv/detail/to_chars_floating_point.hpp>
#include <hamon/charconv/detail/to_chars_floating_point_precision.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 28.2.2 Primitive numeric output conversion[charconv.to.chars]

template <typename T, typename = hamon::enable_if_t<hamon::is_integral<T>::value>>
HAMON_CXX14_CONSTEXPR hamon::to_chars_result
to_chars(char* first, char* last, T value, int base = 10)
{
	// [charconv.to.chars]/4
	HAMON_ASSERT(2 <= base && base <= 36);

	// [charconv.to.chars]/5
	return hamon::detail::to_chars_integer(first, last, value, base);
}

hamon::to_chars_result to_chars(char*, char*, bool, int = 10) = delete;

template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
hamon::to_chars_result
to_chars(char* first, char* last, T value)
{
	// [charconv.to.chars]/7
	return hamon::detail::to_chars_floating_point(first, last, value, hamon::chars_format{});
}

template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
hamon::to_chars_result
to_chars(char* first, char* last, T value, hamon::chars_format fmt)
{
	// [charconv.to.chars]/9
	HAMON_ASSERT(
		fmt == hamon::chars_format::scientific ||
		fmt == hamon::chars_format::fixed ||
		fmt == hamon::chars_format::hex ||
		fmt == hamon::chars_format::general);

	// [charconv.to.chars]/10
	return hamon::detail::to_chars_floating_point(first, last, value, fmt);
}

template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
hamon::to_chars_result
to_chars(char* first, char* last, T value, hamon::chars_format fmt, int precision)
{
	// [charconv.to.chars]/12
	HAMON_ASSERT(
		fmt == hamon::chars_format::scientific ||
		fmt == hamon::chars_format::fixed ||
		fmt == hamon::chars_format::hex ||
		fmt == hamon::chars_format::general);

	// [charconv.to.chars]/13
	return hamon::detail::to_chars_floating_point_precision(first, last, value, fmt, precision);
}

}	// namespace hamon

#endif

#endif // HAMON_CHARCONV_TO_CHARS_HPP
