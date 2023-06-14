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
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <limits>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
scalbln_unchecked(float x, long exp) HAMON_NOEXCEPT
{
	return __builtin_scalblnf(x, exp);
}

inline HAMON_CXX11_CONSTEXPR double
scalbln_unchecked(double x, long exp) HAMON_NOEXCEPT
{
	return __builtin_scalbln(x, exp);
}

inline HAMON_CXX11_CONSTEXPR long double
scalbln_unchecked(long double x, long exp) HAMON_NOEXCEPT
{
	return __builtin_scalblnl(x, exp);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
scalbln_unchecked_ct(T x, long exp)
{
	return x * hamon::detail::pow_n(T(std::numeric_limits<T>::radix), exp);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
scalbln_unchecked(T x, long exp) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::scalbln(x, exp);
	}
#endif
	return scalbln_unchecked_ct(x, exp);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
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
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
scalbln(FloatType x, long exp) HAMON_NOEXCEPT
{
	return detail::scalbln_impl(x, exp);
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

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
scalbln(IntegralType x, long exp) HAMON_NOEXCEPT
{
	return detail::scalbln_impl(static_cast<double>(x), exp);
}

}	// namespace hamon

#endif // HAMON_CMATH_SCALBLN_HPP
