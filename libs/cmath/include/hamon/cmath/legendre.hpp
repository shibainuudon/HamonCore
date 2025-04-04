﻿/**
 *	@file	legendre.hpp
 *
 *	@brief	legendre 関数の定義
 */

#ifndef HAMON_CMATH_LEGENDRE_HPP
#define HAMON_CMATH_LEGENDRE_HPP

#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/limits.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
legendre_unchecked_2(unsigned int n, T x)
{
	T p0 = 1;
	if (n == 0)
	{
		return p0;
	}

	T p1 = x;

	for (unsigned int c = 1; c < n; ++c)
	{
		using hamon::swap;
		swap(p0, p1);
		p1 = ((T(2) * c + T(1)) * x * p0 - c * p1) / (c + T(1));
	}

	return p1;
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
legendre_unchecked(unsigned int n, T x)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::legendre(n, x);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(legendre_unchecked_2(n, static_cast<value_type>(x)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
legendre_impl(unsigned int n, T x)
{
	if (hamon::isnan(x))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	if (hamon::abs(x) > T(1))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	return legendre_unchecked(n, x);
}

}	// namespace detail

/**
 *	@brief	ルジャンドル多項式 (Legendre polynomials) を計算する。
 *
 *	@param	n
 *	@param	x
 *
 *	@return	引数 n, x のルジャンドル多項式を返す
 *
 *	引数 x が NaN のとき、NaN を返す
 *	|x| > 1 のとき、NaN を返す
 *	n >= 128 のとき、振る舞いは実装定義
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
legendre(unsigned int n, FloatType x) HAMON_NOEXCEPT
{
	return detail::legendre_impl(n, x);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR double
legendre(unsigned int n, IntegralType x) HAMON_NOEXCEPT
{
	return detail::legendre_impl(n, static_cast<double>(x));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
legendref(unsigned int n, float x) HAMON_NOEXCEPT
{
	return detail::legendre_impl(n, x);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
legendrel(unsigned int n, long double x) HAMON_NOEXCEPT
{
	return detail::legendre_impl(n, x);
}

}	// namespace hamon

#endif // HAMON_CMATH_LEGENDRE_HPP
