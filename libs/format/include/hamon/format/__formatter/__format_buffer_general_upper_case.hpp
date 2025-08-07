/**
 *	@file	__format_buffer_general_upper_case.hpp
 *
 *	@brief	__format_buffer_general_upper_case の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_GENERAL_UPPER_CASE_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_GENERAL_UPPER_CASE_HPP

#include <hamon/format/__formatter/__float_result.hpp>
#include <hamon/format/__formatter/__float_buffer.hpp>
#include <hamon/format/__formatter/__format_buffer_general_lower_case.hpp>

namespace hamon
{

namespace __formatter
{

template <class _Fp, class _Tp>
__formatter::__float_result
__format_buffer_general_upper_case(__formatter::__float_buffer<_Fp>& __buffer, _Tp __value, int __precision, char* __integral)
{
	__formatter::__float_result __result = __formatter::__format_buffer_general_lower_case(__buffer, __value, __precision, __integral);
	if (__result.__exponent != __result.__last)
	{
		*__result.__exponent = 'E';
	}
	return __result;
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_GENERAL_UPPER_CASE_HPP
