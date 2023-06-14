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
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
isnormal(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::isnormal_impl(static_cast<type>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISNORMAL_HPP
