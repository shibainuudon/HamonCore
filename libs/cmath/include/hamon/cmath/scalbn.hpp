/**
 *	@file	scalbn.hpp
 *
 *	@brief	scalbn 関数の定義
 */

#ifndef HAMON_CMATH_SCALBN_HPP
#define HAMON_CMATH_SCALBN_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
scalbn_unchecked(float x, int exp) HAMON_NOEXCEPT
{
	return __builtin_scalbnf(x, exp);
}

inline HAMON_CXX11_CONSTEXPR double
scalbn_unchecked(double x, int exp) HAMON_NOEXCEPT
{
	return __builtin_scalbn(x, exp);
}

inline HAMON_CXX11_CONSTEXPR long double
scalbn_unchecked(long double x, int exp) HAMON_NOEXCEPT
{
	return __builtin_scalbnl(x, exp);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
scalbn_unchecked_ct(T x, int exp)
{
	return x * hamon::detail::pow_n(T(hamon::numeric_limits<T>::radix), exp);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
scalbn_unchecked(T x, int exp) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::scalbn(x, exp);
	}
#endif
	return scalbn_unchecked_ct(x, exp);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
scalbn_impl(FloatType x, int exp) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) || hamon::isinf(x) || (exp == 0) || hamon::isnan(x) ?
			x :
		scalbn_unchecked(x, exp);
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
scalbn(FloatType x, int exp) HAMON_NOEXCEPT
{
	return detail::scalbn_impl(x, exp);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
scalbnf(float x, int exp) HAMON_NOEXCEPT
{
	return detail::scalbn_impl(x, exp);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
scalbnl(long double x, int exp) HAMON_NOEXCEPT
{
	return detail::scalbn_impl(x, exp);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
scalbn(IntegralType x, int exp) HAMON_NOEXCEPT
{
	return detail::scalbn_impl(static_cast<double>(x), exp);
}

}	// namespace hamon

#endif // HAMON_CMATH_SCALBN_HPP
