/**
 *	@file	exp2.hpp
 *
 *	@brief	exp2 関数の定義
 */

#ifndef HAMON_CMATH_EXP2_HPP
#define HAMON_CMATH_EXP2_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/numbers/ln2.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CONSTEXPR float
exp2_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_exp2f(x);
}

inline HAMON_CONSTEXPR double
exp2_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_exp2(x);
}

inline HAMON_CONSTEXPR long double
exp2_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_exp2l(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
exp2_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return hamon::exp(x * hamon::numbers::ln2_fn<T>());
}

template <typename T>
inline HAMON_CONSTEXPR T
exp2_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::exp2(x);
	}
#endif
	return exp2_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
exp2_impl(FloatType x) HAMON_NOEXCEPT
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
		exp2_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	2 を底とする指数関数を求める
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、2 の x 乗を返す。
 *
 *	x が ±0  の場合、1  を返す。
 *	x が -∞  の場合、+0 を返す。
 *	x が +∞  の場合、+∞ を返す。
 *	x が NaN  の場合、NaN を返す。
 */
inline HAMON_CONSTEXPR float
exp2(float arg) HAMON_NOEXCEPT
{
	return detail::exp2_impl(arg);
}

inline HAMON_CONSTEXPR float
exp2f(float arg) HAMON_NOEXCEPT
{
	return detail::exp2_impl(arg);
}

inline HAMON_CONSTEXPR double
exp2(double arg) HAMON_NOEXCEPT
{
	return detail::exp2_impl(arg);
}

inline HAMON_CONSTEXPR long double
exp2(long double arg) HAMON_NOEXCEPT
{
	return detail::exp2_impl(arg);
}

inline HAMON_CONSTEXPR long double
exp2l(long double arg) HAMON_NOEXCEPT
{
	return detail::exp2_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
inline HAMON_CONSTEXPR double
exp2(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::exp2_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_EXP2_HPP
