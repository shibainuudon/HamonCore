/**
 *	@file	saturate.hpp
 *
 *	@brief	saturate 関数の定義
 */

#ifndef HAMON_CMATH_SATURATE_HPP
#define HAMON_CMATH_SATURATE_HPP

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

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
saturate_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		(x < FloatType(0)) ?
			FloatType(0) :
		(FloatType(1) < x) ?
			FloatType(1) :
		x;
}

}	// namespace detail

/**
 *	@brief	値を0以上1以下の範囲に丸めます
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	対象となる値
 *
 *	@return	x < 0なら0, x > 1なら1, さもなくばx
 *
 *	x が NaN の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic>
saturate(Arithmetic x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::saturate_impl(static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_SATURATE_HPP
