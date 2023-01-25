/**
 *	@file	issubnormal.hpp
 *
 *	@brief	issubnormal 関数の定義
 */

#ifndef HAMON_CMATH_ISSUBNORMAL_HPP
#define HAMON_CMATH_ISSUBNORMAL_HPP

#include <cmath>
#if defined(issubnormal)
#undef issubnormal
#endif

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
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
inline HAMON_CONSTEXPR bool
issubnormal_or_zero(T x) HAMON_NOEXCEPT
{
	return
		x > 0 ?
			x <  (std::numeric_limits<T>::min)():
			x > -(std::numeric_limits<T>::min)();
}

template <typename FloatType>
inline HAMON_CONSTEXPR bool
issubnormal_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		!hamon::isnan(x) &&
		!hamon::iszero(x) &&
		issubnormal_or_zero(x);
}

}	// namespace detail

/**
 *	@brief	非正規化数かどうか調べる
 *
 *	@param	x	調べる値
 *
 *	@return	xが非正規化数ならtrue,そうでないならfalse.
 *
 *	非正規化数とは何かの説明は、長くなるのでここには書かない。
 *
 *	@note	xが整数型のときはdoubleにキャストしてから調べる。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
issubnormal(Arithmetic x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::issubnormal_impl(static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISSUBNORMAL_HPP
