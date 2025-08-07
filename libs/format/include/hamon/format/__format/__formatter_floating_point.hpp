/**
 *	@file	__formatter_floating_point.hpp
 *
 *	@brief	__formatter_floating_point の定義
 */

#ifndef HAMON_FORMAT___FORMAT___FORMATTER_FLOATING_POINT_HPP
#define HAMON_FORMAT___FORMAT___FORMATTER_FLOATING_POINT_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format_spec/__fields_floating_point.hpp>
#include <hamon/format/__format_spec/__process_parsed_floating_point.hpp>
#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__formatter/__format_floating_point.hpp>
#include <hamon/concepts/floating_point.hpp>

namespace hamon
{

namespace __format
{

template <__format::__fmt_char_type _CharT>
struct __formatter_floating_point
{
public:
	template <class _ParseContext>
	constexpr typename _ParseContext::iterator
	parse(_ParseContext& __ctx)
	{
		typename _ParseContext::iterator __result = __parser_.__parse(__ctx, __format_spec::__fields_floating_point);
		__format_spec::__process_parsed_floating_point(__parser_, "a floating-point");
		return __result;
	}

	template <hamon::floating_point _Tp, class _FormatContext>
	typename _FormatContext::iterator
	format(_Tp __value, _FormatContext& __ctx) const
	{
		return __formatter::__format_floating_point(__value, __ctx, __parser_.__get_parsed_std_specifications(__ctx));
	}

	__format_spec::__parser<_CharT> __parser_;
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___FORMATTER_FLOATING_POINT_HPP
