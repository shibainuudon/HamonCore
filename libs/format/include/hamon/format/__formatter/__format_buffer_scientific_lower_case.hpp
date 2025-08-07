/**
 *	@file	__format_buffer_scientific_lower_case.hpp
 *
 *	@brief	__format_buffer_scientific_lower_case の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_SCIENTIFIC_LOWER_CASE_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_SCIENTIFIC_LOWER_CASE_HPP

#include <hamon/format/__formatter/__float_result.hpp>
#include <hamon/format/__formatter/__float_buffer.hpp>
#include <hamon/format/__formatter/__to_buffer.hpp>
#include <hamon/format/__formatter/__find_exponent.hpp>

namespace hamon
{

namespace __formatter
{

template <class _Fp, class _Tp>
__formatter::__float_result
__format_buffer_scientific_lower_case(
	const __formatter::__float_buffer<_Fp>& __buffer, _Tp __value, int __precision, char* __integral)
{
	__formatter::__float_result __result;
	__result.__integral = __integral;
	__result.__last =
		__formatter::__to_buffer(__integral, __buffer.end(), __value, std::chars_format::scientific, __precision);

	char* __first = __integral + 1;
	//_LIBCPP_ASSERT_INTERNAL(__first != __result.__last, "No exponent present");
	if (*__first == '.')
	{
		__result.__radix_point = __first;
		__result.__exponent    = __formatter::__find_exponent(__first + 1, __result.__last);
	}
	else
	{
		__result.__radix_point = __result.__last;
		__result.__exponent    = __first;
	}

	//// clang-format off
	//_LIBCPP_ASSERT_INTERNAL((__result.__integral != __result.__last) &&
	//	(__result.__radix_point == __result.__last || *__result.__radix_point == '.') &&
	//	(__result.__exponent != __result.__last && *__result.__exponent == 'e'),
	//	"Post-condition failure.");
	//// clang-format on

	return __result;
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_SCIENTIFIC_LOWER_CASE_HPP
