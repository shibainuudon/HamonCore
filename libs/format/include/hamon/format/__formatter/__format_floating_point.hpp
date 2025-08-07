/**
 *	@file	__format_floating_point.hpp
 *
 *	@brief	__format_floating_point の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_FLOATING_POINT_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_FLOATING_POINT_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__alignment.hpp>
#include <hamon/format/__formatter/__format_floating_point_non_finite.hpp>
#include <hamon/format/__formatter/__format_buffer.hpp>
#include <hamon/format/__formatter/__copy.hpp>
#include <hamon/format/__formatter/__fill.hpp>
#include <hamon/format/__formatter/__write_using_trailing_zeros.hpp>
#include <hamon/format/__formatter/__write.hpp>
#include <hamon/format/__formatter/__format_locale_specific_form.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/algorithm/rotate.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '' から '' への変換です。データが失われる可能性があります。
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wshorten-64-to-32")

template <hamon::floating_point _Tp, class _CharT, class _FormatContext>
typename _FormatContext::iterator
__format_floating_point(_Tp __value, _FormatContext& __ctx, __format_spec::__parsed_specifications<_CharT> __specs)
{
	bool __negative = std::signbit(__value);

	if (!std::isfinite(__value)) [[unlikely]]
	{
		return __formatter::__format_floating_point_non_finite(__ctx.out(), __specs, __negative, std::isnan(__value));
	}

	// Depending on the std-format-spec string the sign and the value
	// might not be outputted together:
	// - zero-padding may insert additional '0' characters.
	// Therefore the value is processed as a non negative value.
	// The function @ref __insert_sign will insert a '-' when the value was
	// negative.

	if (__negative)
	{
		__value = -__value;
	}

	// TODO FMT _Fp should just be _Tp when to_chars has proper long double support.
	using _Fp = hamon::conditional_t<hamon::same_as<_Tp, long double>, double, _Tp>;
	// Force the type of the precision to avoid -1 to become an unsigned value.
	__float_buffer<_Fp> __buffer(__specs.__precision_);
	__float_result __result = __formatter::__format_buffer(
		__buffer, __value, __negative, (__specs.__has_precision()), __specs.__std_.__sign_, __specs.__std_.__type_);

	if (__specs.__std_.__alternate_form_)
	{
		if (__result.__radix_point == __result.__last)
		{
			*__result.__last++ = '.';

			// When there is an exponent the point needs to be moved before the
			// exponent. When there's no exponent the rotate does nothing. Since
			// rotate tests whether the operation is a nop, call it unconditionally.
			hamon::rotate(__result.__exponent, __result.__last - 1, __result.__last);
			__result.__radix_point = __result.__exponent;

			// The radix point is always placed before the exponent.
			// - No exponent needs to point to the new last.
			// - An exponent needs to move one position to the right.
			// So it's safe to increment the value unconditionally.
			++__result.__exponent;
		}

		// [format.string.std]/6
		//   In addition, for g and G conversions, trailing zeros are not removed
		//   from the result.
		//
		// If the type option for a floating-point type is none it may use the
		// general formatting, but it's not a g or G conversion. So in that case
		// the formatting should not append trailing zeros.
		bool __is_general = __specs.__std_.__type_ == __format_spec::__type::__general_lower_case ||
			__specs.__std_.__type_ == __format_spec::__type::__general_upper_case;

		if (__is_general)
		{
			// https://en.cppreference.com/w/c/io/fprintf
			// Let P equal the precision if nonzero, 6 if the precision is not
			// specified, or 1 if the precision is 0. Then, if a conversion with
			// style E would have an exponent of X:
			int __p = hamon::max<int>(1, (__specs.__has_precision() ? __specs.__precision_ : 6));
			if (__result.__exponent == __result.__last)
			{
				// if P > X >= -4, the conversion is with style f or F and precision P - 1 - X.
				// By including the radix point it calculates P - (1 + X)
				__p -= __result.__radix_point - __result.__integral;
			}
			else
			{
				// otherwise, the conversion is with style e or E and precision P - 1.
				--__p;
			}

			ptrdiff_t __precision = (__result.__exponent - __result.__radix_point) - 1;
			if (__precision < __p)
			{
				__buffer.__add_trailing_zeros(__p - __precision);
			}
		}
	}

#  if 1//_LIBCPP_HAS_LOCALIZATION
	if (__specs.__std_.__locale_specific_form_)
	{
		return __formatter::__format_locale_specific_form(__ctx.out(), __buffer, __result, __ctx.locale(), __specs);
	}
#  endif

	ptrdiff_t __size         = __result.__last - __buffer.begin();
	int __num_trailing_zeros = __buffer.__num_trailing_zeros();
	if (__size + __num_trailing_zeros >= __specs.__width_)
	{
		if (__num_trailing_zeros && __result.__exponent != __result.__last)
		{
			// Insert trailing zeros before exponent character.
			return __formatter::__copy(
				__result.__exponent,
				__result.__last,
				__formatter::__fill(__formatter::__copy(__buffer.begin(), __result.__exponent, __ctx.out()),
					__num_trailing_zeros,
					_CharT('0')));
		}

		return __formatter::__fill(
			__formatter::__copy(__buffer.begin(), __result.__last, __ctx.out()), __num_trailing_zeros, _CharT('0'));
	}

	auto __out_it = __ctx.out();
	char* __first = __buffer.begin();
	if (__specs.__alignment_ == __format_spec::__alignment::__zero_padding)
	{
		// When there is a sign output it before the padding. Note the __size
		// doesn't need any adjustment, regardless whether the sign is written
		// here or in __formatter::__write.
		if (__first != __result.__integral)
		{
			*__out_it++ = *__first++;
		}

		// After the sign is written, zero padding is the same a right alignment
		// with '0'.
		__specs.__alignment_      = __format_spec::__alignment::__right;
		__specs.__fill_.__data[0] = _CharT('0');
	}

	if (__num_trailing_zeros)
	{
		return __formatter::__write_using_trailing_zeros(
			__first, __result.__last, hamon::move(__out_it), __specs, __size, __result.__exponent, __num_trailing_zeros);
	}

	return __formatter::__write(__first, __result.__last, hamon::move(__out_it), __specs, __size);
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_FLOATING_POINT_HPP
