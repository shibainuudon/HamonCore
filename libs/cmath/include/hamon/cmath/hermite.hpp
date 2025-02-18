/**
 *	@file	hermite.hpp
 *
 *	@brief	hermite 関数の定義
 */

#ifndef HAMON_CMATH_HERMITE_HPP
#define HAMON_CMATH_HERMITE_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
hermite_unchecked_2(unsigned int n, T x)
{
	//  Compute H_0.
	T H_0 = 1;
	if (n == 0)
	{
		return H_0;
	}

	//  Compute H_1.
	T H_1 = 2 * x;
	if (n == 1)
	{
		return H_1;
	}

	//  Compute H_n.
	T H_n = 0;
	T H_nm1 = H_1;
	T H_nm2 = H_0;
	for (unsigned int i = 2; i <= n; ++i)
	{
		H_n = 2 * (x * H_nm1 - (i - 1) * H_nm2);
		H_nm2 = H_nm1;
		H_nm1 = H_n;
	}

	return H_n;
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
hermite_unchecked(unsigned int n, T x)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::hermite(n, x);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(hermite_unchecked_2(n, static_cast<value_type>(x)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
hermite_impl(unsigned int n, T x)
{
	if (hamon::isnan(x))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	return hermite_unchecked(n, x);
}

}	// namespace detail

/**
 *	@brief	エルミート多項式 (Hermite polynomials) を計算する。
 *
 *	@param	n
 *	@param	x
 *
 *	@return	引数 n, x のエルミート多項式を返す
 *
 *	x が NaN のとき、NaN を返す
 *	n >= 128 の場合、この関数の呼び出しの効果は実装定義である
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
hermite(unsigned int n, FloatType x) HAMON_NOEXCEPT
{
	return detail::hermite_impl(n, x);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR double
hermite(unsigned int n, IntegralType x) HAMON_NOEXCEPT
{
	return detail::hermite_impl(n, static_cast<double>(x));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
hermitef(unsigned int n, float x) HAMON_NOEXCEPT
{
	return detail::hermite_impl(n, x);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
hermitel(unsigned int n, long double x) HAMON_NOEXCEPT
{
	return detail::hermite_impl(n, x);
}

}	// namespace hamon

#endif // HAMON_CMATH_HERMITE_HPP
