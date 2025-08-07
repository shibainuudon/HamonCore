/**
 *	@file	__format_escaped_string.hpp
 *
 *	@brief	__format_escaped_string の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_ESCAPED_STRING_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_ESCAPED_STRING_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__formatter/__escape.hpp>
#include <hamon/format/__formatter/__escape_quotation_mark.hpp>
#include <hamon/format/__formatter/__write_string.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

template <class _CharT>
auto
__format_escaped_string(hamon::basic_string_view<_CharT> __values,
						hamon::output_iterator<const _CharT&> auto __out_it,
						__format_spec::__parsed_specifications<_CharT> __specs) -> decltype(__out_it)
{
	hamon::basic_string<_CharT> __str;
	__str += _CharT('"');
	__formatter::__escape(__str, __values, __formatter::__escape_quotation_mark::__double_quote);
	__str += _CharT('"');
	return __formatter::__write_string(hamon::basic_string_view{__str}, hamon::move(__out_it), __specs);
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_ESCAPED_STRING_HPP
