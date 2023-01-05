/**
 *	@file	smoothstep.hpp
 *
 *	@brief	smoothstep 関数の定義
 */

#ifndef HAMON_CMATH_SMOOTHSTEP_HPP
#define HAMON_CMATH_SMOOTHSTEP_HPP

#include <hamon/cmath/saturate.hpp>
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
smoothstep_uncheck_1(T t) HAMON_NOEXCEPT
{
	return t * t * (T(3) - (T(2) * t));
}

template <typename T>
inline HAMON_CONSTEXPR T
smoothstep_uncheck(T from, T to, T x) HAMON_NOEXCEPT
{
	return smoothstep_uncheck_1(hamon::saturate((x - from) / (to - from)));
}

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
smoothstep_impl(FloatType from, FloatType to, FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(from) || hamon::isnan(to) || hamon::isnan(x) || from > to ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		x >= to ?
			FloatType(1) :
		x <= from ?
			FloatType(0) :
		from == to ?
			FloatType(1) :
		hamon::isinf(from) && hamon::isinf(to) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(from) ?
			FloatType(1) :
		hamon::isinf(to) ?
			FloatType(0) :
		smoothstep_uncheck(from, to, x);
}

}	// namespace detail

/**
 *	@brief	smoothstep
 *
 *	@tparam		Arithmetic1	算術型
 *	@tparam		Arithmetic2	算術型
 *	@tparam		Arithmetic3	算術型
 *
 *	@param	from	xの最小値
 *	@param	to		xの最大値
 *	@param	x		補間対象の値
 *
 *	@return	fromとtoの間をエルミート補間した値を返す。
 *
 *	from, to, x のうち少なくとも1つがNaNの場合、NaNを返す。
 *	from > to の場合、NaNを返す。
 *	x >= to の場合、1を返す。
 *	x <= from の場合、0を返す。
 *	from = to の場合、1を返す。
 *	fromとtoの両方が±∞の場合、NaNを返す。
 *	fromが±∞の場合、1を返す。
 *	toが±∞の場合、0を返す。
 */
template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic3)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>
smoothstep(Arithmetic1 from, Arithmetic2 to, Arithmetic3 x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>;
	return detail::smoothstep_impl(static_cast<type>(from), static_cast<type>(to), static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_SMOOTHSTEP_HPP
