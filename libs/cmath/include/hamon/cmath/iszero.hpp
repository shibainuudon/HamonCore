/**
 *	@file	iszero.hpp
 *
 *	@brief	iszero
 */

#ifndef HAMON_CMATH_ISZERO_HPP
#define HAMON_CMATH_ISZERO_HPP

#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	std::iszero のconstexpr版
 */
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
iszero(float arg) HAMON_NOEXCEPT
{
	return arg == 0.0f;
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
iszero(double arg) HAMON_NOEXCEPT
{
	return arg == 0.0;
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
iszero(long double arg) HAMON_NOEXCEPT
{
	return arg == 0.0l;
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
iszero(IntegralType arg) HAMON_NOEXCEPT
{
	return arg == 0;
}

}	// namespace hamon

#endif // HAMON_CMATH_ISZERO_HPP
