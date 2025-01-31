/**
 *	@file	remainder.hpp
 *
 *	@brief	remainder 関数の定義
 */

#ifndef HAMON_CMATH_REMAINDER_HPP
#define HAMON_CMATH_REMAINDER_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::remainder;
using std::remainderf;
using std::remainderl;

}	// namespace hamon

#else

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/round_half_even.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
remainder_unchecked(float x, float y) HAMON_NOEXCEPT
{
	return __builtin_remainderf(x, y);
}

inline HAMON_CXX11_CONSTEXPR double
remainder_unchecked(double x, double y) HAMON_NOEXCEPT
{
	return __builtin_remainder(x, y);
}

inline HAMON_CXX11_CONSTEXPR long double
remainder_unchecked(long double x, long double y) HAMON_NOEXCEPT
{
	return __builtin_remainderl(x, y);
}

#else

template <typename T>
HAMON_CXX11_CONSTEXPR T
remainder_unchecked(T x, T y) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::remainder(x, y);
	}
#endif
	return x - (hamon::round_half_even(x / y) * y);
}

#endif

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
remainder_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ||
		hamon::isnan(y) ||
		hamon::isinf(x) ||
		hamon::iszero(y) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		remainder_unchecked(x, y);
}

}	// namespace detail

/**
 *	@brief	剰余を求めます
 *
 *	@param	x
 *	@param	y
 *
 *	@return	x / y の余り
 *
 *	remainder関数はxをyで割った余りを計算する。
 *	返り値は x - n * y である。
 *	ここで n は x / y の値を最も近い整数に丸めたものである。
 *	n - x / y の絶対値が0.5の場合、偶数になるようにnが選ばれる。
 *
 *	fmod関数と違い、戻り値の符号はxと同じになるとは限らない。
 *	ただし戻り値が0の場合、xと同じ符号になる。
 *
 *	x が ±∞ かつ、y が NaN でない場合、NaN を返す。
 *	y が ±0  かつ、x が NaN でない場合、NaN を返す。
 *	x か y がNaNの場合、NaNを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
remainder(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::remainder_impl(x, y);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
remainder(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::remainder_impl(static_cast<type>(x), static_cast<type>(y));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
remainderf(float x, float y) HAMON_NOEXCEPT
{
	return detail::remainder_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
remainderl(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::remainder_impl(x, y);
}

}	// namespace hamon

#endif

#endif // HAMON_CMATH_REMAINDER_HPP
