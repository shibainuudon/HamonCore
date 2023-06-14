/**
 *	@file	is_integer.hpp
 *
 *	@brief	is_integer 関数の定義
 */

#ifndef HAMON_CMATH_IS_INTEGER_HPP
#define HAMON_CMATH_IS_INTEGER_HPP

#include <hamon/cmath/isfinite.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatingPoint)>
inline HAMON_CXX11_CONSTEXPR bool
is_integer_impl_1(FloatingPoint x, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	return hamon::isfinite(x) && (hamon::trunc(x) == x);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integral)>
inline HAMON_CXX11_CONSTEXPR bool
is_integer_impl_1(Integral, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	return true;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
is_integer_impl(T x) HAMON_NOEXCEPT
{
	return is_integer_impl_1(x, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

/**
 *	@brief	整数かどうか調べる
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが整数ならtrue,そうでないならならfalse.
 *
 *	x が NaN または ±∞ の場合、falseを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
is_integer(Arithmetic x) HAMON_NOEXCEPT
{
	return detail::is_integer_impl(x);
}

}	// namespace hamon

#endif // HAMON_CMATH_IS_INTEGER_HPP
