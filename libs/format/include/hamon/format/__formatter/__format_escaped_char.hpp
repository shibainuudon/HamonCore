/**
 *	@file	__format_escaped_char.hpp
 *
 *	@brief	__format_escaped_char の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_ESCAPED_CHAR_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_ESCAPED_CHAR_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__formatter/__escape.hpp>
#include <hamon/format/__formatter/__write.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

template <class _CharT>
auto
__format_escaped_char(
	_CharT __value,
	hamon::output_iterator<const _CharT&> auto __out_it,
	__format_spec::__parsed_specifications<_CharT> __specs) -> decltype(__out_it)
{
	hamon::basic_string<_CharT> __str;
	__str += _CharT('\'');
	__formatter::__escape(__str, hamon::basic_string_view{hamon::addressof(__value), 1}, __formatter::__escape_quotation_mark::__apostrophe);
	__str += _CharT('\'');
	return __formatter::__write(__str.data(), __str.data() + __str.size(), hamon::move(__out_it), __specs, __str.size());
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_ESCAPED_CHAR_HPP
