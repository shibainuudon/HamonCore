/**
 *	@file	fdim.hpp
 *
 *	@brief	fdim 関数の定義
 */

#ifndef HAMON_CMATH_FDIM_HPP
#define HAMON_CMATH_FDIM_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/float_promote.hpp>
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
fdim_unchecked_ct(T x, T y) HAMON_NOEXCEPT
{
	return x > y ? x - y : T(0);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
fdim_unchecked_rt(T x, T y) HAMON_NOEXCEPT
{
	// TODO
	return std::fdim(x, y);
}

inline HAMON_CXX11_CONSTEXPR float
fdim_unchecked(float x, float y) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_fdimf(x, y);
#elif HAMON_HAS_BUILTIN(__builtin_fdimf)
	return hamon::is_constant_evaluated() ? fdim_unchecked_ct(x, y) : __builtin_fdimf(x, y);
#else
	return hamon::is_constant_evaluated() ? fdim_unchecked_ct(x, y) : fdim_unchecked_rt(x, y);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
fdim_unchecked(double x, double y) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_fdim(x, y);
#elif HAMON_HAS_BUILTIN(__builtin_fdim)
	return hamon::is_constant_evaluated() ? fdim_unchecked_ct(x, y) : __builtin_fdim(x, y);
#else
	return hamon::is_constant_evaluated() ? fdim_unchecked_ct(x, y) : fdim_unchecked_rt(x, y);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
fdim_unchecked(long double x, long double y) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_fdiml(x, y);
#elif HAMON_HAS_BUILTIN(__builtin_fdiml)
	return hamon::is_constant_evaluated() ? fdim_unchecked_ct(x, y) : __builtin_fdiml(x, y);
#else
	return hamon::is_constant_evaluated() ? fdim_unchecked_ct(x, y) : fdim_unchecked_rt(x, y);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
fdim_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	FloatType const inf = hamon::numeric_limits<FloatType>::infinity();
	return
		hamon::isnan(x) || hamon::isnan(y) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		x == inf ?
			y == inf ?
				FloatType(0) :
			inf :
		x == -inf ?
			FloatType(0) :
		y == inf ?
			FloatType(0) :
		y == -inf ?
			inf :
		fdim_unchecked(x, y);
}

}	// namespace detail

/**
 *	@brief	正の差分を求める
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return	引数 x と引数 y の正の差分を返す。
 *
 *	x > y の場合、x - y を返す。
 *	x <= y の場合、+0 を返す。
 *	x と y のどちらか一方でもNaNの場合、NaNを返す
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
fdim(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::fdim_impl(x, y);
}

template <
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
fdim(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::fdim_impl(static_cast<type>(x), static_cast<type>(y));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
fdimf(float x, float y) HAMON_NOEXCEPT
{
	return detail::fdim_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
fdiml(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::fdim_impl(x, y);
}

}	// namespace hamon

#endif // HAMON_CMATH_FDIM_HPP
