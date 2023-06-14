/**
 *	@file	signbit.hpp
 *
 *	@brief	signbit
 */

#ifndef HAMON_CMATH_SIGNBIT_HPP
#define HAMON_CMATH_SIGNBIT_HPP

#include <hamon/concepts/arithmetic.hpp>
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
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
signbit(Arithmetic arg) HAMON_NOEXCEPT
{
	// argがNANのときのために
	// return arg < 0.0f; としない
	return Arithmetic(0) > arg;
}

}	// namespace hamon

#endif // HAMON_CMATH_SIGNBIT_HPP
