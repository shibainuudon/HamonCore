/**
 *	@file	repeat.hpp
 *
 *	@brief	repeat 関数の定義
 */

#ifndef HAMON_CMATH_REPEAT_HPP
#define HAMON_CMATH_REPEAT_HPP

#include <hamon/cmath/floor.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
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
inline HAMON_CONSTEXPR T
repeat_unchecked(T t, T length) HAMON_NOEXCEPT
{
	return t - hamon::floor(t / length) * length;
}

template <typename T>
inline HAMON_CONSTEXPR T
repeat_unchecked(T x, T min, T max) HAMON_NOEXCEPT
{
	return min + repeat_unchecked(x - min, max - min);
}

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
repeat_impl(FloatType x, FloatType min, FloatType max) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) || hamon::isnan(min) || hamon::isnan(max) ||
		hamon::isinf(x) || hamon::isinf(min) || hamon::isinf(max) ||
		min > max ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		min == max ?
			min :
		repeat_unchecked(x, min, max);
}

}	// namespace detail

/**
 *	@brief		回り込み処理
 *
 *	@tparam		Arithmetic1
 *	@tparam		Arithmetic2
 *	@tparam		Arithmetic3
 *
 *	@param		x	対象となる値
 *	@param		min	最小値
 *	@param		max	最大値
 *
 *	@return		x を min 以上 max 未満の範囲で回り込み処理をした値
 *
 *	x, min, max のどれか1つでも NaN  の場合、NaN を返す。
 *	x, min, max のどれか1つでも ±∞ の場合、NaN を返す。
 *	min > max の場合、NaN を返す。
 *	min == max の場合、min を返す。
 */
template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic3)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>
repeat(Arithmetic1 x, Arithmetic2 min, Arithmetic3 max) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>;

	return detail::repeat_impl(
		static_cast<type>(x),
		static_cast<type>(min),
		static_cast<type>(max));
}

}	// namespace hamon

#endif // HAMON_CMATH_REPEAT_HPP
