/**
 *	@file	__compile_time_validate_argument.hpp
 *
 *	@brief	__compile_time_validate_argument の定義
 */

#ifndef HAMON_FORMAT___FORMAT___COMPILE_TIME_VALIDATE_ARGUMENT_HPP
#define HAMON_FORMAT___FORMAT___COMPILE_TIME_VALIDATE_ARGUMENT_HPP

#include <hamon/format/__format/__arg_t.hpp>
#include <hamon/format/__format/__compile_time_basic_format_context.hpp>
#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/format/formatter.hpp>

namespace hamon
{

namespace __format
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

// [format.string.std]/8
// If { arg-idopt } is used in a width or precision, the value of the
// corresponding formatting argument is used in its place. If the
// corresponding formatting argument is not of standard signed or unsigned
// integer type, or its value is negative for precision or non-positive for
// width, an exception of type format_error is thrown.
//
// _HasPrecision does the formatter have a precision?
template <class _CharT, class _Tp, bool _HasPrecision = false>
constexpr void __compile_time_validate_argument(
	hamon::basic_format_parse_context<_CharT>& __parse_ctx,
	__compile_time_basic_format_context<_CharT>& __ctx)
{
	auto __validate_type = [](__arg_t __type) {
		// LWG3720 originally allowed "signed or unsigned integer types", however
		// the final version explicitly changed it to "*standard* signed or unsigned
		// integer types". It's trivial to use 128-bit integrals in libc++'s
		// implementation, but other implementations may not implement it.
		// (Using a width or precision, that does not fit in 64-bits, sounds very
		// unlikely in real world code.)
		switch (__type)
		{
		case __arg_t::__int:
		case __arg_t::__long_long:
		case __arg_t::__unsigned:
		case __arg_t::__unsigned_long_long:
			return;

		default:
			hamon::detail::throw_format_error("Replacement argument isn't a standard signed or unsigned integer type");
		}
	};

	hamon::formatter<_Tp, _CharT> __formatter;
	__parse_ctx.advance_to(__formatter.parse(__parse_ctx));
	if (__formatter.__parser_.__width_as_arg_)
	{
		__validate_type(__ctx.arg(__formatter.__parser_.__width_));
	}

	if constexpr (_HasPrecision)
	{
		if (__formatter.__parser_.__precision_as_arg_)
		{
			__validate_type(__ctx.arg(__formatter.__parser_.__precision_));
		}
	}
}

HAMON_WARNING_POP()

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___COMPILE_TIME_VALIDATE_ARGUMENT_HPP
