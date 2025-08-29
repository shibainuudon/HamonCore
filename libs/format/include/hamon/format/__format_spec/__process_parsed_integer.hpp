/**
 *	@file	__process_parsed_integer.hpp
 *
 *	@brief	__process_parsed_integer の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___PROCESS_PARSED_INTEGER_HPP
#define HAMON_FORMAT___FORMAT_SPEC___PROCESS_PARSED_INTEGER_HPP

#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__process_display_type_char.hpp>
#include <hamon/format/__format_spec/__throw_invalid_type_format_error.hpp>

namespace hamon
{

namespace __format_spec
{

template <class _CharT>
constexpr void
__process_parsed_integer(__format_spec::__parser<_CharT>& __parser, const char* __id)
{
	switch (__parser.__type_)
	{
	case __format_spec::__type::__default:
	case __format_spec::__type::__binary_lower_case:
	case __format_spec::__type::__binary_upper_case:
	case __format_spec::__type::__octal:
	case __format_spec::__type::__decimal:
	case __format_spec::__type::__hexadecimal_lower_case:
	case __format_spec::__type::__hexadecimal_upper_case:
		break;

	case __format_spec::__type::__char:
		__format_spec::__process_display_type_char(__parser, __id);
		break;

	default:
		__format_spec::__throw_invalid_type_format_error(__id);
	}
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___PROCESS_PARSED_INTEGER_HPP
