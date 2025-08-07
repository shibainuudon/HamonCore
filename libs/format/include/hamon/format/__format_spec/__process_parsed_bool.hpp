/**
 *	@file	__process_parsed_bool.hpp
 *
 *	@brief	__process_parsed_bool の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___PROCESS_PARSED_BOOL_HPP
#define HAMON_FORMAT___FORMAT_SPEC___PROCESS_PARSED_BOOL_HPP

#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__format_spec/__throw_invalid_type_format_error.hpp>
#include <hamon/format/__format_spec/__process_display_type_bool_string.hpp>

namespace hamon
{

namespace __format_spec
{

template <class _CharT>
constexpr void __process_parsed_bool(__parser<_CharT>& __parser, const char* __id)
{
	switch (__parser.__type_)
	{
	case __format_spec::__type::__default:
	case __format_spec::__type::__string:
		__format_spec::__process_display_type_bool_string(__parser, __id);
		break;

	case __format_spec::__type::__binary_lower_case:
	case __format_spec::__type::__binary_upper_case:
	case __format_spec::__type::__octal:
	case __format_spec::__type::__decimal:
	case __format_spec::__type::__hexadecimal_lower_case:
	case __format_spec::__type::__hexadecimal_upper_case:
		break;

	default:
		__format_spec::__throw_invalid_type_format_error(__id);
	}
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___PROCESS_PARSED_BOOL_HPP
