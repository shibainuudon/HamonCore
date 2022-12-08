/**
 *	@file	pow.hpp
 *
 *	@brief	pow 関数の定義
 */

#ifndef HAMON_CMATH_POW_HPP
#define HAMON_CMATH_POW_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isfinite.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/is_odd.hpp>
#include <hamon/cmath/is_integer.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/copysign.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
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
pow_unchecked(float x, float y) HAMON_NOEXCEPT
{
	return __builtin_powf(x, y);
}

inline HAMON_CONSTEXPR double
pow_unchecked(double x, double y) HAMON_NOEXCEPT
{
	return __builtin_pow(x, y);
}

inline HAMON_CONSTEXPR long double
pow_unchecked(long double x, long double y) HAMON_NOEXCEPT
{
	return __builtin_powl(x, y);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
pow_unchecked_ct(T x, T y)
{
	return
		!(x < 0) ?
			 hamon::exp(y * hamon::log( x)) :
		hamon::is_odd(y) ?
			-hamon::exp(y * hamon::log(-x)) :
			 hamon::exp(y * hamon::log(-x));
}

template <typename T>
inline HAMON_CONSTEXPR T
pow_unchecked(T x, T y) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::pow(x, y);
	}
#endif
	return pow_unchecked_ct(x, y);
}

#endif

template <typename T>
inline HAMON_CONSTEXPR T
pow_impl_2(T x, T y, T inf, T nan) HAMON_NOEXCEPT
{
	//pow(+0, exp), where exp is a negative odd integer, returns +∞ and raises FE_DIVBYZERO
	//pow(-0, exp), where exp is a negative odd integer, returns -∞ and raises FE_DIVBYZERO
	//pow(±0, exp), where exp is negative, finite, and is an even integer or a non-integer, returns +∞ and raises FE_DIVBYZERO
	//pow(±0, -∞) returns +∞ and may raise FE_DIVBYZERO
	//pow(+0, exp), where exp is a positive odd integer, returns +0
	//pow(-0, exp), where exp is a positive odd integer, returns -0
	//pow(±0, exp), where exp is positive non-integer or a positive even integer, returns +0
	//pow(-1, ±∞) returns 1
	//pow(+1, exp) returns 1 for any exp, even when exp is NaN
	//pow(base, ±0) returns 1 for any base, even when base is NaN
	//pow(base, exp) returns NaN and raises FE_INVALID if base is finite and negative and exp is finite and non-integer.
	//pow(base, -∞) returns +∞ for any |base|<1
	//pow(base, -∞) returns +0 for any |base|>1
	//pow(base, +∞) returns +0 for any |base|<1
	//pow(base, +∞) returns +∞ for any |base|>1
	//pow(-∞, exp) returns -0 if exp is a negative odd integer
	//pow(-∞, exp) returns +0 if exp is a negative non-integer or even integer
	//pow(-∞, exp) returns -∞ if exp is a positive odd integer
	//pow(-∞, exp) returns +∞ if exp is a positive non-integer or even integer
	//pow(+∞, exp) returns +0 for any negative exp
	//pow(+∞, exp) returns +∞ for any positive exp
	//except where specified above, if any argument is NaN, NaN is returned

	return
		hamon::iszero(x) ?
			hamon::signbit(y) ?
				hamon::is_odd(y) ?
					hamon::copysign(inf, x) :
				inf :
			hamon::is_odd(y) ?
				x :
			T(0) :
		x == T(-1) && hamon::isinf(y) ?
			T(1) :
		x == T(1) ?
			T(1) :
		hamon::iszero(y) ?
			T(1) :
		hamon::isfinite(x) && hamon::signbit(x) && hamon::isfinite(y) && !hamon::is_integer(y) ?
			nan :
		hamon::isinf(y) ?
			hamon::signbit(y) ?
				hamon::fabs(x) < T(1) ?
					inf :
				T(0) :
			hamon::fabs(x) < T(1) ?
				T(0) :
			inf :
		hamon::isinf(x) ?
			hamon::signbit(x) ?
				hamon::signbit(y) ?
					hamon::is_odd(y) ?
						-T(0) :
					T(0) :
				hamon::is_odd(y) ?
					-inf :
				inf :
			hamon::signbit(y) ?
				T(0) :
			inf :
		hamon::isnan(x) || hamon::isnan(y) ?
			nan :
		pow_unchecked(x, y);
}

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
pow_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return pow_impl_2(x, y,
		std::numeric_limits<FloatType>::infinity(),
		std::numeric_limits<FloatType>::quiet_NaN());
}

}	// namespace detail

/**
 *	@brief	x の y 乗を求める。
 *
 *	@param	x
 *	@param	y
 *
 *	@return	x を y 乗した値を返す。
 *
 *	x が ±0 かつ、y が0より小さい奇数の場合、±∞ を返す。
 *	x が ±0 かつ、y が0より小さい有限の値で偶数または非整数の場合、+∞ を返す。
 *	x が ±0 かつ、y が -∞ の場合、+∞ を返す。
 *	x が ±0 かつ、y が0より大きい奇数の場合、±0 を返す。
 *	x が ±0 かつ、y が0より大きい偶数または非整数の場合、+0 を返す。
 *	x が -1  かつ、y が ±∞ の場合、1 を返す。
 *	x が +1  の場合、1 を返す。
 *	y が ±0 の場合、1 を返す。
 *	x が0より小さい有限の値かつ、yが有限で非整数の場合、NaNを返す。
 *	|x| < 1 かつ、y が -∞ の場合、+∞ を返す。
 *	|x| > 1 かつ、y が -∞ の場合、+0 を返す。
 *	|x| < 1 かつ、y が +∞ の場合、+0 を返す。
 *	|x| > 1 かつ、y が +∞ の場合、+∞ を返す。
 *	x が -∞ かつ、y が負の奇数の場合、            -0 を返す。
 *	x が -∞ かつ、y が負の偶数または非整数の場合、+0 を返す。
 *	x が -∞ かつ、y が正の奇数の場合、            -∞ を返す。
 *	x が -∞ かつ、y が正の偶数または非整数の場合、+∞ を返す。
 *	x が +∞ かつ、y が負の値の場合、+0  を返す。
 *	x が +∞ かつ、y が正の値の場合、+∞ を返す。
 *	上記以外で、xかyの少なくともどちらかがNaNの場合、NaNを返す。
 */
inline HAMON_CONSTEXPR float
pow(float x, float y) HAMON_NOEXCEPT
{
	return detail::pow_impl(x, y);
}

inline HAMON_CONSTEXPR float
powf(float x, float y) HAMON_NOEXCEPT
{
	return detail::pow_impl(x, y);
}

inline HAMON_CONSTEXPR double
pow(double x, double y) HAMON_NOEXCEPT
{
	return detail::pow_impl(x, y);
}

inline HAMON_CONSTEXPR long double
pow(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::pow_impl(x, y);
}

inline HAMON_CONSTEXPR long double
powl(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::pow_impl(x, y);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
pow(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::pow_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif // HAMON_CMATH_POW_HPP
