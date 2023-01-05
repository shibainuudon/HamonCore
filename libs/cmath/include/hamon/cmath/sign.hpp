/**
 *	@file	sign.hpp
 *
 *	@brief	sign
 */

#ifndef HAMON_CMATH_SIGN_HPP
#define HAMON_CMATH_SIGN_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR T
sign_unchecked(T x) HAMON_NOEXCEPT
{
	return
		x <  0 ? T(-1) :
		x == 0 ? T( 0) :
		         T( 1);
}

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
sign_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			x :
		sign_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	符号関数
 *
 *	@param	x	対象となる値
 *
 *	@brief	引数 x の符号を返す
 *
 *	x が NaN の場合、NaNを返す。
 *	x <  0 の場合、-1を返す。
 *	x == 0 の場合、 0を返す。
 *	x >  0 の場合、 1を返す。
 */
inline HAMON_CONSTEXPR float
sign(float arg) HAMON_NOEXCEPT
{
	return detail::sign_impl(arg);
}

inline HAMON_CONSTEXPR double
sign(double arg) HAMON_NOEXCEPT
{
	return detail::sign_impl(arg);
}

inline HAMON_CONSTEXPR long double
sign(long double arg) HAMON_NOEXCEPT
{
	return detail::sign_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
inline HAMON_CONSTEXPR double
sign(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::sign_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_SIGN_HPP
