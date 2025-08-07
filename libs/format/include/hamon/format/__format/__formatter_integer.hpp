/**
 *	@file	__formatter_integer.hpp
 *
 *	@brief	__formatter_integer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___FORMATTER_INTEGER_HPP
#define HAMON_FORMAT___FORMAT___FORMATTER_INTEGER_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format_spec/__fields_integral.hpp>
#include <hamon/format/__format_spec/__process_parsed_integer.hpp>
#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__formatter/__format_char.hpp>
#include <hamon/format/__formatter/__format_integer.hpp>
#include <hamon/format/other/__make_32_64_or_128_bit_t.hpp>
#include <hamon/type_traits/is_void.hpp>

namespace hamon
{

namespace __format
{

template <__format::__fmt_char_type _CharT>
struct __formatter_integer
{
public:
	template <class _ParseContext>
	constexpr typename _ParseContext::iterator
	parse(_ParseContext& __ctx)
	{
		typename _ParseContext::iterator __result = __parser_.__parse(__ctx, __format_spec::__fields_integral);
		__format_spec::__process_parsed_integer(__parser_, "an integer");
		return __result;
	}

	template <integral _Tp, class _FormatContext>
	typename _FormatContext::iterator
	format(_Tp __value, _FormatContext& __ctx) const
	{
		__format_spec::__parsed_specifications<_CharT> __specs = __parser_.__get_parsed_std_specifications(__ctx);

		if (__specs.__std_.__type_ == __format_spec::__type::__char)
		{
			return __formatter::__format_char(__value, __ctx.out(), __specs);
		}

		using _Type = hamon::__make_32_64_or_128_bit_t<_Tp>;
		static_assert(!hamon::is_void<_Type>::value, "unsupported integral type used in __formatter_integer::__format");

		// Reduce the number of instantiation of the integer formatter
		return __formatter::__format_integer(static_cast<_Type>(__value), __ctx, __specs);
	}

	__format_spec::__parser<_CharT> __parser_;
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___FORMATTER_INTEGER_HPP
