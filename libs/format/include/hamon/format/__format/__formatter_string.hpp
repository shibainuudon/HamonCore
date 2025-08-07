/**
 *	@file	__formatter_string.hpp
 *
 *	@brief	__formatter_string の定義
 */

#ifndef HAMON_FORMAT___FORMAT___FORMATTER_STRING_HPP
#define HAMON_FORMAT___FORMAT___FORMATTER_STRING_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format_spec/__process_display_type_string.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__alignment.hpp>
#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__format_spec/__fields_string.hpp>
#include <hamon/format/__formatter/__format_escaped_string.hpp>
#include <hamon/format/__formatter/__write_string.hpp>
#include <hamon/string_view.hpp>

namespace hamon
{

namespace __format
{

template <__format::__fmt_char_type _CharT>
struct __formatter_string
{
public:
	template <class _ParseContext>
	constexpr typename _ParseContext::iterator
	parse(_ParseContext& __ctx)
	{
		typename _ParseContext::iterator __result = __parser_.__parse(__ctx, __format_spec::__fields_string);
		__format_spec::__process_display_type_string(__parser_.__type_);
		return __result;
	}

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(hamon::basic_string_view<_CharT> __str, _FormatContext& __ctx) const
	{
		if (__parser_.__type_ == __format_spec::__type::__debug)
		{
			return __formatter::__format_escaped_string(__str, __ctx.out(), __parser_.__get_parsed_std_specifications(__ctx));
		}

		return __formatter::__write_string(__str, __ctx.out(), __parser_.__get_parsed_std_specifications(__ctx));
	}

	constexpr void set_debug_format() { __parser_.__type_ = __format_spec::__type::__debug; }

	__format_spec::__parser<_CharT> __parser_ {.__alignment_ = __format_spec::__alignment::__left};
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___FORMATTER_STRING_HPP
