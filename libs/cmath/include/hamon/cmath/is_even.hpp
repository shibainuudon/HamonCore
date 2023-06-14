/**
 *	@file	is_even.hpp
 *
 *	@brief	is_even 関数の定義
 */

#ifndef HAMON_CMATH_IS_EVEN_HPP
#define HAMON_CMATH_IS_EVEN_HPP

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
is_even_impl(FloatType x) HAMON_NOEXCEPT
{
	return hamon::fmod(hamon::fabs(x), FloatType(2)) == FloatType(0);
}

}	// namespace detail

/**
 *	@brief	偶数かどうか調べる
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが偶数ならtrue,そうでないならならfalse.
 *
 *	x が NaN または ±∞ の場合、falseを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
is_even(Arithmetic x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::is_even_impl(static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_IS_EVEN_HPP
