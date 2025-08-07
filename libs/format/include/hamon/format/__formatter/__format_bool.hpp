/**
 *	@file	__format_bool.hpp
 *
 *	@brief	__format_bool の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_BOOL_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_BOOL_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__formatter/__write.hpp>
#include <hamon/format/__formatter/__write_string_no_precision.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>

namespace hamon
{

namespace __formatter
{

template <class _CharT>
struct __bool_strings;

template <>
struct __bool_strings<char>
{
	static constexpr hamon::string_view __true {"true"};
	static constexpr hamon::string_view __false {"false"};
};

template <>
struct __bool_strings<wchar_t> {
	static constexpr hamon::wstring_view __true {L"true"};
	static constexpr hamon::wstring_view __false {L"false"};
};

template <class _CharT, class _FormatContext>
typename _FormatContext::iterator
__format_bool(bool __value, _FormatContext& __ctx, __format_spec::__parsed_specifications<_CharT> __specs)
{
#  if 1//_LIBCPP_HAS_LOCALIZATION
	if (__specs.__std_.__locale_specific_form_)
	{
		auto loc = __ctx.locale();
		const auto& __np = std::use_facet<std::numpunct<_CharT>>(loc);
		//hamon::basic_string<_CharT> __str = __value ? __np.truename() : __np.falsename();
		hamon::basic_string<_CharT> __str = __value ? __np.truename().c_str() : __np.falsename().c_str();
		return __formatter::__write_string_no_precision(hamon::basic_string_view<_CharT>{__str}, __ctx.out(), __specs);
	}
#  endif
	hamon::basic_string_view<_CharT> __str =
		__value ? __formatter::__bool_strings<_CharT>::__true : __formatter::__bool_strings<_CharT>::__false;
	return __formatter::__write(__str.begin(), __str.end(), __ctx.out(), __specs);
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_BOOL_HPP
