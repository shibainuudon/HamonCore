/**
 *	@file	radians_to_degrees.hpp
 *
 *	@brief	radians_to_degrees 関数の定義
 */

#ifndef HAMON_CMATH_RADIANS_TO_DEGREES_HPP
#define HAMON_CMATH_RADIANS_TO_DEGREES_HPP

#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR T
radians_to_degrees_unchecked(T x) HAMON_NOEXCEPT
{
	return x * 180 / hamon::numbers::pi_fn<T>();
}

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
radians_to_degrees_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isinf(x) || hamon::isnan(x) ?
			x :
		radians_to_degrees_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	ラジアン値をデグリー値に変換する
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	ラジアン値
 *
 *	@return	関数に成功すると、xをデグリー値に変換した値を返す
 *
 *	x が ±∞ の場合、±∞ を返す。
 *	x が NaN  の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic>
radians_to_degrees(Arithmetic x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::radians_to_degrees_impl(static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_RADIANS_TO_DEGREES_HPP
