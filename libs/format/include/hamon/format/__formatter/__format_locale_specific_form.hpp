/**
 *	@file	__format_locale_specific_form.hpp
 *
 *	@brief	__format_locale_specific_form の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_LOCALE_SPECIFIC_FORM_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_LOCALE_SPECIFIC_FORM_HPP

#include <hamon/format/__formatter/__float_buffer.hpp>
#include <hamon/format/__formatter/__float_result.hpp>
#include <hamon/format/__formatter/__determine_grouping.hpp>
#include <hamon/format/__formatter/__padding_size.hpp>
#include <hamon/format/__formatter/__fill.hpp>
#include <hamon/format/__formatter/__copy.hpp>
#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__alignment.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/string.hpp>
#include <hamon/utility/move.hpp>
#include <locale>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

#  if 1//_LIBCPP_HAS_LOCALIZATION
template <class _OutIt, class _Fp, class _CharT>
_OutIt __format_locale_specific_form(
	_OutIt __out_it,
	const __formatter::__float_buffer<_Fp>& __buffer,
	const __formatter::__float_result& __result,
	std::locale __loc,
	__format_spec::__parsed_specifications<_CharT> __specs)
{
	const auto& __np  = std::use_facet<std::numpunct<_CharT>>(__loc);
//	hamon::string __grouping = __np.grouping();
	hamon::string __grouping = __np.grouping().c_str();
	char* __first     = __result.__integral;
	// When no radix point or exponent are present __last will be __result.__last.
	char* __last = hamon::min(__result.__radix_point, __result.__exponent);

	ptrdiff_t __digits = __last - __first;
	if (!__grouping.empty())
	{
		if (__digits <= __grouping[0])
		{
			__grouping.clear();
		}
		else
		{
			__grouping = __formatter::__determine_grouping(__digits, __grouping);
		}
	}

	ptrdiff_t __size =
		__result.__last - __buffer.begin() + // Formatted string
		__buffer.__num_trailing_zeros() +    // Not yet rendered zeros
		__grouping.size() -                  // Grouping contains one
		!__grouping.empty();                 // additional character

	__formatter::__padding_size_result __padding = {0, 0};
	bool __zero_padding                          = __specs.__alignment_ == __format_spec::__alignment::__zero_padding;
	if (__size < __specs.__width_)
	{
		if (__zero_padding)
		{
			__specs.__alignment_      = __format_spec::__alignment::__right;
			__specs.__fill_.__data[0] = _CharT('0');
		}

		__padding = __formatter::__padding_size(__size, __specs.__width_, __specs.__alignment_);
	}

	// sign and (zero padding or alignment)
	if (__zero_padding && __first != __buffer.begin())
	{
		*__out_it++ = *__buffer.begin();
	}
	__out_it = __formatter::__fill(hamon::move(__out_it), __padding.__before_, __specs.__fill_);
	if (!__zero_padding && __first != __buffer.begin())
	{
		*__out_it++ = *__buffer.begin();
	}

	// integral part
	if (__grouping.empty())
	{
		__out_it = __formatter::__copy(__first, __digits, hamon::move(__out_it));
	}
	else
	{
		auto __r     = __grouping.rbegin();
		auto __e     = __grouping.rend() - 1;
		_CharT __sep = __np.thousands_sep();
		// The output is divided in small groups of numbers to write:
		// - A group before the first separator.
		// - A separator and a group, repeated for the number of separators.
		// - A group after the last separator.
		// This loop achieves that process by testing the termination condition
		// midway in the loop.
		while (true)
		{
			__out_it = __formatter::__copy(__first, *__r, hamon::move(__out_it));
			__first += *__r;

			if (__r == __e)
			{
				break;
			}

			++__r;
			*__out_it++ = __sep;
		}
	}

	// fractional part
	if (__result.__radix_point != __result.__last)
	{
		*__out_it++ = __np.decimal_point();
		__out_it    = __formatter::__copy(__result.__radix_point + 1, __result.__exponent, hamon::move(__out_it));
		__out_it    = __formatter::__fill(hamon::move(__out_it), __buffer.__num_trailing_zeros(), _CharT('0'));
	}

	// exponent
	if (__result.__exponent != __result.__last)
	{
		__out_it = __formatter::__copy(__result.__exponent, __result.__last, hamon::move(__out_it));
	}

	// alignment
	return __formatter::__fill(hamon::move(__out_it), __padding.__after_, __specs.__fill_);
}
#  endif // _LIBCPP_HAS_LOCALIZATION

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_LOCALE_SPECIFIC_FORM_HPP
