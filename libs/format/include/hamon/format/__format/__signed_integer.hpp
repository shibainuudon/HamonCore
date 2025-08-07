/**
 *	@file	__signed_integer.hpp
 *
 *	@brief	__signed_integer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___SIGNED_INTEGER_HPP
#define HAMON_FORMAT___FORMAT___SIGNED_INTEGER_HPP

#include <hamon/format/detail/is_signed_integer.hpp>

namespace hamon
{

namespace __format
{

template <class _Tp>
concept __signed_integer = hamon::detail::is_signed_integer<_Tp>::value;

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___SIGNED_INTEGER_HPP
