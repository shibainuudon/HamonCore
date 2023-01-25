/**
 *	@file	isnormal.hpp
 *
 *	@brief	isnormal 関数の定義
 */

#ifndef HAMON_CMATH_ISNORMAL_HPP
#define HAMON_CMATH_ISNORMAL_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/issubnormal.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
inline HAMON_CONSTEXPR bool
isnormal_impl(FloatType x) HAMON_NOEXCEPT
{
#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isnormal(x);
#else
	return
		!hamon::iszero(x)      &&
		!hamon::issubnormal(x) &&
		!hamon::isinf(x)       &&
		!hamon::isnan(x);
#endif
}

}	// namespace detail

/**
 *	@brief	正規化数かどうか調べる
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが正規化数ならtrue,そうでないならfalse.
 *
 *	正規化数とは以下の条件を全て満たす数のこと:
 *	・ゼロでない
 *	・非正規化数でない
 *	・無限大でない
 *	・NaNでない
 *
 *	@note	ArithmeticTypeが整数型のときはdoubleにキャストしてから調べる。
 */
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isnormal(float arg) HAMON_NOEXCEPT
{
	return detail::isnormal_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isnormal(double arg) HAMON_NOEXCEPT
{
	return detail::isnormal_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isnormal(long double arg) HAMON_NOEXCEPT
{
	return detail::isnormal_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isnormal(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::isnormal_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISNORMAL_HPP
