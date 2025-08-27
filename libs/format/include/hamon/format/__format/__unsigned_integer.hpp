/**
 *	@file	__unsigned_integer.hpp
 *
 *	@brief	__unsigned_integer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___UNSIGNED_INTEGER_HPP
#define HAMON_FORMAT___FORMAT___UNSIGNED_INTEGER_HPP

#include <hamon/format/detail/is_unsigned_integer.hpp>

namespace hamon
{

namespace __format
{

template <class _Tp>
concept __unsigned_integer = hamon::detail::is_unsigned_integer<_Tp>::value;

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___UNSIGNED_INTEGER_HPP
