/**
 *	@file	__process_parsed_floating_point.hpp
 *
 *	@brief	__process_parsed_floating_point の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___PROCESS_PARSED_FLOATING_POINT_HPP
#define HAMON_FORMAT___FORMAT_SPEC___PROCESS_PARSED_FLOATING_POINT_HPP

#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__throw_invalid_type_format_error.hpp>

namespace hamon
{

namespace __format_spec
{

template <class _CharT>
constexpr void __process_parsed_floating_point(__format_spec::__parser<_CharT>& __parser, const char* __id)
{
	switch (__parser.__type_)
	{
	case __format_spec::__type::__default:
	case __format_spec::__type::__hexfloat_lower_case:
	case __format_spec::__type::__hexfloat_upper_case:
		// Precision specific behavior will be handled later.
		break;
	case __format_spec::__type::__scientific_lower_case:
	case __format_spec::__type::__scientific_upper_case:
	case __format_spec::__type::__fixed_lower_case:
	case __format_spec::__type::__fixed_upper_case:
	case __format_spec::__type::__general_lower_case:
	case __format_spec::__type::__general_upper_case:
		if (!__parser.__precision_as_arg_ && __parser.__precision_ == -1)
		{
			// Set the default precision for the call to to_chars.
			__parser.__precision_ = 6;
		}
		break;

	default:
		__format_spec::__throw_invalid_type_format_error(__id);
	}
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___PROCESS_PARSED_FLOATING_POINT_HPP
