/**
 *	@file	tgamma.hpp
 *
 *	@brief	tgamma 関数の定義
 */

#ifndef HAMON_CMATH_TGAMMA_HPP
#define HAMON_CMATH_TGAMMA_HPP

#include <hamon/algorithm/clamp.hpp>
#include <hamon/cmath/factorial.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/is_integer.hpp>
#include <hamon/cmath/round.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
tgamma_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_tgammaf(x);
}

inline HAMON_CXX11_CONSTEXPR double
tgamma_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_tgamma(x);
}

inline HAMON_CXX11_CONSTEXPR long double
tgamma_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_tgammal(x);
}

#else

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_y(T w)
{
	return static_cast<T>(((((((((((((
		-1.99542863674e-7      * w + 1.337767384067e-6)    * w +
		-2.591225267689e-6)    * w - 1.7545539395205e-5)   * w +
		 1.45596568617526e-4)  * w - 3.60837876648255e-4)  * w +
		-8.04329819255744e-4)  * w + 0.008023273027855346) * w +
		-0.017645244547851414) * w - 0.024552490005641278) * w +
		 0.19109110138763841)  * w - 0.233093736421782878) * w +
		-0.422784335098466784) * w + 0.99999999999999999);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_t_pos(T x, int n, int last)
{
	return last - n == 1 ?
		x - static_cast<T>(n) :
		tgamma_unchecked_ct_t_pos(x, n, n + (last - n) / 2) *
		tgamma_unchecked_ct_t_pos(x, n + (last - n) / 2, last);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_t_neg(T x, int n, int last)
{
	return last - n == 1 ?
		x + static_cast<T>(n) :
		tgamma_unchecked_ct_t_neg(x, n, n + (last - n) / 2) *
		tgamma_unchecked_ct_t_neg(x, n + (last - n) / 2, last);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_t_pos_rec(T x, int n, int last)
{
	return last - n == 1 ?
		T(1) / (x - static_cast<T>(n)) :
		tgamma_unchecked_ct_t_pos_rec(x, n, n + (last - n) / 2) *
		tgamma_unchecked_ct_t_pos_rec(x, n + (last - n) / 2, last);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_t_neg_rec(T x, int n, int last)
{
	return last - n == 1 ?
		T(1) / (x + static_cast<T>(n)) :
		tgamma_unchecked_ct_t_neg_rec(x, n, n + (last - n) / 2) *
		tgamma_unchecked_ct_t_neg_rec(x, n + (last - n) / 2, last);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_2_pos_rec(T x, T y, T t)
{
	return t == 0 ? hamon::numeric_limits<T>::infinity() :
		(x - T(1)) / y / t;
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_1(T x, int n)
{
	return
		n == 1 ?
			(x - T(1)) / tgamma_unchecked_ct_y(x - T(n + 2)) :
		n == 0 ?
			T(1) / tgamma_unchecked_ct_y(x - T(n + 2)) :
		n == static_cast<int>(hamon::detail::max_factorial<T>()) ?
			tgamma_unchecked_ct_2_pos_rec(x, tgamma_unchecked_ct_y(x - T(n + 2)), tgamma_unchecked_ct_t_pos_rec(x, 2, n + 1)) :
		n == -static_cast<int>(hamon::detail::max_factorial<T>()) ?
			T(1) / tgamma_unchecked_ct_y(x - T(n + 2)) * tgamma_unchecked_ct_t_neg_rec(x, 0, -n) :
		n > 1 ?
			(x - T(1)) / tgamma_unchecked_ct_y(x - T(n + 2)) * tgamma_unchecked_ct_t_pos(x, 2, n + 1) :
			T(1) / tgamma_unchecked_ct_y(x - T(n + 2)) / tgamma_unchecked_ct_t_neg(x, 0, -n);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct(T x)
{
	return tgamma_unchecked_ct_1(
		x,
		hamon::clamp(
			static_cast<int>(hamon::round(x - T(2))),
			-static_cast<int>(hamon::detail::max_factorial<T>()),
			 static_cast<int>(hamon::detail::max_factorial<T>())));
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::tgamma(x);
	}
#endif
	return tgamma_unchecked_ct(x);
}

#endif

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
tgamma_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::iszero(x) ?
			hamon::numeric_limits<FloatType>::infinity() :
		(x < 0 && hamon::is_integer(x)) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(x)  ?
			hamon::signbit(x) ?
				hamon::numeric_limits<FloatType>::quiet_NaN() :
			hamon::numeric_limits<FloatType>::infinity() :
		tgamma_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	ガンマ関数を計算します．
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x
 *
 *	@return	x のガンマ関数を返します。
 *
 *	x が ±0      の場合、+∞ を返す。
 *	x が 負の整数 の場合、NaN を返す。
 *	x が -∞      の場合、NaN を返す。
 *	x が +∞      の場合、+∞ を返す。
 *	x が NaN     の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
tgamma(FloatType arg) HAMON_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
tgamma(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::tgamma_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
tgammaf(float arg) HAMON_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
tgammal(long double arg) HAMON_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_TGAMMA_HPP
