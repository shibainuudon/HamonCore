/**
 *	@file	__escape.hpp
 *
 *	@brief	__escape の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___ESCAPE_HPP
#define HAMON_FORMAT___FORMATTER___ESCAPE_HPP

#include <hamon/format/__formatter/__escape_quotation_mark.hpp>
#include <hamon/format/__formatter/__is_escaped_sequence_written.hpp>
#include <hamon/format/__formatter/__write_escape_ill_formed_code_unit.hpp>
#include <hamon/format/__formatter/__to_char32.hpp>
#include <hamon/format/other/__unicode.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/algorithm/ranges/for_each.hpp>
#include <hamon/iterator/back_insert_iterator.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>

namespace hamon
{

namespace __formatter
{

template <class _CharT>
void
__escape(hamon::basic_string<_CharT>& __str, hamon::basic_string_view<_CharT> __values, __formatter::__escape_quotation_mark __mark)
{
	__unicode::__code_point_view<_CharT> __view {__values.begin(), __values.end()};

	// When the first code unit has the property Grapheme_Extend=Yes it needs to
	// be escaped. This happens when the previous code unit was also escaped.
	bool __escape = true;
	while (!__view.__at_end())
	{
		auto __first                                  = __view.__position();
		typename __unicode::__consume_result __result = __view.__consume();
		if (__result.__status == __unicode::__consume_result::__ok)
		{
			__escape = __formatter::__is_escaped_sequence_written(__str, __result.__code_point, __escape, __mark);
			if (!__escape)
			{
				// 2.2.1.3 - Add the character
				ranges::copy(__first, __view.__position(), hamon::back_insert_iterator(__str));
			}
		}
		else
		{
			// 2.2.3 sequence of ill-formed code units
			ranges::for_each(__first, __view.__position(), [&](_CharT __value) {
				__formatter::__write_escape_ill_formed_code_unit(__str, __formatter::__to_char32(__value));
			});
		}
	}
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___ESCAPE_HPP
