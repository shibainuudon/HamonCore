/**
 *	@file	signbit.hpp
 *
 *	@brief	signbit
 */

#ifndef HAMON_CMATH_SIGNBIT_HPP
#define HAMON_CMATH_SIGNBIT_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::signbit;

}	// namespace hamon

#else

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
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
signbit(Arithmetic arg) HAMON_NOEXCEPT
{
	// argがNANのときのために
	// return arg < 0.0f; としない
	return Arithmetic(0) > arg;
}

}	// namespace hamon

#endif

#endif // HAMON_CMATH_SIGNBIT_HPP
