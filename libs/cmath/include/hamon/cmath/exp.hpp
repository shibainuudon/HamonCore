/**
 *	@file	exp.hpp
 *
 *	@brief	exp 関数の定義
 */

#ifndef HAMON_CMATH_EXP_HPP
#define HAMON_CMATH_EXP_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CONSTEXPR float
exp_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_expf(x);
}

inline HAMON_CONSTEXPR double
exp_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_exp(x);
}

inline HAMON_CONSTEXPR long double
exp_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_expl(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
exp_unchecked(T x) HAMON_NOEXCEPT
{
	return std::exp(x);	// TODO
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
exp_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			FloatType(1) :
		hamon::isinf(x) ?
			hamon::signbit(x) ?
				FloatType(0) :
			x :
		hamon::isnan(x) ?
			x :
		exp_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	e (ネイピア数) を底とする指数関数を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、e (ネイピア数) の arg 乗を返す。
 *
 *	arg が ±0  の場合、1  を返す。
 *	arg が -∞  の場合、+0 を返す。
 *	arg が +∞  の場合、+∞ を返す。
 *	arg が NaN  の場合、NaN を返す。
 */
inline HAMON_CONSTEXPR float
exp(float arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

inline HAMON_CONSTEXPR float
expf(float arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

inline HAMON_CONSTEXPR double
exp(double arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

inline HAMON_CONSTEXPR long double
exp(long double arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

inline HAMON_CONSTEXPR long double
expl(long double arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
inline HAMON_CONSTEXPR double
exp(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_EXP_HPP
