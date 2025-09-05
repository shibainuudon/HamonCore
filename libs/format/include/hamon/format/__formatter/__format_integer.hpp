/**
 *	@file	__format_integer.hpp
 *
 *	@brief	__format_integer の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_INTEGER_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_INTEGER_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__alignment.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__formatter/__insert_sign.hpp>
#include <hamon/format/__formatter/__to_buffer.hpp>
#include <hamon/format/__formatter/__copy.hpp>
#include <hamon/format/__formatter/__write.hpp>
#include <hamon/format/__formatter/__write_transformed.hpp>
#include <hamon/format/__formatter/__buffer_size.hpp>
#include <hamon/format/__formatter/__write_using_decimal_separators.hpp>
#include <hamon/format/__formatter/__determine_grouping.hpp>
#include <hamon/format/other/__hex_to_upper.hpp>
#include <hamon/format/other/__to_unsigned_like.hpp>
#include <hamon/format/other/__complement.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/array.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/signed_integral.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/string.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <locale>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '' から '' への変換です。データが失われる可能性があります。
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_CLANG("-Wshorten-64-to-32")

template <hamon::unsigned_integral _Tp, hamon::contiguous_iterator _Iterator, class _CharT, class _FormatContext>
requires hamon::same_as<char, hamon::iter_value_t<_Iterator>>
typename _FormatContext::iterator __format_integer(
	_Tp __value,
	_FormatContext& __ctx,
	__format_spec::__parsed_specifications<_CharT> __specs,
	bool __negative,
	_Iterator __begin,
	_Iterator __end,
	const char* __prefix,
	int __base)
{
	_Iterator __first = __formatter::__insert_sign(__begin, __negative, __specs.__std_.__sign_);
	if (__specs.__std_.__alternate_form_ && __prefix)
	{
		while (*__prefix)
		{
			*__first++ = *__prefix++;
		}
	}

	_Iterator __last = __formatter::__to_buffer(__first, __end, __value, __base);

#  if 1//_LIBCPP_HAS_LOCALIZATION
	if (__specs.__std_.__locale_specific_form_)
	{
		auto loc = __ctx.locale();
		const auto& __np  = std::use_facet<std::numpunct<_CharT>>(loc);
//		hamon::string __grouping = __np.grouping();
		hamon::string __grouping = __np.grouping().c_str();
		ptrdiff_t __size  = __last - __first;
		// Writing the grouped form has more overhead than the normal output
		// routines. If there will be no separators written the locale-specific
		// form is identical to the normal routine. Test whether to grouped form
		// is required.
		if (!__grouping.empty() && __size > __grouping[0])
		{
			return __formatter::__write_using_decimal_separators(
				__ctx.out(),
				__begin,
				__first,
				__last,
				__formatter::__determine_grouping(__size, __grouping),
				__np.thousands_sep(),
				__specs);
		}
	}
#  endif
	auto __out_it = __ctx.out();
	if (__specs.__alignment_ != __format_spec::__alignment::__zero_padding)
	{
		__first = __begin;
	}
	else
	{
		// __buf contains [sign][prefix]data
		//                              ^ location of __first
		// The zero padding is done like:
		// - Write [sign][prefix]
		// - Write data right aligned with '0' as fill character.
		__out_it                  = __formatter::__copy(__begin, __first, hamon::move(__out_it));
		__specs.__alignment_      = __format_spec::__alignment::__right;
		__specs.__fill_.__data[0] = _CharT('0');
		int32_t __size            = __first - __begin;

		__specs.__width_ -= hamon::min(__size, __specs.__width_);
	}

	if (__specs.__std_.__type_ != __format_spec::__type::__hexadecimal_upper_case) [[likely]]
	{
		return __formatter::__write(__first, __last, __ctx.out(), __specs);
	}

	return __formatter::__write_transformed(__first, __last, __ctx.out(), __specs, hamon::__hex_to_upper);
}

HAMON_WARNING_POP()

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4715)	// 値を返さないコントロール パスがあります。
HAMON_WARNING_DISABLE_CLANG("-Wreturn-type")

template <hamon::unsigned_integral _Tp, class _CharT, class _FormatContext>
typename _FormatContext::iterator
__format_integer(_Tp __value,
				 _FormatContext& __ctx,
				 __format_spec::__parsed_specifications<_CharT> __specs,
				 bool __negative = false)
{
	switch (__specs.__std_.__type_)
	{
	case __format_spec::__type::__binary_lower_case:
		{
			hamon::array<char, __formatter::__buffer_size<decltype(__value), 2>()> __array;
			return __formatter::__format_integer(__value, __ctx, __specs, __negative, __array.begin(), __array.end(), "0b", 2);
		}
	case __format_spec::__type::__binary_upper_case:
		{
			hamon::array<char, __formatter::__buffer_size<decltype(__value), 2>()> __array;
			return __formatter::__format_integer(__value, __ctx, __specs, __negative, __array.begin(), __array.end(), "0B", 2);
		}
	case __format_spec::__type::__octal:
		{
			// Octal is special; if __value == 0 there's no prefix.
			hamon::array<char, __formatter::__buffer_size<decltype(__value), 8>()> __array;
			return __formatter::__format_integer(
				__value, __ctx, __specs, __negative, __array.begin(), __array.end(), __value != 0 ? "0" : nullptr, 8);
		}
	case __format_spec::__type::__default:
	case __format_spec::__type::__decimal:
		{
			hamon::array<char, __formatter::__buffer_size<decltype(__value), 10>()> __array;
			return __formatter::__format_integer(
				__value, __ctx, __specs, __negative, __array.begin(), __array.end(), nullptr, 10);
		}
	case __format_spec::__type::__hexadecimal_lower_case:
		{
			hamon::array<char, __formatter::__buffer_size<decltype(__value), 16>()> __array;
			return __formatter::__format_integer(__value, __ctx, __specs, __negative, __array.begin(), __array.end(), "0x", 16);
		}
	case __format_spec::__type::__hexadecimal_upper_case:
		{
			hamon::array<char, __formatter::__buffer_size<decltype(__value), 16>()> __array;
			return __formatter::__format_integer(__value, __ctx, __specs, __negative, __array.begin(), __array.end(), "0X", 16);
		}
	default:
		//_LIBCPP_ASSERT_INTERNAL(false, "The parse function should have validated the type");
		HAMON_UNREACHABLE();
	}
}

HAMON_WARNING_POP()


template <hamon::signed_integral _Tp, class _CharT, class _FormatContext>
typename _FormatContext::iterator
__format_integer(_Tp __value, _FormatContext& __ctx, __format_spec::__parsed_specifications<_CharT> __specs)
{
	// Depending on the std-format-spec string the sign and the value
	// might not be outputted together:
	// - alternate form may insert a prefix string.
	// - zero-padding may insert additional '0' characters.
	// Therefore the value is processed as a positive unsigned value.
	// The function @ref __insert_sign will a '-' when the value was negative.
	auto __r        = hamon::__to_unsigned_like(__value);
	bool __negative = __value < 0;
	if (__negative)
	{
		__r = hamon::__complement(__r);
	}

	return __formatter::__format_integer(__r, __ctx, __specs, __negative);
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_INTEGER_HPP
