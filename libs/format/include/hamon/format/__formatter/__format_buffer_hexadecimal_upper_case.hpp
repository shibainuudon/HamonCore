/**
 *	@file	__format_buffer_hexadecimal_upper_case.hpp
 *
 *	@brief	__format_buffer_hexadecimal_upper_case の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_HEXADECIMAL_UPPER_CASE_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_HEXADECIMAL_UPPER_CASE_HPP

#include <hamon/format/__formatter/__float_result.hpp>
#include <hamon/format/__formatter/__float_buffer.hpp>
#include <hamon/format/__formatter/__format_buffer_hexadecimal_lower_case.hpp>
#include <hamon/format/other/__hex_to_upper.hpp>
#include <hamon/algorithm/transform.hpp>

namespace hamon
{

namespace __formatter
{

template <class _Fp, class _Tp>
__formatter::__float_result
__format_buffer_hexadecimal_upper_case(
	const __formatter::__float_buffer<_Fp>& __buffer, _Tp __value, int __precision, char* __integral)
{
	__formatter::__float_result __result =
		__formatter::__format_buffer_hexadecimal_lower_case(__buffer, __value, __precision, __integral);
	hamon::transform(__result.__integral, __result.__exponent, __result.__integral, hamon::__hex_to_upper);
	*__result.__exponent = 'P';
	return __result;
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_HEXADECIMAL_UPPER_CASE_HPP
