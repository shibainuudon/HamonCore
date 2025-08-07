/**
 *	@file	__formatter_char.hpp
 *
 *	@brief	__formatter_char の定義
 */

#ifndef HAMON_FORMAT___FORMAT___FORMATTER_CHAR_HPP
#define HAMON_FORMAT___FORMAT___FORMATTER_CHAR_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format_spec/__fields_integral.hpp>
#include <hamon/format/__format_spec/__process_parsed_char.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__formatter/__format_char.hpp>
#include <hamon/format/__formatter/__format_escaped_char.hpp>
#include <hamon/format/__formatter/__format_integer.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/make_unsigned.hpp>

namespace hamon
{

namespace __format
{

template <__format::__fmt_char_type _CharT>
struct __formatter_char
{
public:
	template <class _ParseContext>
	constexpr typename _ParseContext::iterator
	parse(_ParseContext& __ctx)
	{
		typename _ParseContext::iterator __result = __parser_.__parse(__ctx, __format_spec::__fields_integral);
		__format_spec::__process_parsed_char(__parser_, "a character");
		return __result;
	}

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(_CharT __value, _FormatContext& __ctx) const
	{
		if (__parser_.__type_ == __format_spec::__type::__default || __parser_.__type_ == __format_spec::__type::__char)
		{
			return __formatter::__format_char(__value, __ctx.out(), __parser_.__get_parsed_std_specifications(__ctx));
		}

		if (__parser_.__type_ == __format_spec::__type::__debug)
		{
			return __formatter::__format_escaped_char(__value, __ctx.out(), __parser_.__get_parsed_std_specifications(__ctx));
		}

		if constexpr (sizeof(_CharT) <= sizeof(unsigned))
		{
			return __formatter::__format_integer(
				static_cast<unsigned>(static_cast<hamon::make_unsigned_t<_CharT>>(__value)),
				__ctx,
				__parser_.__get_parsed_std_specifications(__ctx));
		}
		else
		{
			return __formatter::__format_integer(
				static_cast<hamon::make_unsigned_t<_CharT>>(__value), __ctx, __parser_.__get_parsed_std_specifications(__ctx));
		}
	}

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(char __value, _FormatContext& __ctx) const
		requires(hamon::same_as<_CharT, wchar_t>)
	{
		return format(static_cast<wchar_t>(static_cast<unsigned char>(__value)), __ctx);
	}

	constexpr void set_debug_format() { __parser_.__type_ = __format_spec::__type::__debug; }

	__format_spec::__parser<_CharT> __parser_;
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___FORMATTER_CHAR_HPP
