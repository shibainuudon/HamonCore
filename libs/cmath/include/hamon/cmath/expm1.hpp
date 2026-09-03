/**
 *	@file	expm1.hpp
 *
 *	@brief	expm1 関数の定義
 */

#ifndef HAMON_CMATH_EXPM1_HPP
#define HAMON_CMATH_EXPM1_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
expm1_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return hamon::exp(x) - T(1);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
expm1_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::expm1(x);
}

inline HAMON_CXX11_CONSTEXPR float
expm1_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_expm1f(x);
#elif HAMON_HAS_BUILTIN(__builtin_expm1f)
	return hamon::is_constant_evaluated() ? expm1_unchecked_ct(x) : __builtin_expm1f(x);
#else
	return hamon::is_constant_evaluated() ? expm1_unchecked_ct(x) : expm1_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
expm1_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_expm1(x);
#elif HAMON_HAS_BUILTIN(__builtin_expm1)
	return hamon::is_constant_evaluated() ? expm1_unchecked_ct(x) : __builtin_expm1(x);
#else
	return hamon::is_constant_evaluated() ? expm1_unchecked_ct(x) : expm1_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
expm1_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_expm1l(x);
#elif HAMON_HAS_BUILTIN(__builtin_expm1l)
	return hamon::is_constant_evaluated() ? expm1_unchecked_ct(x) : __builtin_expm1l(x);
#else
	return hamon::is_constant_evaluated() ? expm1_unchecked_ct(x) : expm1_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
expm1_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			x :
		hamon::isinf(x) ?
			hamon::signbit(x) ?
				FloatType(-1) :
			x :
		hamon::isnan(x) ?
			x :
		expm1_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	e (ネイピア数) を底とする指数関数から 1 を引いた値を求める。
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	e (ネイピア数) の x 乗から 1 を引いた値を返す。
 *
 *	x が ±0  の場合、±0 を返す。
 *	x が -∞  の場合、-1  を返す。
 *	x が +∞  の場合、+∞ を返す。
 *	x が NaN  の場合、NaN を返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
expm1(FloatType arg) HAMON_NOEXCEPT
{
	return detail::expm1_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
expm1f(float arg) HAMON_NOEXCEPT
{
	return detail::expm1_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
expm1l(long double arg) HAMON_NOEXCEPT
{
	return detail::expm1_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
expm1(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::expm1_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_EXPM1_HPP
