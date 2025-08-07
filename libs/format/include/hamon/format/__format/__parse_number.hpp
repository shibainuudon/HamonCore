/**
 *	@file	__parse_number.hpp
 *
 *	@brief	__parse_number の定義
 */

#ifndef HAMON_FORMAT___FORMAT___PARSE_NUMBER_HPP
#define HAMON_FORMAT___FORMAT___PARSE_NUMBER_HPP

#include <hamon/format/__format/__parse_number_result.hpp>
#include <hamon/format/__format/__number_max.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>

namespace hamon
{

namespace __format
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

/**
 * Parses a number.
 *
 * The number is used for the 31-bit values @em width and @em precision. This
 * allows a maximum value of 2147483647.
 */
template <hamon::contiguous_iterator _Iterator>
constexpr __parse_number_result<_Iterator>
__parse_number(_Iterator __begin, _Iterator __end_input)
{
	using _CharT = hamon::iter_value_t<_Iterator>;
	static_assert(__format::__number_max == INT32_MAX, "The algorithm is implemented based on this value.");
	/*
	 * Limit the input to 9 digits, otherwise we need two checks during every
	 * iteration:
	 * - Are we at the end of the input?
	 * - Does the value exceed width of an uint32_t? (Switching to uint64_t would
	 *   have the same issue, but with a higher maximum.)
	 */
	_Iterator __end  = __end_input - __begin > 9 ? __begin + 9 : __end_input;
	uint32_t __value = *__begin - _CharT('0');
	while (++__begin != __end)
	{
		if (*__begin < _CharT('0') || *__begin > _CharT('9'))
		{
			return {__begin, __value};
		}

		__value = __value * 10 + *__begin - _CharT('0');
	}

	if (__begin != __end_input && *__begin >= _CharT('0') && *__begin <= _CharT('9'))
	{
		/*
		 * There are more than 9 digits, do additional validations:
		 * - Does the 10th digit exceed the maximum allowed value?
		 * - Are there more than 10 digits?
		 * (More than 10 digits always overflows the maximum.)
		 */
		uint64_t __v = uint64_t(__value) * 10 + *__begin++ - _CharT('0');
		if (__v > __format::__number_max || (__begin != __end_input && *__begin >= _CharT('0') && *__begin <= _CharT('9')))
		{
			hamon::detail::throw_format_error("The numeric value of the format specifier is too large");
		}

//		__value = __v;
		__value = static_cast<uint32_t>(__v);	// TODO
	}

	return {__begin, __value};
}

HAMON_WARNING_POP()

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___PARSE_NUMBER_HPP
