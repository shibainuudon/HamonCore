/**
 *	@file	is_negative.hpp
 *
 *	@brief	is_negative 関数の定義
 */

#ifndef HAMON_CMATH_IS_NEGATIVE_HPP
#define HAMON_CMATH_IS_NEGATIVE_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/signed_integral.hpp>
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
is_negative_impl_2(FloatType x, hamon::detail::overload_priority<2>)
{
	return !hamon::isnan(x) && (x < 0);
}

template <HAMON_CONSTRAINED_PARAM(hamon::signed_integral, SignedType)>
inline HAMON_CXX11_CONSTEXPR bool
is_negative_impl_2(SignedType x, hamon::detail::overload_priority<1>)
{
	return x < 0;
}

template <typename UnsignedType>
inline HAMON_CXX11_CONSTEXPR bool
is_negative_impl_2(UnsignedType /*x*/, hamon::detail::overload_priority<0>)
{
	return false;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
is_negative_impl(T x) HAMON_NOEXCEPT
{
	return is_negative_impl_2(x, hamon::detail::overload_priority<2>{});
}

}	// namespace detail

/**
 *	@brief	負の値かどうか調べる
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	x < 0 ならtrue,そうでないならならfalse.
 *
 *	x が 0   の場合、falseを返す。
 *	x が NaN の場合、falseを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
is_negative(Arithmetic x) HAMON_NOEXCEPT
{
	return detail::is_negative_impl(x);
}

}	// namespace hamon

#endif // HAMON_CMATH_IS_NEGATIVE_HPP
