/**
 *	@file	logb.hpp
 *
 *	@brief	logb 関数の定義
 */

#ifndef HAMON_CMATH_LOGB_HPP
#define HAMON_CMATH_LOGB_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/numbers/ln2.hpp>
#include <hamon/numbers/ln10.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <limits>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
log_a(T x, T y)
{
	return
		x ==  2 ? hamon::log(y) / hamon::numbers::ln2_fn<T>() :
		x == 10 ? hamon::log(y) / hamon::numbers::ln10_fn<T>() :
		hamon::log(y) / hamon::log(x);
}

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
logb_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_logbf(x);
}

inline HAMON_CXX11_CONSTEXPR double
logb_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_logb(x);
}

inline HAMON_CXX11_CONSTEXPR long double
logb_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_logbl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_3_neg_lo(T x, T x0, T base, T exp, T radix = std::numeric_limits<T>::radix)
{
	return
		base < 1 ?
			logb_unchecked_ct_3_neg_lo(x, x0 * radix, x / (x0 / radix), exp - 1) :
		exp;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_3_neg_hi(T x, T x0, T base, T exp, T radix = std::numeric_limits<T>::radix)
{
	return
		!(base < radix) ?
			logb_unchecked_ct_3_neg_hi(x, x0 / radix, x / (x0 * radix), exp + 1) :
		exp;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_3_pos_lo(T x, T x0, T base, T exp, T radix = std::numeric_limits<T>::radix)
{
	return
		base < 1 ?
			logb_unchecked_ct_3_pos_lo(x, x0 * radix, x / (x0 / radix), exp - 1) :
		exp;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_3_pos_hi(T x, T x0, T base, T exp, T radix = std::numeric_limits<T>::radix)
{
	return
		!(base < radix) ?
			logb_unchecked_ct_3_pos_hi(x, x0 / radix, x / (x0 * radix), exp + 1) :
		exp;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_3(T x, T x0, T base, T exp, T radix = std::numeric_limits<T>::radix)
{
	return
		x < 1 ?
			base < 1 ?
				logb_unchecked_ct_3_neg_lo(x, x0 * radix, x / (x0 / radix), exp - 1) :
			!(base < radix) ?
				logb_unchecked_ct_3_neg_hi(x, x0 / radix, x / (x0 * radix), exp + 1) :
			exp :
		base < 1 ?
			logb_unchecked_ct_3_pos_lo(x, x0 * radix, x / (x0 / radix), exp - 1) :
		!(base < radix) ?
			logb_unchecked_ct_3_pos_hi(x, x0 / radix, x / (x0 * radix), exp + 1) :
		exp;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_2(T x, T x0, T exp)
{
	return logb_unchecked_ct_3(x, x0, x / x0, exp);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_1(T x, T exp, T radix = std::numeric_limits<T>::radix)
{
	return logb_unchecked_ct_2(
		x, hamon::detail::pow_n(radix, /*hamon::itrunc*/static_cast<hamon::intmax_t>(exp)), exp);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct(T x, T radix = std::numeric_limits<T>::radix) HAMON_NOEXCEPT
{
	return x < 0 ?
		logb_unchecked_ct_1(-x, hamon::trunc(log_a(radix, -x))) :
		logb_unchecked_ct_1( x, hamon::trunc(log_a(radix,  x)));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
logb_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::logb(x);
	}
#endif
	return logb_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
logb_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			-std::numeric_limits<FloatType>::infinity() :
		hamon::isinf(x) ?
			std::numeric_limits<FloatType>::infinity() :
		hamon::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		logb_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	浮動小数点数の指数部を返す
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg の 指数部
 *
 *	arg が ±0  だった場合、-∞ を返す。
 *	arg が ±∞  だった場合、+∞ を返す。
 *	arg が NaN だった場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
logb(FloatType arg) HAMON_NOEXCEPT
{
	return detail::logb_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
logbf(float arg) HAMON_NOEXCEPT
{
	return detail::logb_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
logbl(long double arg) HAMON_NOEXCEPT
{
	return detail::logb_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
logb(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::logb_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_LOGB_HPP
