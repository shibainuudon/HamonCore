/**
 *	@file	logb.hpp
 *
 *	@brief	logb 関数の定義
 */

#ifndef HAMON_CMATH_LOGB_HPP
#define HAMON_CMATH_LOGB_HPP

#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/numbers/ln2.hpp>
#include <hamon/numbers/ln10.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_a(T x, T y)
{
	return
		x ==  2 ? hamon::log(y) / hamon::numbers::ln2_v<T> :
		x == 10 ? hamon::log(y) / hamon::numbers::ln10_v<T> :
		hamon::log(y) / hamon::log(x);
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
logb_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T const radix = hamon::numeric_limits<T>::radix;
	x = hamon::fabs(x);
	T exp = hamon::trunc(logb_unchecked_ct_a(radix, x));
	T x0 = hamon::detail::pow_n(radix, static_cast<hamon::intmax_t>(exp));
	T base = x / x0;

	for (;;)
	{
		if (base < 1)
		{
			base = x / (x0 / radix);
			x0 *= radix;
			exp -= 1;
		}
		else if (base >= radix)
		{
			base = x / (x0 * radix);
			x0 /= radix;
			exp += 1;
		}
		else
		{
			return exp;
		}
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
logb_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::logb(x);
}

inline HAMON_CXX11_CONSTEXPR float
logb_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_logbf(x);
#elif HAMON_HAS_BUILTIN(__builtin_logbf)
	return hamon::is_constant_evaluated() ? logb_unchecked_ct(x) : __builtin_logbf(x);
#else
	return hamon::is_constant_evaluated() ? logb_unchecked_ct(x) : logb_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
logb_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_logb(x);
#elif HAMON_HAS_BUILTIN(__builtin_logb)
	return hamon::is_constant_evaluated() ? logb_unchecked_ct(x) : __builtin_logb(x);
#else
	return hamon::is_constant_evaluated() ? logb_unchecked_ct(x) : logb_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
logb_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_logbl(x);
#elif HAMON_HAS_BUILTIN(__builtin_logbl)
	return hamon::is_constant_evaluated() ? logb_unchecked_ct(x) : __builtin_logbl(x);
#else
	return hamon::is_constant_evaluated() ? logb_unchecked_ct(x) : logb_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
logb_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			-hamon::numeric_limits<FloatType>::infinity() :
		hamon::isinf(x) ?
			hamon::numeric_limits<FloatType>::infinity() :
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
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
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
logb(FloatType arg) HAMON_NOEXCEPT
{
	return detail::logb_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
logb(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::logb_impl(static_cast<double>(arg));
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

}	// namespace hamon

#endif // HAMON_CMATH_LOGB_HPP
