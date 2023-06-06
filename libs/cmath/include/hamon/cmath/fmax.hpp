/**
 *	@file	fmax.hpp
 *
 *	@brief	fmax 関数の定義
 */

#ifndef HAMON_CMATH_FMAX_HPP
#define HAMON_CMATH_FMAX_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CONSTEXPR float
fmax_unchecked(float x, float y) HAMON_NOEXCEPT
{
	return __builtin_fmaxf(x, y);
}

inline HAMON_CONSTEXPR double
fmax_unchecked(double x, double y) HAMON_NOEXCEPT
{
	return __builtin_fmax(x, y);
}

inline HAMON_CONSTEXPR long double
fmax_unchecked(long double x, long double y) HAMON_NOEXCEPT
{
	return __builtin_fmaxl(x, y);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
fmax_unchecked(T x, T y) HAMON_NOEXCEPT
{
	return x < y ? y : x;
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
fmax_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			y :
		hamon::isnan(y) ?
			x :
		fmax_unchecked(x, y);
}

}	// namespace detail

/**
 *	@brief	x と y のうち大きい方の値を返す
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x	算術型の値
 *	@param	y	算術型の値
 *
 *	@return	関数に成功すると、x と y のうち大きい方の値を返す
 *
 *	x が NaN の場合、y を返す。
 *	y が NaN の場合、x を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
inline HAMON_CXX11_CONSTEXPR FloatType
fmax(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::fmax_impl(x, y);
}

inline HAMON_CONSTEXPR float
fmaxf(float x, float y) HAMON_NOEXCEPT
{
	return detail::fmax_impl(x, y);
}

inline HAMON_CONSTEXPR long double
fmaxl(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::fmax_impl(x, y);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
fmax(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::fmax_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif // HAMON_CMATH_FMAX_HPP
