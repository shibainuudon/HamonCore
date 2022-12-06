/**
 *	@file	cos.hpp
 *
 *	@brief	cos 関数の定義
 */

#ifndef HAMON_CMATH_COS_HPP
#define HAMON_CMATH_COS_HPP

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
cos_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_cosf(x);
}

inline HAMON_CONSTEXPR double
cos_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_cos(x);
}

inline HAMON_CONSTEXPR long double
cos_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_cosl(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
cos_unchecked(T x) HAMON_NOEXCEPT
{
	return std::cos(x);
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
cos_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			FloatType(1) :
		hamon::isinf(x) || hamon::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		cos_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	余弦（コサイン）を取得する
 *
 *	@param	arg	算術型の値(ラジアン）
 *
 *	@return	関数に成功すると、argのコサインを返す
 *
 *	arg が ±0  の場合、1を返す。
 *	arg が ±∞ の場合、NaNを返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline HAMON_CONSTEXPR float
cos(float arg) HAMON_NOEXCEPT
{
	return detail::cos_impl(arg);
}

inline HAMON_CONSTEXPR float
cosf(float arg) HAMON_NOEXCEPT
{
	return detail::cos_impl(arg);
}

inline HAMON_CONSTEXPR double
cos(double arg) HAMON_NOEXCEPT
{
	return detail::cos_impl(arg);
}

inline HAMON_CONSTEXPR long double
cos(long double arg) HAMON_NOEXCEPT
{
	return detail::cos_impl(arg);
}

inline HAMON_CONSTEXPR long double
cosl(long double arg) HAMON_NOEXCEPT
{
	return detail::cos_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
inline HAMON_CONSTEXPR double
cos(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::cos_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_COS_HPP
