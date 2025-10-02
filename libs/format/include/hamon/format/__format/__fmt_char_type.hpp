/**
 *	@file	__fmt_char_type.hpp
 *
 *	@brief	__fmt_char_type の定義
 */

#ifndef HAMON_FORMAT___FORMAT___FMT_CHAR_TYPE_HPP
#define HAMON_FORMAT___FORMAT___FMT_CHAR_TYPE_HPP

#include <hamon/concepts/same_as.hpp>

namespace hamon
{

namespace __format
{

/// The character type specializations of \ref formatter.
template <class _CharT>
concept __fmt_char_type = same_as<_CharT, char> || same_as<_CharT, wchar_t>;

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___FMT_CHAR_TYPE_HPP
