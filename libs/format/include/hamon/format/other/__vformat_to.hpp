/**
 *	@file	__vformat_to.hpp
 *
 *	@brief	__vformat_to の定義
 */

#ifndef HAMON_FORMAT_OTHER___VFORMAT_TO_HPP
#define HAMON_FORMAT_OTHER___VFORMAT_TO_HPP

#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/format/__format/__vformat_to.hpp>
#include <hamon/format/__format/__buffer_selector.hpp>
#include <hamon/format/other/__format_context_create.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>
#include <locale>

namespace hamon
{

template <class _OutIt, class _CharT, class _FormatOutIt>
	requires(hamon::output_iterator<_OutIt, const _CharT&>)
_OutIt __vformat_to(
	_OutIt __out_it,
	hamon::basic_string_view<_CharT> __fmt,
	hamon::basic_format_args<hamon::basic_format_context<_FormatOutIt, _CharT>> __args)
{
	if constexpr (hamon::same_as<_OutIt, _FormatOutIt>)
	{
		return hamon::__format::__vformat_to(
			hamon::basic_format_parse_context{__fmt, __args.__size()},
			hamon::__format_context_create(hamon::move(__out_it), __args));
	}
	else
	{
		typename __format::__buffer_selector<_OutIt, _CharT>::type __buffer {hamon::move(__out_it)};
		hamon::__format::__vformat_to(
			hamon::basic_format_parse_context{__fmt, __args.__size()},
			hamon::__format_context_create(__buffer.__make_output_iterator(), __args));
		return hamon::move(__buffer).__out_it();
	}
}

template <class _OutIt, class _CharT, class _FormatOutIt>
	requires(hamon::output_iterator<_OutIt, const _CharT&>)
_OutIt __vformat_to(
	_OutIt __out_it,
	std::locale const& __loc,
	hamon::basic_string_view<_CharT> __fmt,
	hamon::basic_format_args<hamon::basic_format_context<_FormatOutIt, _CharT>> __args)
{
	if constexpr (hamon::same_as<_OutIt, _FormatOutIt>)
	{
		return hamon::__format::__vformat_to(
			hamon::basic_format_parse_context{__fmt, __args.__size()},
			hamon::__format_context_create(hamon::move(__out_it), __args, __loc));
	}
	else
	{
		typename __format::__buffer_selector<_OutIt, _CharT>::type __buffer {hamon::move(__out_it)};
		hamon::__format::__vformat_to(
			hamon::basic_format_parse_context{__fmt, __args.__size()},
			hamon::__format_context_create(__buffer.__make_output_iterator(), __args, __loc));
		return hamon::move(__buffer).__out_it();
	}
}

}	// namespace hamon

#endif // HAMON_FORMAT_OTHER___VFORMAT_TO_HPP
