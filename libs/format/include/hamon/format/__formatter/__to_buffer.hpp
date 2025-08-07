/**
 *	@file	__to_buffer.hpp
 *
 *	@brief	__to_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___TO_BUFFER_HPP
#define HAMON_FORMAT___FORMATTER___TO_BUFFER_HPP

#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/memory/to_address.hpp>


#include <hamon/concepts/floating_point.hpp>
#include <charconv>

namespace hamon
{

namespace __formatter
{

//
// Integer
//

/** Wrapper around @ref to_chars, returning the output iterator. */
template <hamon::contiguous_iterator _Iterator, integral _Tp>
	requires hamon::same_as<char, hamon::iter_value_t<_Iterator>>
_Iterator __to_buffer(_Iterator __first, _Iterator __last, _Tp __value, int __base)
{
	// TODO FMT Evaluate code overhead due to not calling the internal function
	// directly. (Should be zero overhead.)
	std::to_chars_result __r = std::to_chars(std::to_address(__first), std::to_address(__last), __value, __base);
//	_LIBCPP_ASSERT_INTERNAL(__r.ec == errc(0), "Internal buffer too small");
	auto __diff = __r.ptr - std::to_address(__first);
	return __first + __diff;
}





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
