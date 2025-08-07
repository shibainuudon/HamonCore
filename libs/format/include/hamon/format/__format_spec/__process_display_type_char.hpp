/**
 *	@file	__process_display_type_char.hpp
 *
 *	@brief	__process_display_type_char の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_CHAR_HPP
#define HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_CHAR_HPP

#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__format_spec/__process_display_type_bool_string.hpp>

namespace hamon
{

namespace __format_spec
{

template <class _CharT>
constexpr void __process_display_type_char(__parser<_CharT>& __parser, const char* __id)
{
	__format_spec::__process_display_type_bool_string(__parser, __id);
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___PROCESS_DISPLAY_TYPE_CHAR_HPP
