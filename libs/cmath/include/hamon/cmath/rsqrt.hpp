/**
 *	@file	rsqrt.hpp
 *
 *	@brief	rsqrt 関数の定義
 */

#ifndef HAMON_CMATH_RSQRT_HPP
#define HAMON_CMATH_RSQRT_HPP

#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
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
rsqrt_unchecked(T x) HAMON_NOEXCEPT
{
	return T(1) / hamon::detail::sqrt_unchecked(x);
}

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
rsqrt_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		x < 0 ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(x) ?
			FloatType(0) :
		hamon::iszero(x) ?
			std::numeric_limits<FloatType>::infinity() :
		rsqrt_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	平方根の逆数を取得する
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの平方根の逆数を返す
 *
 *	x が 0 よりも小さい場合、NaN を返す。
 *	x が +∞ の場合、+0   を返す。
 *	x が ±0 の場合、±∞ を返す。
 *	x が NaN の場合、NaN  を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic>
rsqrt(Arithmetic x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::rsqrt_impl(static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_RSQRT_HPP
