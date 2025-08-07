/**
 *	@file	__formatter_pointer.hpp
 *
 *	@brief	__formatter_pointer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___FORMATTER_POINTER_HPP
#define HAMON_FORMAT___FORMAT___FORMATTER_POINTER_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format_spec/__fields_pointer.hpp>
#include <hamon/format/__format_spec/__process_display_type_pointer.hpp>
#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__parser.hpp>
#include <hamon/format/__formatter/__format_integer.hpp>

namespace hamon
{

namespace __format
{

template <__format::__fmt_char_type _CharT>
struct __formatter_pointer
{
public:
	template <class _ParseContext>
	constexpr typename _ParseContext::iterator
	parse(_ParseContext& __ctx)
	{
		typename _ParseContext::iterator __result = __parser_.__parse(__ctx, __format_spec::__fields_pointer);
		__format_spec::__process_display_type_pointer(__parser_.__type_, "a pointer");
		return __result;
	}

	template <class _FormatContext>
	typename _FormatContext::iterator
	format(const void* __ptr, _FormatContext& __ctx) const
	{
		__format_spec::__parsed_specifications<_CharT> __specs = __parser_.__get_parsed_std_specifications(__ctx);
		__specs.__std_.__alternate_form_                       = true;
		__specs.__std_.__type_ =
			__specs.__std_.__type_ == __format_spec::__type::__pointer_upper_case
			? __format_spec::__type::__hexadecimal_upper_case
			: __format_spec::__type::__hexadecimal_lower_case;

		return __formatter::__format_integer(reinterpret_cast<uintptr_t>(__ptr), __ctx, __specs);
	}

	__format_spec::__parser<_CharT> __parser_;
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___FORMATTER_POINTER_HPP
