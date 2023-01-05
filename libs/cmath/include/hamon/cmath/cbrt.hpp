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
cbrt_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_cbrtf(x);
}

inline HAMON_CONSTEXPR double
cbrt_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_cbrt(x);
}

inline HAMON_CONSTEXPR long double
cbrt_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_cbrtl(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
cbrt_unchecked_ct_1(T x, T third) HAMON_NOEXCEPT
{
	return x < 0 ?
		-hamon::pow(-x, third) :
		 hamon::pow( x, third);
}

template <typename T>
inline HAMON_CONSTEXPR T
cbrt_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return cbrt_unchecked_ct_1(x, T(1) / T(3));
}

template <typename T>
inline HAMON_CONSTEXPR T
cbrt_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::cbrt(x);
	}
#endif
	return cbrt_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
cbrt_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isinf(x) || hamon::iszero(x) ?
			x :
		hamon::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
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
HAMON_NODISCARD inline HAMON_CONSTEXPR float
cbrt(float arg) HAMON_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR float
cbrtf(float arg) HAMON_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR double
cbrt(double arg) HAMON_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
cbrt(long double arg) HAMON_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
cbrtl(long double arg) HAMON_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR double
cbrt(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::cbrt_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_CBRT_HPP
