/**
 *	@file	log2.hpp
 *
 *	@brief	log2 関数の定義
 */

#ifndef HAMON_CMATH_LOG2_HPP
#define HAMON_CMATH_LOG2_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/numbers/ln2.hpp>
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
log2_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_log2f(x);
}

inline HAMON_CONSTEXPR double
log2_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_log2(x);
}

inline HAMON_CONSTEXPR long double
log2_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_log2l(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
log2_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return hamon::log(x) / hamon::numbers::ln2_fn<T>();
}

template <typename T>
inline HAMON_CONSTEXPR T
log2_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::log2(x);
	}
#endif
	return log2_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
log2_impl(FloatType x) HAMON_NOEXCEPT
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
		log2_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	2 を底とする二進対数を求める
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x の 2 を底とする二進対数
 *
 *	x が ±0  だった場合、-∞ を返す。
 *	x が 1   だった場合、+0  を返す。
 *	x < 0    だった場合、NaN を返す。
 *	x が +∞  だった場合、+∞ を返す。
 *	x が NaN だった場合、NaN を返す。
 */
HAMON_NODISCARD inline HAMON_CONSTEXPR float
log2(float arg) HAMON_NOEXCEPT
{
	return detail::log2_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR float
log2f(float arg) HAMON_NOEXCEPT
{
	return detail::log2_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR double
log2(double arg) HAMON_NOEXCEPT
{
	return detail::log2_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
log2(long double arg) HAMON_NOEXCEPT
{
	return detail::log2_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
log2l(long double arg) HAMON_NOEXCEPT
{
	return detail::log2_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR double
log2(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::log2_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_LOG2_HPP
