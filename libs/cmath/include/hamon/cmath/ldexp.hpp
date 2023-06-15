/**
 *	@file	ldexp.hpp
 *
 *	@brief	ldexp 関数の定義
 */

#ifndef HAMON_CMATH_LDEXP_HPP
#define HAMON_CMATH_LDEXP_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/scalbn.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
ldexp_unchecked(float x, int exp) HAMON_NOEXCEPT
{
	return __builtin_ldexpf(x, exp);
}

inline HAMON_CXX11_CONSTEXPR double
ldexp_unchecked(double x, int exp) HAMON_NOEXCEPT
{
	return __builtin_ldexp(x, exp);
}

inline HAMON_CXX11_CONSTEXPR long double
ldexp_unchecked(long double x, int exp) HAMON_NOEXCEPT
{
	return __builtin_ldexpl(x, exp);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
ldexp_unchecked(T x, int exp) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::ldexp(x, exp);
	}
#endif

	// FLT_RADIX が2のとき、scalbn と等しい
	// そうでないときは、x * std::pow(2, exp) となる
	return hamon::scalbn(x, exp);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
ldexp_impl(FloatType x, int exp) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) || hamon::isinf(x) || (exp == 0) || hamon::isnan(x) ?
			x :
		ldexp_unchecked(x, exp);
}

}	// namespace detail

/**
 *	@brief	浮動小数点数に2の整数乗を掛ける
 *
 *	@param	x	浮動小数点型の値
 *	@param	exp	整数型の値
 *
 *	@return	x に 2 の exp 乗を掛ける(x * (2 ^ exp))
 *
 *	x が ±0  だった場合、x をそのまま返す。
 *	x が ±∞ だった場合、x をそのまま返す。
 *	exp が 0 だった場合、x をそのまま返す。
 *	x が NaN だった場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
ldexp(FloatType x, int exp) HAMON_NOEXCEPT
{
	return detail::ldexp_impl(x, exp);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
ldexpf(float x, int exp) HAMON_NOEXCEPT
{
	return detail::ldexp_impl(x, exp);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
ldexpl(long double x, int exp) HAMON_NOEXCEPT
{
	return detail::ldexp_impl(x, exp);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
ldexp(IntegralType x, int exp) HAMON_NOEXCEPT
{
	return detail::ldexp_impl(static_cast<double>(x), exp);
}

}	// namespace hamon

#endif // HAMON_CMATH_LDEXP_HPP
