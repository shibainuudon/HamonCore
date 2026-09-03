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
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
ldexp_unchecked_ct(T x, int exp) HAMON_NOEXCEPT
{
	// FLT_RADIX が2のとき、scalbn と等しい
	// そうでないときは、x * std::pow(2, exp) となる
	return hamon::scalbn(x, exp);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
ldexp_unchecked_rt(T x, int exp) HAMON_NOEXCEPT
{
	// TODO
	return std::ldexp(x, exp);
}

inline HAMON_CXX11_CONSTEXPR float
ldexp_unchecked(float x, int exp) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_ldexpf(x, exp);
#elif HAMON_HAS_BUILTIN(__builtin_ldexpf)
	return hamon::is_constant_evaluated() ? ldexp_unchecked_ct(x, exp) : __builtin_ldexpf(x, exp);
#else
	return hamon::is_constant_evaluated() ? ldexp_unchecked_ct(x, exp) : ldexp_unchecked_rt(x, exp);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
ldexp_unchecked(double x, int exp) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_ldexp(x, exp);
#elif HAMON_HAS_BUILTIN(__builtin_ldexp)
	return hamon::is_constant_evaluated() ? ldexp_unchecked_ct(x, exp) : __builtin_ldexp(x, exp);
#else
	return hamon::is_constant_evaluated() ? ldexp_unchecked_ct(x, exp) : ldexp_unchecked_rt(x, exp);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
ldexp_unchecked(long double x, int exp) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_ldexpl(x, exp);
#elif HAMON_HAS_BUILTIN(__builtin_ldexpl)
	return hamon::is_constant_evaluated() ? ldexp_unchecked_ct(x, exp) : __builtin_ldexpl(x, exp);
#else
	return hamon::is_constant_evaluated() ? ldexp_unchecked_ct(x, exp) : ldexp_unchecked_rt(x, exp);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
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
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
ldexp(FloatType x, int exp) HAMON_NOEXCEPT
{
	return detail::ldexp_impl(x, exp);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
ldexp(IntegralType x, int exp) HAMON_NOEXCEPT
{
	return detail::ldexp_impl(static_cast<double>(x), exp);
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

}	// namespace hamon

#endif // HAMON_CMATH_LDEXP_HPP
