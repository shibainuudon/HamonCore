/**
 *	@file	__handle_replacement_field.hpp
 *
 *	@brief	__handle_replacement_field の定義
 */

#ifndef HAMON_FORMAT___FORMAT___HANDLE_REPLACEMENT_FIELD_HPP
#define HAMON_FORMAT___FORMAT___HANDLE_REPLACEMENT_FIELD_HPP

#include <hamon/format/__format/__parse_number_result.hpp>
#include <hamon/format/__format/__parse_arg_id.hpp>
#include <hamon/format/__format/__compile_time_basic_format_context.hpp>
#include <hamon/format/__format/__arg_t.hpp>
#include <hamon/format/__format/__compile_time_visit_format_arg.hpp>
#include <hamon/format/other/__visit_format_arg.hpp>
#include <hamon/format/basic_format_arg.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/format/formatter.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/iter_value_t.hpp>

namespace hamon
{

namespace __format
{

template <contiguous_iterator _Iterator, class _ParseCtx, class _Ctx>
constexpr _Iterator
__handle_replacement_field(_Iterator __begin, _Iterator __end, _ParseCtx& __parse_ctx, _Ctx& __ctx)
{
	using _CharT                        = hamon::iter_value_t<_Iterator>;
	__format::__parse_number_result __r = __format::__parse_arg_id(__begin, __end, __parse_ctx);

	if (__r.__last == __end)
	{
		hamon::detail::throw_format_error("The argument index should end with a ':' or a '}'");
	}

	bool __parse = *__r.__last == _CharT(':');
	switch (*__r.__last)
	{
	case _CharT(':'):
		// The arg-id has a format-specifier, advance the input to the format-spec.
		__parse_ctx.advance_to(__r.__last + 1);
		break;
	case _CharT('}'):
		// The arg-id has no format-specifier.
		__parse_ctx.advance_to(__r.__last);
		break;
	default:
		hamon::detail::throw_format_error("The argument index should end with a ':' or a '}'");
	}

	if constexpr (hamon::same_as<_Ctx, __compile_time_basic_format_context<_CharT>>)
	{
		__arg_t __type = __ctx.arg(__r.__value);
		if (__type == __arg_t::__none)
		{
			hamon::detail::throw_format_error("The argument index value is too large for the number of arguments supplied");
		}
		else if (__type == __arg_t::__handle)
		{
			__ctx.__handle(__r.__value).__parse(__parse_ctx);
		}
		else if (__parse)
		{
			__format::__compile_time_visit_format_arg(__parse_ctx, __ctx, __type);
		}
	}
	else
	{
		hamon::__visit_format_arg(
			[&](auto __arg) {
				if constexpr (hamon::same_as<decltype(__arg), monostate>)
				{
					hamon::detail::throw_format_error("The argument index value is too large for the number of arguments supplied");
				}
				else if constexpr (hamon::same_as<decltype(__arg), typename hamon::basic_format_arg<_Ctx>::handle>)
				{
					__arg.format(__parse_ctx, __ctx);
				}
				else
				{
					hamon::formatter<decltype(__arg), _CharT> __formatter;
					if (__parse)
					{
						__parse_ctx.advance_to(__formatter.parse(__parse_ctx));
					}
					__ctx.advance_to(__formatter.format(__arg, __ctx));
				}
			},
			__ctx.arg(__r.__value));
	}

	__begin = __parse_ctx.begin();
	if (__begin == __end || *__begin != _CharT('}'))
	{
		hamon::detail::throw_format_error("The replacement field misses a terminating '}'");
	}

	return ++__begin;
}

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___HANDLE_REPLACEMENT_FIELD_HPP
