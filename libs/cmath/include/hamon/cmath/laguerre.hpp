/**
 *	@file	laguerre.hpp
 *
 *	@brief	laguerre 関数の定義
 */

#ifndef HAMON_CMATH_LAGUERRE_HPP
#define HAMON_CMATH_LAGUERRE_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/assoc_laguerre.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/limits.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
laguerre_unchecked(unsigned int n, T x)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::laguerre(n, x);
HAMON_WARNING_POP()
	}
#endif
#endif

	return hamon::detail::assoc_laguerre_unchecked(n, 0, x);
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
laguerre_impl(unsigned int n, T x)
{
	if (hamon::isnan(x))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	if (x < T(0))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	return laguerre_unchecked(n, x);
}

}	// namespace detail

/**
 *	@brief	ラゲール多項式 (Laguerre polynomials) を計算する。
 *
 *	@param	n
 *	@param	x
 *
 *	@return	引数 n, x のラゲール多項式を返す
 *
 *	引数 x が NaN のとき、NaN を返す
 *	x が負の値のとき、NaN を返す(std::laguerre と違い、例外を投げない)
 *	n >= 128 のとき、振る舞いは実装定義
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
laguerre(unsigned int n, FloatType x) HAMON_NOEXCEPT
{
	return detail::laguerre_impl(n, x);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR double
laguerre(unsigned int n, IntegralType x) HAMON_NOEXCEPT
{
	return detail::laguerre_impl(n, static_cast<double>(x));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
laguerref(unsigned int n, float x) HAMON_NOEXCEPT
{
	return detail::laguerre_impl(n, x);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
laguerrel(unsigned int n, long double x) HAMON_NOEXCEPT
{
	return detail::laguerre_impl(n, x);
}

}	// namespace hamon

#endif // HAMON_CMATH_LAGUERRE_HPP
