/**
 *	@file	log1p.hpp
 *
 *	@brief	log1p 関数の定義
 */

#ifndef HAMON_CMATH_LOG1P_HPP
#define HAMON_CMATH_LOG1P_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/log.hpp>
//#include <hamon/cmath/signbit.hpp>
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
log1p_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_log1pf(x);
}

inline HAMON_CONSTEXPR double
log1p_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_log1p(x);
}

inline HAMON_CONSTEXPR long double
log1p_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_log1pl(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
log1p_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return hamon::log(T(1) + x);
}

template <typename T>
inline HAMON_CONSTEXPR T
log1p_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::log1p(x);
	}
#endif
	return log1p_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
log1p_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		hamon::iszero(x) ?
			x :
		x == -1 ?
			-std::numeric_limits<FloatType>::infinity() :
		x < -1 ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(x) ? //&& !hamon::signbit(x) ?
			std::numeric_limits<FloatType>::infinity() :
		log1p_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	引数に 1 を足した値の、e (ネイピア数) を底とする自然対数を求める。
 *
 *	@param	arg
 *
 *	@return	引数 arg に対して 1+arg の e (ネイピア数) を底とする自然対数を返す。
 *
 *	arg が ±0    の場合、±0 を返す。
 *	arg が -1     の場合、-∞ を返す。
 *	arg が -1未満 の場合、NaN を返す。
 *	arg が +∞    の場合、+∞ を返す。
 *	arg が NaN    の場合、NaN を返す。
 */
HAMON_NODISCARD inline HAMON_CONSTEXPR float
log1p(float arg) HAMON_NOEXCEPT
{
	return detail::log1p_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR float
log1pf(float arg) HAMON_NOEXCEPT
{
	return detail::log1p_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR double
log1p(double arg) HAMON_NOEXCEPT
{
	return detail::log1p_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
log1p(long double arg) HAMON_NOEXCEPT
{
	return detail::log1p_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
log1pl(long double arg) HAMON_NOEXCEPT
{
	return detail::log1p_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR double
log1p(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::log1p_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_LOG1P_HPP
