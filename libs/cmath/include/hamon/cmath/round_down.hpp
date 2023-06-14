/**
 *	@file	round_down.hpp
 *
 *	@brief	round_down 関数の定義
 */

#ifndef HAMON_CMATH_ROUND_DOWN_HPP
#define HAMON_CMATH_ROUND_DOWN_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/floor.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
round_down_unchecked(T x, T base) HAMON_NOEXCEPT
{
	return hamon::floor(x / base) * base;
}

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
round_down_impl(FloatType x, FloatType base) HAMON_NOEXCEPT
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
		round_down_unchecked(x, base);
}

}	// namespace detail

/**
 *	@brief	切り下げ
 *
 *	@tparam	Arithmetic1	算術型
 *	@tparam	Arithmetic2	算術型
 *
 *	@param	x		切り下げる数
 *	@param	base	基数
 *
 *	@return	xをbaseの倍数に切り下げた値
 *
 *	xをbaseの倍数に切り下げた値を取得します。
 *	正確に言うと
 *	a % base = 0 (a <= x) となる最大の整数aを取得します。
 *
 *	base が NaN  の場合、NaN  を返す。
 *	x が NaN     の場合、NaN  を返す。
 *	base が ±∞ の場合、±∞ を返す。
 *	x が ±∞    の場合、±∞ を返す。
 *	base == 0　  の場合、x    を返す。
 */
template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR Arithmetic1
round_down(Arithmetic1 x, Arithmetic2 base) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return static_cast<Arithmetic1>(
		detail::round_down_impl(static_cast<type>(x), static_cast<type>(base)));
}

}	// namespace hamon

#endif // HAMON_CMATH_ROUND_DOWN_HPP
