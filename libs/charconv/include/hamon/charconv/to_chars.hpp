/**
 *	@file	to_chars.hpp
 *
 *	@brief	to_chars の定義
 */

#ifndef HAMON_CHARCONV_TO_CHARS_HPP
#define HAMON_CHARCONV_TO_CHARS_HPP

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
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
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

	return hamon::detail::to_chars_integer(first, last, value, base);
}

hamon::to_chars_result to_chars(char*, char*, bool, int = 10) = delete;

}	// namespace hamon

#endif

#endif // HAMON_CHARCONV_TO_CHARS_HPP
