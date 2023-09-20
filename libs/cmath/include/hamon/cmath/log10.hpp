/**
 *	@file	log10.hpp
 *
 *	@brief	log10 関数の定義
 */

#ifndef HAMON_CMATH_LOG10_HPP
#define HAMON_CMATH_LOG10_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/numbers/ln10.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
log10_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_log10f(x);
}

inline HAMON_CXX11_CONSTEXPR double
log10_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_log10(x);
}

inline HAMON_CXX11_CONSTEXPR long double
log10_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_log10l(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
log10_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return hamon::log(x) / hamon::numbers::ln10_fn<T>();
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
log10_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::log10(x);
	}
#endif
	return log10_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
log10_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::iszero(x) ?
			-hamon::numeric_limits<FloatType>::infinity() :
		x == FloatType(1) ?
			FloatType(0) :
		x < FloatType(0) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(x) ?
			hamon::numeric_limits<FloatType>::infinity() :
		log10_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	10 を底とする常用対数を求める
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x の 10 を底とする常用対数
 *
 *	x が ±0  だった場合、-∞ を返す。
 *	x が 1   だった場合、+0  を返す。
 *	x < 0    だった場合、NaN を返す。
 *	x が +∞  だった場合、+∞ を返す。
 *	x が NaN だった場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
log10(FloatType arg) HAMON_NOEXCEPT
{
	return detail::log10_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
log10f(float arg) HAMON_NOEXCEPT
{
	return detail::log10_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
log10l(long double arg) HAMON_NOEXCEPT
{
	return detail::log10_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
log10(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::log10_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_LOG10_HPP
