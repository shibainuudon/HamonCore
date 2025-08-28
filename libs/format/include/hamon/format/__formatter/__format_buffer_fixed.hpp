/**
 *	@file	__format_buffer_fixed.hpp
 *
 *	@brief	__format_buffer_fixed の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_FIXED_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_FIXED_HPP

#include <hamon/format/__formatter/__float_result.hpp>
#include <hamon/format/__formatter/__float_buffer.hpp>
#include <hamon/format/__formatter/__to_buffer.hpp>

namespace hamon
{

namespace __formatter
{

template <class _Fp, class _Tp>
__formatter::__float_result
__format_buffer_fixed(const __formatter::__float_buffer<_Fp>& __buffer, _Tp __value, int __precision, char* __integral)
{
	__formatter::__float_result __result;
	__result.__integral = __integral;
	__result.__last     = __formatter::__to_buffer(__integral, __buffer.end(), __value, std::chars_format::fixed, __precision);

	// When there's no precision there's no radix point.
	// Else the radix point is placed at __precision + 1 from the end.
	// By converting __precision to a bool the subtraction can be done
	// unconditionally.
	__result.__radix_point = __result.__last - (__precision + bool(__precision));
	__result.__exponent    = __result.__last;

	//// clang-format off
	//_LIBCPP_ASSERT_INTERNAL((__result.__integral != __result.__last) &&
	//	(__result.__radix_point == __result.__last || *__result.__radix_point == '.') &&
	//	(__result.__exponent == __result.__last),
	//	"Post-condition failure.");
	//// clang-format on

	return __result;
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_FIXED_HPP
