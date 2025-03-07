﻿/**
 *	@file	sqrt.hpp
 *
 *	@brief	sqrt 関数の定義
 */

#ifndef HAMON_CMATH_SQRT_HPP
#define HAMON_CMATH_SQRT_HPP

#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
sqrt_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_sqrtf(x);
}

inline HAMON_CXX11_CONSTEXPR double
sqrt_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_sqrt(x);
}

inline HAMON_CXX11_CONSTEXPR long double
sqrt_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_sqrtl(x);
}

#else

#if defined(HAMON_HAS_CXX14_CONSTEXPR)

template <typename T>
HAMON_CXX14_CONSTEXPR T
sqrt_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T s = x > 1 ? x : T(1);
	for (;;)
	{
		T const s1 = (x / s + s) / 2;
		if (s <= s1)
		{
			break;
		}
		s = s1;
	}
	return s;
}

#else

template <typename T>
HAMON_CXX11_CONSTEXPR T
sqrt_unchecked_ct_2(T x, T s, T s2) HAMON_NOEXCEPT
{
	return !(s < s2) ?
		s2 :
		detail::sqrt_unchecked_ct_2(x, (x / s + s) / 2, s);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
sqrt_unchecked_ct_1(T x, T s) HAMON_NOEXCEPT
{
	return detail::sqrt_unchecked_ct_2(x, (x / s + s) / 2, s);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
sqrt_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return detail::sqrt_unchecked_ct_1(x, x > 1 ? x : T(1));
}

#endif

template <typename T>
HAMON_CXX11_CONSTEXPR T
sqrt_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::sqrt(x);
	}
#endif
	return sqrt_unchecked_ct(x);
}

#endif

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
sqrt_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		x < 0 ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(x) || hamon::iszero(x) ?
			x :
		sqrt_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	平方根を取得する
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの平方根を返す
 *
 *	arg が 0 よりも小さい場合、NaNを返す。
 *	arg が +∞ の場合、argをそのまま返す。
 *	arg が ±0 の場合、argをそのまま返す。
 *	arg が NaN の場合、NaNを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
sqrt(FloatType arg) HAMON_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
sqrt(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::sqrt_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
sqrtf(float arg) HAMON_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
sqrtl(long double arg) HAMON_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_SQRT_HPP
