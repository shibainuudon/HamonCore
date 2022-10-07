/**
 *	@file	degrees_to_radians.hpp
 *
 *	@brief	degrees_to_radians 関数の定義
 */

#ifndef HAMON_CMATH_DEGREES_TO_RADIANS_HPP
#define HAMON_CMATH_DEGREES_TO_RADIANS_HPP

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
degrees_to_radians_unchecked(T x) HAMON_NOEXCEPT
{
	return x * hamon::numbers::pi_fn<T>() / 180;
}

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
degrees_to_radians_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isinf(x) || hamon::isnan(x) ?
			x :
		degrees_to_radians_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	デグリー値をラジアン値に変換する
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	デグリー値
 *
 *	@return	関数に成功すると、xをラジアン値に変換した値を返す
 *
 *	x が ±∞ の場合、±∞ を返す。
 *	x が NaN  の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic>
degrees_to_radians(Arithmetic x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::degrees_to_radians_impl(static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_DEGREES_TO_RADIANS_HPP
