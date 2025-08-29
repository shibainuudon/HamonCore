/**
 *	@file	__process_display_type_string.hpp
 *
 *	@brief	__process_display_type_string の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_STRING_HPP
#define HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_STRING_HPP

#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/format_error.hpp>

namespace hamon
{

namespace __format_spec
{

constexpr void __process_display_type_string(__format_spec::__type __type)
{
	switch (__type)
	{
	case __format_spec::__type::__default:
	case __format_spec::__type::__string:
	case __format_spec::__type::__debug:
		break;

	default:
		hamon::detail::throw_format_error("The type option contains an invalid value for a string formatting argument");
	}
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_STRING_HPP
