/**
 *	@file	__parse_arg_id.hpp
 *
 *	@brief	__parse_arg_id の定義
 */

#ifndef HAMON_FORMAT___FORMAT___PARSE_ARG_ID_HPP
#define HAMON_FORMAT___FORMAT___PARSE_ARG_ID_HPP

#include <hamon/format/__format/__parse_number_result.hpp>
#include <hamon/format/__format/__parse_number.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>

namespace hamon
{

namespace __format
{

namespace __detail
{

template <hamon::contiguous_iterator _Iterator>
constexpr __parse_number_result<_Iterator>
__parse_zero(_Iterator __begin, _Iterator, auto& __parse_ctx)
{
	__parse_ctx.check_arg_id(0);
	return {++__begin, 0}; // can never be larger than the maximum.
}

template <hamon::contiguous_iterator _Iterator>
constexpr __parse_number_result<_Iterator>
__parse_automatic(_Iterator __begin, _Iterator, auto& __parse_ctx)
{
	size_t __value = __parse_ctx.next_arg_id();
	//_LIBCPP_ASSERT_UNCATEGORIZED(__value <= __number_max, "Compilers don't support this number of arguments");

	return {__begin, uint32_t(__value)};
}

template <hamon::contiguous_iterator _Iterator>
constexpr __parse_number_result<_Iterator>
__parse_manual(_Iterator __begin, _Iterator __end, auto& __parse_ctx)
{
	__parse_number_result<_Iterator> __r = __format::__parse_number(__begin, __end);
	__parse_ctx.check_arg_id(__r.__value);
	return __r;
}

} // namespace __detail

/**
 * Multiplexer for all parse functions.
 *
 * The parser will return a pointer beyond the last consumed character. This
 * should be the closing '}' of the arg-id.
 */
template <hamon::contiguous_iterator _Iterator>
constexpr __parse_number_result<_Iterator>
__parse_arg_id(_Iterator __begin, _Iterator __end, auto& __parse_ctx)
{
	using _CharT = hamon::iter_value_t<_Iterator>;
	switch (*__begin)
	{
	case _CharT('0'):
		return __detail::__parse_zero(__begin, __end, __parse_ctx);

	case _CharT(':'):
		// This case is conditionally valid. It's allowed in an arg-id in the
		// replacement-field, but not in the std-format-spec. The caller can
		// provide a better diagnostic, so accept it here unconditionally.
	case _CharT('}'):
		return __detail::__parse_automatic(__begin, __end, __parse_ctx);
	}

	if (*__begin < _CharT('0') || *__begin > _CharT('9'))
	{
		hamon::detail::throw_format_error("The argument index starts with an invalid character");
	}

	return __detail::__parse_manual(__begin, __end, __parse_ctx);
}

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___PARSE_ARG_ID_HPP
