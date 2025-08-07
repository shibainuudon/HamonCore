/**
 *	@file	__vformat_to_n.hpp
 *
 *	@brief	__vformat_to_n の定義
 */

#ifndef HAMON_FORMAT_OTHER___VFORMAT_TO_N_HPP
#define HAMON_FORMAT_OTHER___VFORMAT_TO_N_HPP

#include <hamon/format/format_to_n_result.hpp>
#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/format/__format/__format_to_n_buffer.hpp>
#include <hamon/format/__format/__vformat_to.hpp>
#include <hamon/format/other/__format_context_create.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>
#include <locale>

namespace hamon
{

template <class _Context, class _OutIt, class _CharT>
hamon::format_to_n_result<_OutIt>
__vformat_to_n(
	_OutIt __out_it,
	hamon::iter_difference_t<_OutIt> __n,
	hamon::basic_string_view<_CharT> __fmt,
	hamon::basic_format_args<_Context> __args)
{
	__format::__format_to_n_buffer<_OutIt, _CharT> __buffer{hamon::move(__out_it), __n};
	__format::__vformat_to(
		hamon::basic_format_parse_context{__fmt, __args.__size()},
		hamon::__format_context_create(__buffer.__make_output_iterator(), __args));
	return hamon::move(__buffer).__result();
}

template <class _Context, class _OutIt, class _CharT>
hamon::format_to_n_result<_OutIt>
__vformat_to_n(
	_OutIt __out_it,
	hamon::iter_difference_t<_OutIt> __n,
	std::locale const& __loc,
	hamon::basic_string_view<_CharT> __fmt,
	hamon::basic_format_args<_Context> __args)
{
	__format::__format_to_n_buffer<_OutIt, _CharT> __buffer{hamon::move(__out_it), __n};
	__format::__vformat_to(
		hamon::basic_format_parse_context{__fmt, __args.__size()},
		hamon::__format_context_create(__buffer.__make_output_iterator(), __args, __loc));
	return hamon::move(__buffer).__result();
}

}	// namespace hamon

#endif // HAMON_FORMAT_OTHER___VFORMAT_TO_N_HPP
