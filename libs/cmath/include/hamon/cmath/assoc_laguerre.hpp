/**
 *	@file	assoc_laguerre.hpp
 *
 *	@brief	assoc_laguerre 関数の定義
 */

#ifndef HAMON_CMATH_ASSOC_LAGUERRE_HPP
#define HAMON_CMATH_ASSOC_LAGUERRE_HPP

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
assoc_laguerre_unchecked_2(unsigned int n, unsigned int m, T x)
{
	T p0 = 1;
	if (n == 0)
	{
		return p0;
	}

	T p1 = m + T(1) - x;

	for (unsigned int c = 1; c < n; ++c)
	{
		using hamon::swap;
		swap(p0, p1);
		p1 = ((T(2) * c + m + T(1) - x) * p0 - (T(c) + T(m)) * p1) / (c + T(1));
	}

	return p1;
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
assoc_laguerre_unchecked(unsigned int n, unsigned int m, T x)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::assoc_laguerre(n, m, x);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(assoc_laguerre_unchecked_2(n, m, static_cast<value_type>(x)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
assoc_laguerre_impl(unsigned int n, unsigned int m, T x)
{
	if (hamon::isnan(x))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	if (x < T(0))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	return assoc_laguerre_unchecked(n, m, x);
}

}	// namespace detail

/**
 *	@brief	ラゲール陪多項式 (associated Laguerre polynomials) を計算する。
 *
 *	@param	n
 *	@param	m
 *	@param	x
 *
 *	@return	引数 n, m, x のラゲール陪多項式を返す
 *
 *	引数 x が NaN のとき、NaN を返す
 *	x が負の値のとき、NaN を返す(std::assoc_laguerre と違い、例外を投げない)
 *	n >= 128 または m >= 128 のとき、振る舞いは実装定義
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
assoc_laguerre(unsigned int n, unsigned int m, FloatType x) HAMON_NOEXCEPT
{
	return detail::assoc_laguerre_impl(n, m, x);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR double
assoc_laguerre(unsigned int n, unsigned int m, IntegralType x) HAMON_NOEXCEPT
{
	return detail::assoc_laguerre_impl(n, m, static_cast<double>(x));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
assoc_laguerref(unsigned int n, unsigned int m, float x) HAMON_NOEXCEPT
{
	return detail::assoc_laguerre_impl(n, m, x);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
assoc_laguerrel(unsigned int n, unsigned int m, long double x) HAMON_NOEXCEPT
{
	return detail::assoc_laguerre_impl(n, m, x);
}

}	// namespace hamon

#endif // HAMON_CMATH_ASSOC_LAGUERRE_HPP
