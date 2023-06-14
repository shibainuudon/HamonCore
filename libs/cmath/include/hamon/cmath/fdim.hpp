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
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
fdim_unchecked(float x, float y) HAMON_NOEXCEPT
{
	return __builtin_fdimf(x, y);
}

inline HAMON_CXX11_CONSTEXPR double
fdim_unchecked(double x, double y) HAMON_NOEXCEPT
{
	return __builtin_fdim(x, y);
}

inline HAMON_CXX11_CONSTEXPR long double
fdim_unchecked(long double x, long double y) HAMON_NOEXCEPT
{
	return __builtin_fdiml(x, y);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
fdim_unchecked(T x, T y) HAMON_NOEXCEPT
{
	return x > y ? x - y : T(0);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
fdim_impl_2(FloatType x, FloatType y, FloatType inf) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) || hamon::isnan(y) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
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

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
fdim_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return fdim_impl_2(x, y, std::numeric_limits<FloatType>::infinity());
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
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
fdim(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::fdim_impl(x, y);
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

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
fdim(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::fdim_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif // HAMON_CMATH_FDIM_HPP
