/**
 *	@file	__process_display_type_pointer.hpp
 *
 *	@brief	__process_display_type_pointer の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_POINTER_HPP
#define HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_POINTER_HPP

#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__throw_invalid_type_format_error.hpp>

namespace hamon
{

namespace __format_spec
{

constexpr void __process_display_type_pointer(__format_spec::__type __type, const char* __id)
{
	switch (__type)
	{
	case __format_spec::__type::__default:
	case __format_spec::__type::__pointer_lower_case:
	case __format_spec::__type::__pointer_upper_case:
		break;

	default:
		__format_spec::__throw_invalid_type_format_error(__id);
	}
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_POINTER_HPP
