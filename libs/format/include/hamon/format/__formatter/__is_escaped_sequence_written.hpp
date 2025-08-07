/**
 *	@file	__is_escaped_sequence_written.hpp
 *
 *	@brief	__is_escaped_sequence_written の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___IS_ESCAPED_SEQUENCE_WRITTEN_HPP
#define HAMON_FORMAT___FORMATTER___IS_ESCAPED_SEQUENCE_WRITTEN_HPP

#include <hamon/format/__formatter/__write_well_formed_escaped_code_unit.hpp>
#include <hamon/format/__formatter/__escape_quotation_mark.hpp>
#include <hamon/format/__formatter/__to_char32.hpp>
#include <hamon/format/other/__escaped_output_table.hpp>
#include <hamon/format/other/__extended_grapheme_custer_property_boundary.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/string.hpp>

namespace hamon
{

namespace __formatter
{

template <class _CharT>
[[nodiscard]] bool
__is_escaped_sequence_written(hamon::basic_string<_CharT>& __str, bool __last_escaped, char32_t __value)
{
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

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '' から '' への変換です。データが失われる可能性があります。
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

// [format.string.escaped]/2
template <class _CharT>
[[nodiscard]] bool
__is_escaped_sequence_written(
	hamon::basic_string<_CharT>& __str, char32_t __value, bool __last_escaped, __formatter::__escape_quotation_mark __mark)
{
	// 2.2.1.1 - Mapped character in [tab:format.escape.sequences]
	switch (__value)
	{
	case _CharT('\t'):
		__str += HAMON_STATICALLY_WIDEN(_CharT, "\\t");
		return true;
	case _CharT('\n'):
		__str += HAMON_STATICALLY_WIDEN(_CharT, "\\n");
		return true;
	case _CharT('\r'):
		__str += HAMON_STATICALLY_WIDEN(_CharT, "\\r");
		return true;
	case _CharT('\''):
		if (__mark == __formatter::__escape_quotation_mark::__apostrophe)
		{
			__str += HAMON_STATICALLY_WIDEN(_CharT, R"(\')");
		}
		else
		{
			__str += __value;
		}
		return true;
	case _CharT('"'):
		if (__mark == __formatter::__escape_quotation_mark::__double_quote)
		{
			__str += HAMON_STATICALLY_WIDEN(_CharT, R"(\")");
		}
		else
		{
			__str += __value;
		}
		return true;
	case _CharT('\\'):
		__str += HAMON_STATICALLY_WIDEN(_CharT, R"(\\)");
		return true;

		// 2.2.1.2 - Space
	case _CharT(' '):
		__str += __value;
		return true;
	}

	// 2.2.2
	//   Otherwise, if X is a shift sequence, the effect on E and further
	//   decoding of S is unspecified.
	// For now shift sequences are ignored and treated as Unicode. Other parts
	// of the format library do the same. It's unknown how ostream treats them.
	// TODO FMT determine what to do with shift sequences.

	// 2.2.1.2.1 and 2.2.1.2.2 - Escape
	return __formatter::__is_escaped_sequence_written(__str, __last_escaped, __formatter::__to_char32(__value));
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___IS_ESCAPED_SEQUENCE_WRITTEN_HPP
