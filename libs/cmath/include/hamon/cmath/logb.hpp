/**
 *	@file	logb.hpp
 *
 *	@brief	logb 関数の定義
 */

#ifndef HAMON_CMATH_LOGB_HPP
#define HAMON_CMATH_LOGB_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::logb;
using std::logbf;
using std::logbl;

}	// namespace hamon

#else

#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/numbers/ln2.hpp>
#include <hamon/numbers/ln10.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
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

#if defined(HAMON_HAS_CXX14_CONSTEXPR)

template <typename T>
HAMON_CXX14_CONSTEXPR T
logb_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T const radix = hamon::numeric_limits<T>::radix;
	x = hamon::fabs(x);
	T exp = hamon::trunc(log_a(radix, x));
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

#else

template <typename T>
HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_3(T x, T x0, T base, T exp, T radix)
{
	return
		base < 1 ?
			logb_unchecked_ct_3(x, x0 * radix, x / (x0 / radix), exp - 1, radix) :
		base >= radix ?
			logb_unchecked_ct_3(x, x0 / radix, x / (x0 * radix), exp + 1, radix) :
		exp;
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_2(T x, T x0, T exp, T radix)
{
	return logb_unchecked_ct_3(x, x0, x / x0, exp, radix);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct_1(T x, T exp, T radix)
{
	return logb_unchecked_ct_2(
		x, hamon::detail::pow_n(radix, static_cast<hamon::intmax_t>(exp)), exp, radix);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
logb_unchecked_ct(T x, T radix = hamon::numeric_limits<T>::radix) HAMON_NOEXCEPT
{
	return logb_unchecked_ct_1(
		hamon::fabs(x), hamon::trunc(log_a(radix, hamon::fabs(x))), radix);
}

#endif

template <typename T>
HAMON_CXX11_CONSTEXPR T
logb_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::logb(x);
	}
#endif
	return logb_unchecked_ct(x);
}

#endif

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
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
logb(FloatType arg) HAMON_NOEXCEPT
{
	return detail::logb_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
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

#endif

#endif // HAMON_CMATH_LOGB_HPP
