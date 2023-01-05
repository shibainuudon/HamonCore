/**
 *	@file	iszero.hpp
 *
 *	@brief	iszero
 */

#ifndef HAMON_CMATH_ISZERO_HPP
#define HAMON_CMATH_ISZERO_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

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

template <
	typename IntegralType,
	typename = hamon::enable_if_t<
		std::is_integral<IntegralType>::value
	>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
iszero(IntegralType arg) HAMON_NOEXCEPT
{
	return arg == 0;
}

}	// namespace hamon

#endif // HAMON_CMATH_ISZERO_HPP
