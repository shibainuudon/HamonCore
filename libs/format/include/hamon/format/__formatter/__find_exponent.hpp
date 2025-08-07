/**
 *	@file	__find_exponent.hpp
 *
 *	@brief	__find_exponent の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FIND_EXPONENT_HPP
#define HAMON_FORMAT___FORMATTER___FIND_EXPONENT_HPP

#include <hamon/algorithm/min.hpp>

namespace hamon
{

namespace __formatter
{

/// Finds the position of the exponent character 'e' at the end of the buffer.
///
/// Assuming there is an exponent the input will terminate with
/// eSdd and eSdddd (S = sign, d = digit)
///
/// \returns a pointer to the exponent or __last when not found.
constexpr inline char*
__find_exponent(char* __first, char* __last)
{
	ptrdiff_t __size = __last - __first;
	if (__size >= 4)
	{
		__first = __last - hamon::min(__size, ptrdiff_t(6));
		for (; __first != __last - 3; ++__first)
		{
			if (*__first == 'e')
			{
				return __first;
			}
		}
	}
	return __last;
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FIND_EXPONENT_HPP
