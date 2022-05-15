﻿/**
 *	@file	round_up.hpp
 *
 *	@brief	round_up
 */

#ifndef HAMON_CMATH_ROUND_UP_HPP
#define HAMON_CMATH_ROUND_UP_HPP

#include <hamon/cmath/ceil.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>
#include <limits>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
round_up_impl(FloatType x, FloatType base) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) || hamon::isnan(base) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(base) ?
			base :
		hamon::isinf(x) ?
			x :
		base == 0 ?
			x :
		hamon::ceil(x / base) * base;
}

}	// namespace detail

/**
 *	@brief	切り上げ
 *
 *	@tparam	Arithmetic1	算術型
 *	@tparam	Arithmetic2	算術型
 *
 *	@param	x		切り上げる数
 *	@param	base	基数
 *
 *	@return	xをbaseの倍数に切り上げた値
 *
 *	xをbaseの倍数に切り上げた値を取得します。
 *	正確に言うと
 *	a % base = 0 (a >= x) となる最小の整数aを取得します。
 *
 *	base が NaN  の場合、NaN  を返す。
 *	x が NaN     の場合、NaN  を返す。
 *	base が ±∞ の場合、±∞ を返す。
 *	x が ±∞    の場合、±∞ を返す。
 *	base == 0　  の場合、x    を返す。
 */
template <
	typename Arithmetic1,
	typename Arithmetic2,
	typename = typename std::enable_if<
		std::is_arithmetic<Arithmetic1>::value &&
		std::is_arithmetic<Arithmetic2>::value
	>::type
>
inline HAMON_CONSTEXPR Arithmetic1
round_up(Arithmetic1 x, Arithmetic2 base) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return static_cast<Arithmetic1>(
		detail::round_up_impl(static_cast<type>(x), static_cast<type>(base)));
}

}	// namespace hamon

#endif // HAMON_CMATH_ROUND_UP_HPP