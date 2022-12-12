/**
 *	@file	round_half_even.hpp
 *
 *	@brief	round_half_even 関数の定義
 */

#ifndef HAMON_CMATH_ROUND_HALF_EVEN_HPP
#define HAMON_CMATH_ROUND_HALF_EVEN_HPP

#include <hamon/cmath/ceil.hpp>
#include <hamon/cmath/floor.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR T
round_half_even_unchecked(T x, T h = T(0.5)) HAMON_NOEXCEPT
{
	return hamon::ceil((x - h) * h) + hamon::floor((x + h) * h);
}

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
round_half_even_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isinf(x) || hamon::isnan(x) || hamon::iszero(x) ?
			x :
		round_half_even_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	最近接偶数への丸め
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	対象となる値
 *
 *	@return	xを最近接偶数へ丸めた値
 *
 *	x が ±∞ の場合、xをそのまま返す。
 *	x が ±0  の場合、xをそのまま返す。
 *	x が NaN  の場合、NaNを返す。
 *
 *	@note	端数が0.5より小さいなら切り捨て、
 *			端数が0.5より大きいならは切り上げ、
 *			端数がちょうど0.5なら切り捨てと切り上げのうち結果が偶数となる方へ丸める。
 *			多数のデータを丸めた値を足しあわせても、丸め誤差が特定の側に偏って累積しない。
 *			「偶数丸め」「最近接丸め」「JIS丸め」「ISO丸め」「銀行家の丸め」「銀行丸め」
 *			「五捨五入」「偶捨奇入」と呼ばれたりもする。
 *
 *	https://ja.wikipedia.org/wiki/%E7%AB%AF%E6%95%B0%E5%87%A6%E7%90%86#.E6.9C.80.E8.BF.91.E6.8E.A5.E5.81.B6.E6.95.B0.E3.81.B8.E3.81.AE.E4.B8.B8.E3.82.81
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic>
round_half_even(Arithmetic x)
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::round_half_even_impl(static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_ROUND_HALF_EVEN_HPP
