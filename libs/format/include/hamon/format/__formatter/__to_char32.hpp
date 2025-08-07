/**
 *	@file	__to_char32.hpp
 *
 *	@brief	__to_char32 の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___TO_CHAR32_HPP
#define HAMON_FORMAT___FORMATTER___TO_CHAR32_HPP

#include <hamon/type_traits/make_unsigned.hpp>

namespace hamon
{

namespace __formatter
{

template <class _CharT>
[[nodiscard]] constexpr char32_t __to_char32(_CharT __value)
{
	return static_cast<hamon::make_unsigned_t<_CharT>>(__value);
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___TO_CHAR32_HPP
