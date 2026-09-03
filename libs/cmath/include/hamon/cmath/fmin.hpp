/**
 *	@file	fmin.hpp
 *
 *	@brief	fmin 関数の定義
 */

#ifndef HAMON_CMATH_FMIN_HPP
#define HAMON_CMATH_FMIN_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
fmin_unchecked_ct(T x, T y) HAMON_NOEXCEPT
{
	return x < y ? x : y;
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
fmin_unchecked_rt(T x, T y) HAMON_NOEXCEPT
{
	// TODO
	return std::fmin(x, y);
}

inline HAMON_CXX11_CONSTEXPR float
fmin_unchecked(float x, float y) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_fminf)
	return hamon::is_constant_evaluated() ? fmin_unchecked_ct(x, y) : __builtin_fminf(x, y);
#else
	return hamon::is_constant_evaluated() ? fmin_unchecked_ct(x, y) : fmin_unchecked_rt(x, y);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
fmin_unchecked(double x, double y) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_fmin)
	return hamon::is_constant_evaluated() ? fmin_unchecked_ct(x, y) : __builtin_fmin(x, y);
#else
	return hamon::is_constant_evaluated() ? fmin_unchecked_ct(x, y) : fmin_unchecked_rt(x, y);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
fmin_unchecked(long double x, long double y) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_fminl)
	return hamon::is_constant_evaluated() ? fmin_unchecked_ct(x, y) : __builtin_fminl(x, y);
#else
	return hamon::is_constant_evaluated() ? fmin_unchecked_ct(x, y) : fmin_unchecked_rt(x, y);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
fmin_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			y :
		hamon::isnan(y) ?
			x :
		fmin_unchecked(x, y);
}

}	// namespace detail

/**
 *	@brief	x と y のうち小さい方の値を返す
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x	算術型の値
 *	@param	y	算術型の値
 *
 *	@return	関数に成功すると、x と y のうち小さい方の値を返す
 *
 *	x が NaN の場合、y を返す。
 *	y が NaN の場合、x を返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
fmin(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::fmin_impl(x, y);
}

template <
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
fmin(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::fmin_impl(static_cast<type>(x), static_cast<type>(y));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
fminf(float x, float y) HAMON_NOEXCEPT
{
	return detail::fmin_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
fminl(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::fmin_impl(x, y);
}

}	// namespace hamon

#endif // HAMON_CMATH_FMIN_HPP
