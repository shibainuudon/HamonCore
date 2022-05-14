﻿/**
 *	@file	iszero.hpp
 *
 *	@brief	iszero
 */

#ifndef HAMON_CMATH_ISZERO_HPP
#define HAMON_CMATH_ISZERO_HPP

#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	std::iszero のconstexpr版
 */
inline HAMON_CONSTEXPR bool
iszero(float arg) HAMON_NOEXCEPT
{
	return arg == 0.0f;
}

inline HAMON_CONSTEXPR bool
iszero(double arg) HAMON_NOEXCEPT
{
	return arg == 0.0;
}

inline HAMON_CONSTEXPR bool
iszero(long double arg) HAMON_NOEXCEPT
{
	return arg == 0.0l;
}

template <
	typename IntegralType,
	typename = typename std::enable_if<
		std::is_integral<IntegralType>::value
	>::type
>
inline HAMON_CONSTEXPR bool
iszero(IntegralType arg) HAMON_NOEXCEPT
{
	return arg == 0;
}

}	// namespace hamon

#endif // HAMON_CMATH_ISZERO_HPP
