/**
 *	@file	__is_escaped_sequence_written.hpp
 *
 *	@brief	__is_escaped_sequence_written の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___IS_ESCAPED_SEQUENCE_WRITTEN_HPP
#define HAMON_FORMAT___FORMATTER___IS_ESCAPED_SEQUENCE_WRITTEN_HPP

#include <hamon/format/__formatter/__write_well_formed_escaped_code_unit.hpp>
#include <hamon/format/other/__escaped_output_table.hpp>
#include <hamon/format/other/__extended_grapheme_custer_property_boundary.hpp>
#include <hamon/string.hpp>

namespace hamon
{

namespace __formatter
{

template <class _CharT>
[[nodiscard]] bool
__is_escaped_sequence_written(hamon::basic_string<_CharT>& __str, bool __last_escaped, char32_t __value)
{
#  if !_LIBCPP_HAS_UNICODE
	// For ASCII assume everything above 127 is printable.
	if (__value > 127)
	{
		return false;
	}
#  endif

	// [format.string.escaped]/2.2.1.2.1
	//   CE is UTF-8, UTF-16, or UTF-32 and C corresponds to a Unicode scalar
	//   value whose Unicode property General_Category has a value in the groups
	//   Separator (Z) or Other (C), as described by UAX #44 of the Unicode Standard,
	if (!__escaped_output_table::__needs_escape(__value))
	{
		// [format.string.escaped]/2.2.1.2.2
		//   CE is UTF-8, UTF-16, or UTF-32 and C corresponds to a Unicode scalar
		//   value with the Unicode property Grapheme_Extend=Yes as described by UAX
		//   #44 of the Unicode Standard and C is not immediately preceded in S by a
		//   character P appended to E without translation to an escape sequence,
		if (!__last_escaped || __extended_grapheme_custer_property_boundary::__get_property(__value) !=
								   __extended_grapheme_custer_property_boundary::__property::__Extend)
		{
			return false;
		}
	}

	__formatter::__write_well_formed_escaped_code_unit(__str, __value);
	return true;
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___IS_ESCAPED_SEQUENCE_WRITTEN_HPP
