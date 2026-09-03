/**
 *	@file	cbrt.hpp
 *
 *	@brief	cbrt 関数の定義
 */

#ifndef HAMON_CMATH_CBRT_HPP
#define HAMON_CMATH_CBRT_HPP

#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/pow.hpp>
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
cbrt_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T const third = T(1) / T(3);
	return x < 0 ?
		-hamon::pow(-x, third) :
		 hamon::pow( x, third);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
cbrt_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::cbrt(x);
}

inline HAMON_CXX11_CONSTEXPR float
cbrt_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_cbrtf(x);
#elif HAMON_HAS_BUILTIN(__builtin_cbrtf)
	return hamon::is_constant_evaluated() ? cbrt_unchecked_ct(x) : __builtin_cbrtf(x);
#else
	return hamon::is_constant_evaluated() ? cbrt_unchecked_ct(x) : cbrt_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
cbrt_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_cbrt(x);
#elif HAMON_HAS_BUILTIN(__builtin_cbrt)
	return hamon::is_constant_evaluated() ? cbrt_unchecked_ct(x) : __builtin_cbrt(x);
#else
	return hamon::is_constant_evaluated() ? cbrt_unchecked_ct(x) : cbrt_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
cbrt_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_cbrtl(x);
#elif HAMON_HAS_BUILTIN(__builtin_cbrtl)
	return hamon::is_constant_evaluated() ? cbrt_unchecked_ct(x) : __builtin_cbrtl(x);
#else
	return hamon::is_constant_evaluated() ? cbrt_unchecked_ct(x) : cbrt_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
cbrt_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isinf(x) || hamon::iszero(x) ?
			x :
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		cbrt_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	立方根を取得する
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの立方根を返す
 *
 *	x が ±∞ の場合、xをそのまま返す。
 *	x が ±0 の場合、xをそのまま返す。
 *	x が NaN の場合、NaNを返す。
 *
 *	@note	cbrt(x) は pow(x, 1.0 / 3.0) と違い、
 *			xが負の値でも立方根を計算できる。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
cbrt(FloatType arg) HAMON_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
cbrtf(float arg) HAMON_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
cbrtl(long double arg) HAMON_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
cbrt(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::cbrt_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_CBRT_HPP
