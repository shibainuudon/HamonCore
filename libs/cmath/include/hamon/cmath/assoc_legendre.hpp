/**
 *	@file	assoc_legendre.hpp
 *
 *	@brief	assoc_legendre 関数の定義
 */

#ifndef HAMON_CMATH_ASSOC_LEGENDRE_HPP
#define HAMON_CMATH_ASSOC_LEGENDRE_HPP

#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/legendre.hpp>
#include <hamon/cmath/sqrt.hpp>
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
assoc_legendre_unchecked_2(unsigned int n, unsigned int m, T x)
{
	T const phase = T(+1);

	if (m > n)
	{
		return T(0);
	}

	if (m == 0)
	{
		return hamon::detail::legendre_unchecked(n, x);
	}

	T p_mm = T(1);
	if (m > 0)
	{
		//  Two square roots seem more accurate more of the time
		//  than just one.
		T root = hamon::sqrt(T(1) - x) * hamon::sqrt(T(1) + x);
		T fact = T(1);
		for (unsigned int i = 1; i <= m; ++i)
		{
			p_mm *= phase * fact * root;
			fact += T(2);
		}
	}

	if (n == m)
	{
		return p_mm;
	}

	T p_mp1m = T(2 * m + 1) * x * p_mm;
	if (n == m + 1)
	{
		return p_mp1m;
	}

	T p_lm2m = p_mm;
	T P_lm1m = p_mp1m;
	T p_lm = T(0);
	for (unsigned int j = m + 2; j <= n; ++j)
	{
		p_lm = (T(2 * j - 1) * x * P_lm1m - T(j + m - 1) * p_lm2m) / T(j - m);
		p_lm2m = P_lm1m;
		P_lm1m = p_lm;
	}

	return p_lm;
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
assoc_legendre_unchecked(unsigned int n, unsigned int m, T x)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::assoc_legendre(n, m, x);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(assoc_legendre_unchecked_2(n, m, static_cast<value_type>(x)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
assoc_legendre_impl(unsigned int n, unsigned int m, T x)
{
	if (hamon::isnan(x))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	if (hamon::abs(x) > T(1))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	return assoc_legendre_unchecked(n, m, x);
}

}	// namespace detail

/**
 *	@brief	ルジャンドル陪関数 (associated Legendre functions) を計算する。
 *
 *	@param	n
 *	@param	m
 *	@param	x
 *
 *	@return	引数 n, m, x のルジャンドル陪関数を返す
 *
 *	引数 x が NaN のとき、NaN を返す
 *	|x| > 1 のとき、NaN を返す(std::assoc_legendre と違い、例外を投げない)
 *	n >= 128 のとき、振る舞いは実装定義
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
assoc_legendre(unsigned int n, unsigned int m, FloatType x) HAMON_NOEXCEPT
{
	return detail::assoc_legendre_impl(n, m, x);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR double
assoc_legendre(unsigned int n, unsigned int m, IntegralType x) HAMON_NOEXCEPT
{
	return detail::assoc_legendre_impl(n, m, static_cast<double>(x));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
assoc_legendref(unsigned int n, unsigned int m, float x) HAMON_NOEXCEPT
{
	return detail::assoc_legendre_impl(n, m, x);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
assoc_legendrel(unsigned int n, unsigned int m, long double x) HAMON_NOEXCEPT
{
	return detail::assoc_legendre_impl(n, m, x);
}

}	// namespace hamon

#endif // HAMON_CMATH_ASSOC_LEGENDRE_HPP
