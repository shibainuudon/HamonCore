/**
 *	@file	__write_escape_ill_formed_code_unit.hpp
 *
 *	@brief	__write_escape_ill_formed_code_unit の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___WRITE_ESCAPE_ILL_FORMED_CODE_UNIT_HPP
#define HAMON_FORMAT___FORMATTER___WRITE_ESCAPE_ILL_FORMED_CODE_UNIT_HPP

#include <hamon/format/__formatter/__write_escaped_code_unit.hpp>
#include <hamon/string.hpp>
#include <hamon/detail/statically_widen.hpp>

namespace hamon
{

namespace __formatter
{

// [format.string.escaped]/2.2.3
// Otherwise (X is a sequence of ill-formed code units), each code unit U is
// appended to E in order as the sequence \x{hex-digit-sequence}, where
// hex-digit-sequence is the shortest hexadecimal representation of U using
// lower-case hexadecimal digits.
template <class _CharT>
void __write_escape_ill_formed_code_unit(hamon::basic_string<_CharT>& __str, char32_t __value)
{
	__formatter::__write_escaped_code_unit(__str, __value, HAMON_STATICALLY_WIDEN(_CharT, "\\x{"));
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___WRITE_ESCAPE_ILL_FORMED_CODE_UNIT_HPP
