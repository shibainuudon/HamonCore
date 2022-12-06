/**
 *	@file	sin.hpp
 *
 *	@brief	sin 関数の定義
 */

#ifndef HAMON_CMATH_SIN_HPP
#define HAMON_CMATH_SIN_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <limits>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CONSTEXPR float
sin_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_sinf(x);
}

inline HAMON_CONSTEXPR double
sin_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_sin(x);
}

inline HAMON_CONSTEXPR long double
sin_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_sinl(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
sin_unchecked(T x) HAMON_NOEXCEPT
{
	return std::sin(x);
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
sin_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			x :
		hamon::isinf(x) || hamon::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		sin_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	正弦（サイン）を取得する
 *
 *	@param	arg	算術型の値(ラジアン）
 *
 *	@return	関数に成功すると、argのサインを返す
 *
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が ±∞ の場合、NaNを返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline HAMON_CONSTEXPR float
sin(float arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

inline HAMON_CONSTEXPR float
sinf(float arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

inline HAMON_CONSTEXPR double
sin(double arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

inline HAMON_CONSTEXPR long double
sin(long double arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

inline HAMON_CONSTEXPR long double
sinl(long double arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
inline HAMON_CONSTEXPR double
sin(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_SIN_HPP
