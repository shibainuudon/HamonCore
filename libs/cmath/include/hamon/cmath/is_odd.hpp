/**
 *	@file	is_odd.hpp
 *
 *	@brief	is_odd 関数の定義
 */

#ifndef HAMON_CMATH_IS_ODD_HPP
#define HAMON_CMATH_IS_ODD_HPP

#include <hamon/cmath/fmod.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR bool
is_odd_impl(FloatType x) HAMON_NOEXCEPT
{
	return hamon::fmod(hamon::fabs(x), FloatType(2)) == FloatType(1);
}

}	// namespace detail

/**
 *	@brief	奇数かどうか調べる
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが奇数ならtrue,そうでないならならfalse.
 *
 *	x が NaN または ±∞ の場合、falseを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
is_odd(Arithmetic x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::is_odd_impl(static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_IS_ODD_HPP
