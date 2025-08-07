/**
 *	@file	__vformatted_size.hpp
 *
 *	@brief	__vformatted_size の定義
 */

#ifndef HAMON_FORMAT_OTHER___VFORMATTED_SIZE_HPP
#define HAMON_FORMAT_OTHER___VFORMATTED_SIZE_HPP

#include <hamon/format/__format/__formatted_size_buffer.hpp>
#include <hamon/format/__format/__vformat_to.hpp>
#include <hamon/format/other/__format_context_create.hpp>
#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>
#include <locale>

namespace hamon
{

template <class _CharT>
hamon::size_t __vformatted_size(hamon::basic_string_view<_CharT> __fmt, auto __args)
{
	__format::__formatted_size_buffer<_CharT> __buffer;
	__format::__vformat_to(
		hamon::basic_format_parse_context{ __fmt, __args.__size() },
		hamon::__format_context_create(__buffer.__make_output_iterator(), __args));
	return hamon::move(__buffer).__result();
}

template <class _CharT>
hamon::size_t __vformatted_size(std::locale const& __loc, hamon::basic_string_view<_CharT> __fmt, auto __args)
{
	__format::__formatted_size_buffer<_CharT> __buffer;
	__format::__vformat_to(
		hamon::basic_format_parse_context{ __fmt, __args.__size() },
		hamon::__format_context_create(__buffer.__make_output_iterator(), __args, __loc));
	return hamon::move(__buffer).__result();
}

}	// namespace hamon

#endif // HAMON_FORMAT_OTHER___VFORMATTED_SIZE_HPP
