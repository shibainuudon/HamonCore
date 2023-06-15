/**
 *	@file	is_positive.hpp
 *
 *	@brief	is_positive 関数の定義
 */

#ifndef HAMON_CMATH_IS_POSITIVE_HPP
#define HAMON_CMATH_IS_POSITIVE_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
inline HAMON_CXX11_CONSTEXPR bool
is_positive_impl_2(FloatType x, hamon::detail::overload_priority<1>)
{
	return !hamon::isnan(x) && (x > 0);
}

template <typename IntegralType>
inline HAMON_CXX11_CONSTEXPR bool
is_positive_impl_2(IntegralType x, hamon::detail::overload_priority<0>)
{
	return x > 0;
}

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR bool
is_positive_impl(FloatType x) HAMON_NOEXCEPT
{
	return is_positive_impl_2(x, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

/**
 *	@brief	正の値かどうか調べる
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	x > 0 ならtrue,そうでないならならfalse.
 *
 *	x が 0   の場合、falseを返す。
 *	x が NaN の場合、falseを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
is_positive(Arithmetic x) HAMON_NOEXCEPT
{
	return detail::is_positive_impl(x);
}

}	// namespace hamon

#endif // HAMON_CMATH_IS_POSITIVE_HPP
