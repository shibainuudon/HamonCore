/**
 *	@file	signbit.hpp
 *
 *	@brief	signbit
 */

#ifndef HAMON_CMATH_SIGNBIT_HPP
#define HAMON_CMATH_SIGNBIT_HPP

#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	std::signbit のconstexpr版
 *
 *	※std::signbitとの違い
 *	argが±0または±NaNのとき、falseを返す。
 *	これはconstexpr関数にするための制限。
 */
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
signbit(float arg) HAMON_NOEXCEPT
{
	// argがNANのときのために
	// return arg < 0.0f; としない
	return 0.0f > arg;
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
signbit(double arg) HAMON_NOEXCEPT
{
	return 0.0 > arg;
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
signbit(long double arg) HAMON_NOEXCEPT
{
	return 0.0l > arg;
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
signbit(IntegralType arg) HAMON_NOEXCEPT
{
	return arg < 0;
}

}	// namespace hamon

#endif // HAMON_CMATH_SIGNBIT_HPP
