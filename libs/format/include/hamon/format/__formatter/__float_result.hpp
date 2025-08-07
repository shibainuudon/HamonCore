/**
 *	@file	__float_result.hpp
 *
 *	@brief	__float_result の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FLOAT_RESULT_HPP
#define HAMON_FORMAT___FORMATTER___FLOAT_RESULT_HPP

namespace hamon
{

namespace __formatter
{

struct __float_result
{
	/// Points at the beginning of the integral part in the buffer.
	///
	/// When there's no sign character this points at the start of the buffer.
	char* __integral;

	/// Points at the radix point, when not present it's the same as \ref __last.
	char* __radix_point;

	/// Points at the exponent character, when not present it's the same as \ref __last.
	char* __exponent;

	/// Points beyond the last written element in the buffer.
	char* __last;
};

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FLOAT_RESULT_HPP
