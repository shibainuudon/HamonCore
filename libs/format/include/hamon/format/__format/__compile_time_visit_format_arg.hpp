/**
 *	@file	__compile_time_visit_format_arg.hpp
 *
 *	@brief	__compile_time_visit_format_arg の定義
 */

#ifndef HAMON_FORMAT___FORMAT___COMPILE_TIME_VISIT_FORMAT_ARG_HPP
#define HAMON_FORMAT___FORMAT___COMPILE_TIME_VISIT_FORMAT_ARG_HPP

#include <hamon/format/__format/__compile_time_basic_format_context.hpp>
#include <hamon/format/__format/__arg_t.hpp>
#include <hamon/format/__format/__compile_time_validate_argument.hpp>
#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/format/format_error.hpp>

namespace hamon
{

namespace __format
{

// This function is not user facing, so it can directly use the non-standard types of the "variant".
template <class _CharT>
constexpr void __compile_time_visit_format_arg(
	hamon::basic_format_parse_context<_CharT>& __parse_ctx,
	__compile_time_basic_format_context<_CharT>& __ctx,
	__arg_t __type)
{
	switch (__type)
	{
	case __arg_t::__none:
		hamon::detail::throw_format_error("Invalid argument");
	case __arg_t::__boolean:
		return __format::__compile_time_validate_argument<_CharT, bool>(__parse_ctx, __ctx);
	case __arg_t::__char_type:
		return __format::__compile_time_validate_argument<_CharT, _CharT>(__parse_ctx, __ctx);
	case __arg_t::__int:
		return __format::__compile_time_validate_argument<_CharT, int>(__parse_ctx, __ctx);
	case __arg_t::__long_long:
		return __format::__compile_time_validate_argument<_CharT, long long>(__parse_ctx, __ctx);
	case __arg_t::__unsigned:
		return __format::__compile_time_validate_argument<_CharT, unsigned>(__parse_ctx, __ctx);
	case __arg_t::__unsigned_long_long:
		return __format::__compile_time_validate_argument<_CharT, unsigned long long>(__parse_ctx, __ctx);
	case __arg_t::__float:
		return __format::__compile_time_validate_argument<_CharT, float, true>(__parse_ctx, __ctx);
	case __arg_t::__double:
		return __format::__compile_time_validate_argument<_CharT, double, true>(__parse_ctx, __ctx);
	case __arg_t::__long_double:
		return __format::__compile_time_validate_argument<_CharT, long double, true>(__parse_ctx, __ctx);
	case __arg_t::__const_char_type_ptr:
		return __format::__compile_time_validate_argument<_CharT, const _CharT*, true>(__parse_ctx, __ctx);
	case __arg_t::__string_view:
		return __format::__compile_time_validate_argument<_CharT, basic_string_view<_CharT>, true>(__parse_ctx, __ctx);
	case __arg_t::__ptr:
		return __format::__compile_time_validate_argument<_CharT, const void*>(__parse_ctx, __ctx);
	case __arg_t::__handle:
		hamon::detail::throw_format_error("Handle should use __compile_time_validate_handle_argument");
	}
	hamon::detail::throw_format_error("Invalid argument");
}

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___COMPILE_TIME_VISIT_FORMAT_ARG_HPP
