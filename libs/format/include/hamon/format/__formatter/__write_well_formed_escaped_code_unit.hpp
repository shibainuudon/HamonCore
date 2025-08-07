/**
 *	@file	__write_well_formed_escaped_code_unit.hpp
 *
 *	@brief	__write_well_formed_escaped_code_unit の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___WRITE_WELL_FORMED_ESCAPED_CODE_UNIT_HPP
#define HAMON_FORMAT___FORMATTER___WRITE_WELL_FORMED_ESCAPED_CODE_UNIT_HPP

#include <hamon/format/__formatter/__write_escaped_code_unit.hpp>
#include <hamon/string.hpp>
#include <hamon/detail/statically_widen.hpp>

namespace hamon
{

namespace __formatter
{

// [format.string.escaped]/2.2.1.2
// ...
// then the sequence \u{hex-digit-sequence} is appended to E, where
// hex-digit-sequence is the shortest hexadecimal representation of C using
// lower-case hexadecimal digits.
template <class _CharT>
void __write_well_formed_escaped_code_unit(hamon::basic_string<_CharT>& __str, char32_t __value)
{
	__formatter::__write_escaped_code_unit(__str, __value, HAMON_STATICALLY_WIDEN(_CharT, "\\u{"));
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___WRITE_WELL_FORMED_ESCAPED_CODE_UNIT_HPP
