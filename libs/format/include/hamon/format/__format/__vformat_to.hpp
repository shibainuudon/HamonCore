/**
 *	@file	__vformat_to.hpp
 *
 *	@brief	__vformat_to の定義
 */

#ifndef HAMON_FORMAT___FORMAT___VFORMAT_TO_HPP
#define HAMON_FORMAT___FORMAT___VFORMAT_TO_HPP

#include <hamon/format/format_error.hpp>
#include <hamon/format/__format/__handle_replacement_field.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __format
{

template <class _ParseCtx, class _Ctx>
constexpr typename _Ctx::iterator
__vformat_to(_ParseCtx&& __parse_ctx, _Ctx&& __ctx)
{
	using _CharT = typename _ParseCtx::char_type;
	static_assert(same_as<typename _Ctx::char_type, _CharT>);

	auto __begin                     = __parse_ctx.begin();
	auto __end                       = __parse_ctx.end();
	typename _Ctx::iterator __out_it = __ctx.out();
	while (__begin != __end)
	{
		switch (*__begin)
		{
		case _CharT('{'):
			++__begin;
			if (__begin == __end)
			{
				hamon::detail::throw_format_error("The format string terminates at a '{'");
			}

			if (*__begin != _CharT('{')) [[likely]]
			{
				__ctx.advance_to(hamon::move(__out_it));
				__begin  = __format::__handle_replacement_field(__begin, __end, __parse_ctx, __ctx);
				__out_it = __ctx.out();

				// The output is written and __begin points to the next character. So
				// start the next iteration.
				continue;
			}
			// The string is an escape character.
			break;

		case _CharT('}'):
			++__begin;
			if (__begin == __end || *__begin != _CharT('}'))
			{
				hamon::detail::throw_format_error("The format string contains an invalid escape sequence");
			}

			break;
		}

		// Copy the character to the output verbatim.
		*__out_it++ = *__begin++;
	}
	return __out_it;
}

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___VFORMAT_TO_HPP
