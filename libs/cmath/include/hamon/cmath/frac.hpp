/**
 *	@file	frac.hpp
 *
 *	@brief	frac 関数の定義
 */

#ifndef HAMON_CMATH_FRAC_HPP
#define HAMON_CMATH_FRAC_HPP

#include <hamon/cmath/floor.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR T
frac_unchecked(T x) HAMON_NOEXCEPT
{
	return x - hamon::floor(x);
}

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatingPoint)>
inline HAMON_CONSTEXPR FloatingPoint
frac_impl(FloatingPoint x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			std::numeric_limits<FloatingPoint>::quiet_NaN() :
		hamon::isinf(x) ?
			FloatingPoint(0) :
		frac_unchecked(x);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::integral, Integral),
	typename Promoted = hamon::float_promote_t<Integral>
>
inline HAMON_CONSTEXPR Promoted
frac_impl(Integral) HAMON_NOEXCEPT
{
	return Promoted(0);
}

}	// namespace detail

/**
 *	@brief	小数部を求める
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの小数部（常に正）を返す
 *
 *	x が ±∞の場合、+0  を返す。
 *	x が NaN の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic>
frac(Arithmetic x) HAMON_NOEXCEPT
{
	return detail::frac_impl(x);
}

}	// namespace hamon

#endif // HAMON_CMATH_FRAC_HPP
