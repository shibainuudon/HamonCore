/**
 *	@file	__format_buffer_default.hpp
 *
 *	@brief	__format_buffer_default の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_DEFAULT_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_DEFAULT_HPP

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
__format_buffer_default(const __formatter::__float_buffer<_Fp>& __buffer, _Tp __value, char* __integral)
{
	__formatter::__float_result __result;
	__result.__integral = __integral;
	__result.__last     = __formatter::__to_buffer(__integral, __buffer.end(), __value);

	__result.__exponent = __formatter::__find_exponent(__result.__integral, __result.__last);

	// Constrains:
	// - There's at least one decimal digit before the radix point.
	// - The radix point, when present, is placed before the exponent.
	__result.__radix_point = hamon::find(__result.__integral + 1, __result.__exponent, '.');

	// When the radix point isn't found its position is the exponent instead of
	// __result.__last.
	if (__result.__radix_point == __result.__exponent)
	{
		__result.__radix_point = __result.__last;
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

#endif // HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_DEFAULT_HPP
