/**
 *	@file	from_chars.hpp
 *
 *	@brief	from_chars の定義
 */

#ifndef HAMON_CHARCONV_FROM_CHARS_HPP
#define HAMON_CHARCONV_FROM_CHARS_HPP

#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/charconv/config.hpp>

#if defined(HAMON_USE_STD_CHARCONV)

#include <charconv>

namespace hamon
{

using std::from_chars;

}	// namespace hamon

#else

#include <hamon/charconv/detail/from_chars_integer.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 28.2.3 Primitive numeric input conversion[charconv.from.chars]

template <typename T, typename = hamon::enable_if_t<hamon::is_integral<T>::value>>
HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars(char const* first, char const* last, T& value, int base = 10)
{
	// [charconv.from.chars]/2
	HAMON_ASSERT(2 <= base && base <= 36);

	return hamon::detail::from_chars_integer(first, last, value, base);
}

}	// namespace hamon

#endif

#endif // HAMON_CHARCONV_FROM_CHARS_HPP
