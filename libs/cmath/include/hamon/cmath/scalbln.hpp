/**
 *	@file	scalbln.hpp
 *
 *	@brief	scalbln 関数の定義
 */

#ifndef HAMON_CMATH_SCALBLN_HPP
#define HAMON_CMATH_SCALBLN_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
scalbln_unchecked_ct(T x, long exp) HAMON_NOEXCEPT
{
	return x * hamon::detail::pow_n(T(hamon::numeric_limits<T>::radix), exp);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
scalbln_unchecked_rt(T x, long exp) HAMON_NOEXCEPT
{
	// TODO
	return std::scalbln(x, exp);
}

inline HAMON_CXX11_CONSTEXPR float
scalbln_unchecked(float x, long exp) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_scalblnf(x, exp);
#elif HAMON_HAS_BUILTIN(__builtin_scalblnf)
	return hamon::is_constant_evaluated() ? scalbln_unchecked_ct(x, exp) : __builtin_scalblnf(x, exp);
#else
	return hamon::is_constant_evaluated() ? scalbln_unchecked_ct(x, exp) : scalbln_unchecked_rt(x, exp);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
scalbln_unchecked(double x, long exp) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_scalbln(x, exp);
#elif HAMON_HAS_BUILTIN(__builtin_scalbln)
	return hamon::is_constant_evaluated() ? scalbln_unchecked_ct(x, exp) : __builtin_scalbln(x, exp);
#else
	return hamon::is_constant_evaluated() ? scalbln_unchecked_ct(x, exp) : scalbln_unchecked_rt(x, exp);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
scalbln_unchecked(long double x, long exp) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_scalblnl(x, exp);
#elif HAMON_HAS_BUILTIN(__builtin_scalblnl)
	return hamon::is_constant_evaluated() ? scalbln_unchecked_ct(x, exp) : __builtin_scalblnl(x, exp);
#else
	return hamon::is_constant_evaluated() ? scalbln_unchecked_ct(x, exp) : scalbln_unchecked_rt(x, exp);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
scalbln_impl(FloatType x, long exp) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) || hamon::isinf(x) || (exp == 0) || hamon::isnan(x) ?
			x :
		scalbln_unchecked(x, exp);
}

}	// namespace detail

/**
 *	@brief	浮動小数点数に基数の整数乗を掛ける
 *
 *	@param	x	浮動小数点型の値
 *	@param	exp	整数型の値
 *
 *	@return	x に FLT_RADIX の exp 乗を掛ける(x * (FLT_RADIX ^ exp))
 *
 *	x が ±0  だった場合、x をそのまま返す。
 *	x が ±∞  だった場合、x をそのまま返す。
 *	exp が 0 だった場合、x をそのまま返す。
 *	x が NaN だった場合、NaN を返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
scalbln(FloatType x, long exp) HAMON_NOEXCEPT
{
	return detail::scalbln_impl(x, exp);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
scalbln(IntegralType x, long exp) HAMON_NOEXCEPT
{
	return detail::scalbln_impl(static_cast<double>(x), exp);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
scalblnf(float x, long exp) HAMON_NOEXCEPT
{
	return detail::scalbln_impl(x, exp);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
scalblnl(long double x, long exp) HAMON_NOEXCEPT
{
	return detail::scalbln_impl(x, exp);
}

}	// namespace hamon

#endif // HAMON_CMATH_SCALBLN_HPP
