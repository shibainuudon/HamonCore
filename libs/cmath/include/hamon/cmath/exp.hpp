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
#include <hamon/cmath/factorial.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <type_traits>
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
exp_unchecked_ct_1(T x, unsigned int n, unsigned int last) HAMON_NOEXCEPT
{
	return last - n == 1 ?
		pow_n(x, n) / unchecked_factorial<T>(n) :
		exp_unchecked_ct_1(x, n, n + (last - n) / 2) +
		exp_unchecked_ct_1(x, n + (last - n) / 2, last);
}

template <typename T>
inline HAMON_CONSTEXPR T
exp_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return !(x > -1) ?
		T(1) / (T(1) + exp_unchecked_ct_1(-x, 1, max_factorial<T>() / 2 + 1)) :
		        T(1) + exp_unchecked_ct_1( x, 1, max_factorial<T>() / 2 + 1);
}

template <typename T>
inline HAMON_CONSTEXPR T
exp_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::exp(x);
	}
#endif
	return exp_unchecked_ct(x);
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
HAMON_NODISCARD inline HAMON_CONSTEXPR float
exp(float arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR float
expf(float arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR double
exp(double arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
exp(long double arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
expl(long double arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR double
exp(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_EXP_HPP
