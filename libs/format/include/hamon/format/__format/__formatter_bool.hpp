/**
 *	@file	__formatter_bool.hpp
 *
 *	@brief	__formatter_bool の定義
 */

#ifndef HAMON_FORMAT___FORMAT___FORMATTER_BOOL_HPP
#define HAMON_FORMAT___FORMAT___FORMATTER_BOOL_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format_spec/__fields_integral.hpp>
#include <hamon/format/__format_spec/__process_parsed_bool.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__formatter/__format_bool.hpp>
#include <hamon/format/__formatter/__format_integer.hpp>

namespace hamon
{

namespace __format
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4715)	// 値を返さないコントロール パスがあります。
HAMON_WARNING_DISABLE_CLANG("-Wreturn-type")

template <__format::__fmt_char_type _CharT>
struct __formatter_bool
{
public:
	template <class _ParseContext>
	constexpr typename _ParseContext::iterator parse(_ParseContext& __ctx)
	{
		typename _ParseContext::iterator __result = __parser_.__parse(__ctx, __format_spec::__fields_integral);
		__format_spec::__process_parsed_bool(__parser_, "a bool");
		return __result;
	}

	template <class _FormatContext>
	typename _FormatContext::iterator format(bool __value, _FormatContext& __ctx) const
	{
		switch (__parser_.__type_)
		{
		case __format_spec::__type::__default:
		case __format_spec::__type::__string:
			return __formatter::__format_bool(__value, __ctx, __parser_.__get_parsed_std_specifications(__ctx));

		case __format_spec::__type::__binary_lower_case:
		case __format_spec::__type::__binary_upper_case:
		case __format_spec::__type::__octal:
		case __format_spec::__type::__decimal:
		case __format_spec::__type::__hexadecimal_lower_case:
		case __format_spec::__type::__hexadecimal_upper_case:
			// Promotes bool to an integral type. This reduces the number of
			// instantiations of __format_integer reducing code size.
			return __formatter::__format_integer(
				static_cast<unsigned>(__value), __ctx, __parser_.__get_parsed_std_specifications(__ctx));

		default:
			//_LIBCPP_ASSERT_INTERNAL(false, "The parse function should have validated the type");
			HAMON_UNREACHABLE();
		}
	}

	__format_spec::__parser<_CharT> __parser_;
};

HAMON_WARNING_POP()

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___FORMATTER_BOOL_HPP
