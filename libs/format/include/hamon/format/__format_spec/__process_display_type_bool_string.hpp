/**
 *	@file	__process_display_type_bool_string.hpp
 *
 *	@brief	__process_display_type_bool_string の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_BOOL_STRING_HPP
#define HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_BOOL_STRING_HPP

#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__format_spec/__fields_bool.hpp>
#include <hamon/format/__format_spec/__alignment.hpp>

namespace hamon
{

namespace __format_spec
{

template <class _CharT>
constexpr void
__process_display_type_bool_string(__parser<_CharT>& __parser, const char* __id)
{
	__parser.__validate(__format_spec::__fields_bool, __id);
	if (__parser.__alignment_ == __alignment::__default)
	{
		__parser.__alignment_ = __alignment::__left;
	}
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_BOOL_STRING_HPP
