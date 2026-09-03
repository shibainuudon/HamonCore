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
#include <hamon/cmath/cos.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
sin_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return -cos_unchecked(x + hamon::numbers::pi_v<T> / 2);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
sin_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::sin(x);
}

inline HAMON_CXX11_CONSTEXPR float
sin_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_sinf(x);
#elif HAMON_HAS_BUILTIN(__builtin_sinf)
	return hamon::is_constant_evaluated() ? sin_unchecked_ct(x) : __builtin_sinf(x);
#else
	return hamon::is_constant_evaluated() ? sin_unchecked_ct(x) : sin_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
sin_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_sin(x);
#elif HAMON_HAS_BUILTIN(__builtin_sin)
	return hamon::is_constant_evaluated() ? sin_unchecked_ct(x) : __builtin_sin(x);
#else
	return hamon::is_constant_evaluated() ? sin_unchecked_ct(x) : sin_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
sin_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_sinl(x);
#elif HAMON_HAS_BUILTIN(__builtin_sinl)
	return hamon::is_constant_evaluated() ? sin_unchecked_ct(x) : __builtin_sinl(x);
#else
	return hamon::is_constant_evaluated() ? sin_unchecked_ct(x) : sin_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
sin_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			x :
		hamon::isinf(x) || hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
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
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
sin(FloatType arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
sinf(float arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
sinl(long double arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
sin(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_SIN_HPP
