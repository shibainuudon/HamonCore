/**
 *	@file	__code_point.hpp
 *
 *	@brief	__code_point の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___CODE_POINT_HPP
#define HAMON_FORMAT___FORMAT_SPEC___CODE_POINT_HPP


namespace hamon
{

namespace __format_spec
{

// The fill UCS scalar value.
//
// This is always an array, with 1, 2, or 4 elements.
// The size of the data structure is always 32-bits.
template <class _CharT>
struct __code_point;

template <>
struct __code_point<char>
{
	char __data[4] = {' '};
};

template <>
struct __code_point<wchar_t>
{
	wchar_t __data[4 / sizeof(wchar_t)] = {L' '};
};

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___CODE_POINT_HPP
