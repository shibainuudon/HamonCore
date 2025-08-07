/**
 *	@file	__format_buffer.hpp
 *
 *	@brief	__format_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_HPP

#include <hamon/format/__formatter/__float_result.hpp>
#include <hamon/format/__formatter/__float_buffer.hpp>
#include <hamon/format/__formatter/__insert_sign.hpp>
#include <hamon/format/__formatter/__format_buffer_general_lower_case.hpp>
#include <hamon/format/__formatter/__format_buffer_general_upper_case.hpp>
#include <hamon/format/__formatter/__format_buffer_default.hpp>
#include <hamon/format/__formatter/__format_buffer_hexadecimal_lower_case.hpp>
#include <hamon/format/__formatter/__format_buffer_hexadecimal_upper_case.hpp>
#include <hamon/format/__formatter/__format_buffer_scientific_lower_case.hpp>
#include <hamon/format/__formatter/__format_buffer_scientific_upper_case.hpp>
#include <hamon/format/__formatter/__format_buffer_fixed.hpp>
#include <hamon/format/__format_spec/__sign.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4715)	// 値を返さないコントロール パスがあります。
HAMON_WARNING_DISABLE_CLANG("-Wreturn-type")

/// Fills the buffer with the data based on the requested formatting.
///
/// This function, when needed, turns the characters to upper case and
/// determines the "interesting" locations which are returned to the caller.
///
/// This means the caller never has to convert the contents of the buffer to
/// upper case or search for radix points and the location of the exponent.
/// This gives a bit of overhead. The original code didn't do that, but due
/// to the number of possible additional work needed to turn this number to
/// the proper output the code was littered with tests for upper cases and
/// searches for radix points and exponents.
/// - When a precision larger than the type's precision is selected
///   additional zero characters need to be written before the exponent.
/// - alternate form needs to add a radix point when not present.
/// - localization needs to do grouping in the integral part.
template <class _Fp, class _Tp>
// TODO FMT _Fp should just be _Tp when to_chars has proper long double support.
__formatter::__float_result __format_buffer(
	__formatter::__float_buffer<_Fp>& __buffer,
	_Tp __value,
	bool __negative,
	bool __has_precision,
	__format_spec::__sign __sign,
	__format_spec::__type __type)
{
	char* __first = __formatter::__insert_sign(__buffer.begin(), __negative, __sign);
	switch (__type)
	{
	case __format_spec::__type::__default:
		if (__has_precision)
		{
			return __formatter::__format_buffer_general_lower_case(__buffer, __value, __buffer.__precision(), __first);
		}
		else
		{
			return __formatter::__format_buffer_default(__buffer, __value, __first);
		}

	case __format_spec::__type::__hexfloat_lower_case:
		return __formatter::__format_buffer_hexadecimal_lower_case(__buffer, __value, __has_precision ? __buffer.__precision() : -1, __first);

	case __format_spec::__type::__hexfloat_upper_case:
		return __formatter::__format_buffer_hexadecimal_upper_case(__buffer, __value, __has_precision ? __buffer.__precision() : -1, __first);

	case __format_spec::__type::__scientific_lower_case:
		return __formatter::__format_buffer_scientific_lower_case(__buffer, __value, __buffer.__precision(), __first);

	case __format_spec::__type::__scientific_upper_case:
		return __formatter::__format_buffer_scientific_upper_case(__buffer, __value, __buffer.__precision(), __first);

	case __format_spec::__type::__fixed_lower_case:
	case __format_spec::__type::__fixed_upper_case:
		return __formatter::__format_buffer_fixed(__buffer, __value, __buffer.__precision(), __first);

	case __format_spec::__type::__general_lower_case:
		return __formatter::__format_buffer_general_lower_case(__buffer, __value, __buffer.__precision(), __first);

	case __format_spec::__type::__general_upper_case:
		return __formatter::__format_buffer_general_upper_case(__buffer, __value, __buffer.__precision(), __first);

	default:
		//_LIBCPP_ASSERT_INTERNAL(false, "The parser should have validated the type");
		HAMON_UNREACHABLE();
	}
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_BUFFER_HPP
