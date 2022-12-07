﻿/**
 *	@file	log.hpp
 *
 *	@brief	log 関数の定義
 */

#ifndef HAMON_CMATH_LOG_HPP
#define HAMON_CMATH_LOG_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/factorial.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/numbers/sqrt2.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <limits>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CONSTEXPR float
log_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_logf(x);
}

inline HAMON_CONSTEXPR double
log_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_log(x);
}

inline HAMON_CONSTEXPR long double
log_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_logl(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
log_unchecked_ct_2(T x, unsigned int n, unsigned int last)
{
	return last - n == 1 ?
		(n % 2 ? 1 : -1) * pow_n(x, n) / T(n) :
		log_unchecked_ct_2(x, n, n + (last - n) / 2) +
		log_unchecked_ct_2(x, n + (last - n) / 2, last);
}
template <typename T>
inline HAMON_CONSTEXPR T
log_unchecked_ct_1(T x)
{
	return !(x > hamon::numbers::sqrt2_fn<T>()) ?
		log_unchecked_ct_2(x - T(1), 1, max_factorial<T>() + 1) :
		T(2) * log_unchecked_ct_1(hamon::sqrt(x));
}
template <typename T>
inline HAMON_CONSTEXPR T
log_unchecked_ct(T x)
{
	return x < 1 ?
		-log_unchecked_ct_1(T(1) / x) :
		log_unchecked_ct_1(x);
}

template <typename T>
inline HAMON_CONSTEXPR T
log_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::log(x);
	}
#endif
	return log_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
log_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		hamon::iszero(x) ?
			-std::numeric_limits<FloatType>::infinity() :
		x == FloatType(1) ?
			FloatType(0) :
		x < FloatType(0) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(x) ?
			std::numeric_limits<FloatType>::infinity() :
		log_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	e (ネイピア数) を底とする自然対数を求める
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg の e (ネイピア数) を底とする自然対数
 *
 *	arg が ±0 だった場合、-∞ を返す。
 *	arg が 1   だった場合、+0  を返す。
 *	arg < 0    だった場合、NaN を返す。
 *	arg が +∞ だった場合、+∞ を返す。
 *	arg が NaN だった場合、NaN を返す。
 */
inline HAMON_CONSTEXPR float
log(float arg) HAMON_NOEXCEPT
{
	return detail::log_impl(arg);
}

inline HAMON_CONSTEXPR float
logf(float arg) HAMON_NOEXCEPT
{
	return detail::log_impl(arg);
}

inline HAMON_CONSTEXPR double
log(double arg) HAMON_NOEXCEPT
{
	return detail::log_impl(arg);
}

inline HAMON_CONSTEXPR long double
log(long double arg) HAMON_NOEXCEPT
{
	return detail::log_impl(arg);
}

inline HAMON_CONSTEXPR long double
logl(long double arg) HAMON_NOEXCEPT
{
	return detail::log_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
inline HAMON_CONSTEXPR double
log(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::log_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_LOG_HPP