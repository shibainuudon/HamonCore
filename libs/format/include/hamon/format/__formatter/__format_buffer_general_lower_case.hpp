/**
 *	@file	__format_buffer_general_lower_case.hpp
 *
 *	@brief	__format_buffer_general_lower_case の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_GENERAL_LOWER_CASE_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_GENERAL_LOWER_CASE_HPP

#include <hamon/format/__formatter/__float_result.hpp>
#include <hamon/format/__formatter/__float_buffer.hpp>
#include <hamon/format/__formatter/__to_buffer.hpp>
#include <hamon/format/__formatter/__find_exponent.hpp>
#include <hamon/algorithm/find.hpp>

namespace hamon
{

namespace __formatter
{

template <class _Fp, class _Tp>
__formatter::__float_result
__format_buffer_general_lower_case(__formatter::__float_buffer<_Fp>& __buffer, _Tp __value, int __precision, char* __integral)
{
	__buffer.__remove_trailing_zeros();

	__formatter::__float_result __result;
	__result.__integral = __integral;
	__result.__last = __formatter::__to_buffer(__integral, __buffer.end(), __value, std::chars_format::general, __precision);

	char* __first = __integral + 1;
	if (__first == __result.__last)
	{
		__result.__radix_point = __result.__last;
		__result.__exponent    = __result.__last;
	}
	else
	{
		__result.__exponent = __formatter::__find_exponent(__first, __result.__last);
		if (__result.__exponent != __result.__last)
		{
			// In scientific mode if there's a radix point it will always be after
			// the first digit. (This is the position __first points at).
			__result.__radix_point = *__first == '.' ? __first : __result.__last;
		}
		else
		{
			// In fixed mode the algorithm truncates trailing spaces and possibly the
			// radix point. There's no good guess for the position of the radix point
			// therefore scan the output after the first digit.
			__result.__radix_point = hamon::find(__first, __result.__last, '.');
		}
	}

	//// clang-format off
	//_LIBCPP_ASSERT_INTERNAL((__result.__integral != __result.__last) &&
	//	(__result.__radix_point == __result.__last || *__result.__radix_point == '.') &&
	//	(__result.__exponent == __result.__last || *__result.__exponent == 'e'),
	//	"Post-condition failure.");
	//// clang-format on

	return __result;
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_GENERAL_LOWER_CASE_HPP
