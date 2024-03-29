﻿/**
 *	@file	cos.hpp
 *
 *	@brief	cos 関数の定義
 */

#ifndef HAMON_CMATH_COS_HPP
#define HAMON_CMATH_COS_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/factorial.hpp>
#include <hamon/cmath/fmod.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/numbers/pi.hpp>
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
cos_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_cosf(x);
}

inline HAMON_CXX11_CONSTEXPR double
cos_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_cos(x);
}

inline HAMON_CXX11_CONSTEXPR long double
cos_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_cosl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
cos_unchecked_ct_1(T x2, unsigned int n, unsigned int last) HAMON_NOEXCEPT
{
	return
		last - n == 1 ?
			(n % 2 ? -1 : 1) * pow_n(x2, n) / unchecked_factorial<T>(2 * n) :
			cos_unchecked_ct_1(x2, n, n + (last - n) / 2) +
			cos_unchecked_ct_1(x2, n + (last - n) / 2, last);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
cos_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return T(1) + cos_unchecked_ct_1(
		pow2(hamon::fmod(x, hamon::numbers::pi_fn<T>() * 2)),
		1, max_factorial<T>() / 2 + 1);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
cos_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::cos(x);
	}
#endif
	return cos_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
cos_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			FloatType(1) :
		hamon::isinf(x) || hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
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
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
cos(FloatType arg) HAMON_NOEXCEPT
{
	return detail::cos_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
cosf(float arg) HAMON_NOEXCEPT
{
	return detail::cos_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
cosl(long double arg) HAMON_NOEXCEPT
{
	return detail::cos_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
cos(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::cos_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_COS_HPP
