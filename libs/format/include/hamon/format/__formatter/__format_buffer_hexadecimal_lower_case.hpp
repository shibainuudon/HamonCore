/**
 *	@file	__format_buffer_hexadecimal_lower_case.hpp
 *
 *	@brief	__format_buffer_hexadecimal_lower_case の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_HEXADECIMAL_LOWER_CASE_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_HEXADECIMAL_LOWER_CASE_HPP

#include <hamon/format/__formatter/__float_result.hpp>
#include <hamon/format/__formatter/__float_buffer.hpp>
#include <hamon/format/__formatter/__to_buffer.hpp>
#include <hamon/format/__formatter/__traits.hpp>
#include <hamon/algorithm/find.hpp>

namespace hamon
{

namespace __formatter
{

template <class _Fp, class _Tp>
__formatter::__float_result
__format_buffer_hexadecimal_lower_case(
	const __formatter::__float_buffer<_Fp>& __buffer, _Tp __value, int __precision, char* __integral)
{
	__formatter::__float_result __result;
	__result.__integral = __integral;
	if (__precision == -1)
	{
		__result.__last = __formatter::__to_buffer(__integral, __buffer.end(), __value, std::chars_format::hex);
	}
	else
	{
		__result.__last = __formatter::__to_buffer(__integral, __buffer.end(), __value, std::chars_format::hex, __precision);
	}

	// H = one or more hex-digits
	// S = sign
	// D = one or more decimal-digits
	// When the fractional part is zero and no precision the output is 0p+0
	// else the output is                                              0.HpSD
	// So testing the second position can differentiate between these two cases.
	char* __first = __integral + 1;
	if (*__first == '.')
	{
		__result.__radix_point = __first;
		// One digit is the minimum
		// 0.hpSd
		//       ^-- last
		//     ^---- integral = end of search
		// ^-------- start of search
		// 0123456
		//
		// Four digits is the maximum
		// 0.hpSdddd
		//          ^-- last
		//        ^---- integral = end of search
		//    ^-------- start of search
		// 0123456789
		static_assert(__formatter::__traits<_Fp>::__hex_precision_digits <= 4, "Guard against possible underflow.");

		char* __last        = __result.__last - 2;
		__first             = __last - __formatter::__traits<_Fp>::__hex_precision_digits;
		__result.__exponent = hamon::find(__first, __last, 'p');
	}
	else
	{
		__result.__radix_point = __result.__last;
		__result.__exponent    = __first;
	}

	//// clang-format off
	//_LIBCPP_ASSERT_INTERNAL((__result.__integral != __result.__last) &&
	//	(__result.__radix_point == __result.__last || *__result.__radix_point == '.') &&
	//	(__result.__exponent != __result.__last && *__result.__exponent == 'p'),
	//	"Post-condition failure.");
	//// clang-format on

	return __result;
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_HEXADECIMAL_LOWER_CASE_HPP
