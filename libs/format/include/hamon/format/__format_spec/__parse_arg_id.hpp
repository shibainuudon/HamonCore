/**
 *	@file	__parse_arg_id.hpp
 *
 *	@brief	__parse_arg_id の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___PARSE_ARG_ID_HPP
#define HAMON_FORMAT___FORMAT_SPEC___PARSE_ARG_ID_HPP

#include <hamon/format/__format/__parse_number_result.hpp>
#include <hamon/format/__format/__parse_arg_id.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>

namespace hamon
{

namespace __format_spec
{

template <hamon::contiguous_iterator _Iterator, class _ParseContext>
constexpr __format::__parse_number_result<_Iterator>
__parse_arg_id(_Iterator __begin, _Iterator __end, _ParseContext& __ctx)
{
	using _CharT = hamon::iter_value_t<_Iterator>;
	// This function is a wrapper to call the real parser. But it does the
	// validation for the pre-conditions and post-conditions.
	if (__begin == __end)
	{
		hamon::detail::throw_format_error("End of input while parsing an argument index");
	}

	__format::__parse_number_result __r = __format::__parse_arg_id(__begin, __end, __ctx);

	if (__r.__last == __end || *__r.__last != _CharT('}'))
	{
		hamon::detail::throw_format_error("The argument index is invalid");
	}

	++__r.__last;
	return __r;
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___PARSE_ARG_ID_HPP
