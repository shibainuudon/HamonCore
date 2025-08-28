/**
 *	@file	__to_buffer.hpp
 *
 *	@brief	__to_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___TO_BUFFER_HPP
#define HAMON_FORMAT___FORMATTER___TO_BUFFER_HPP

#include <hamon/concepts/floating_point.hpp>
#include <charconv>

namespace hamon
{

namespace __formatter
{

template <hamon::floating_point _Tp>
char* __to_buffer(char* __first, char* __last, _Tp __value)
{
	std::to_chars_result __r = std::to_chars(__first, __last, __value);
//	_LIBCPP_ASSERT_INTERNAL(__r.ec == errc(0), "Internal buffer too small");
	return __r.ptr;
}

template <hamon::floating_point _Tp>
char* __to_buffer(char* __first, char* __last, _Tp __value, std::chars_format __fmt)
{
	std::to_chars_result __r = std::to_chars(__first, __last, __value, __fmt);
//	_LIBCPP_ASSERT_INTERNAL(__r.ec == errc(0), "Internal buffer too small");
	return __r.ptr;
}

template <hamon::floating_point _Tp>
char* __to_buffer(char* __first, char* __last, _Tp __value, std::chars_format __fmt, int __precision)
{
	std::to_chars_result __r = std::to_chars(__first, __last, __value, __fmt, __precision);
//	_LIBCPP_ASSERT_INTERNAL(__r.ec == errc(0), "Internal buffer too small");
	return __r.ptr;
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___TO_BUFFER_HPP
