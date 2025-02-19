/**
 *	@file	sph_bessel.hpp
 *
 *	@brief	sph_bessel 関数の定義
 */

#ifndef HAMON_CMATH_SPH_BESSEL_HPP
#define HAMON_CMATH_SPH_BESSEL_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/detail/sph_bessel_jn.hpp>
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
sph_bessel_unchecked_2(unsigned int n, T x)
{
	if (x == T(0))
	{
		if (n == 0)
		{
			return T(1);
		}
		else
		{
			return T(0);
		}
	}
	else
	{
		T j_n, n_n, jp_n, np_n;
		hamon::detail::sph_bessel_jn(n, x, j_n, n_n, jp_n, np_n);
		return j_n;
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
sph_bessel_unchecked(unsigned int n, T x)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::sph_bessel(n, x);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(sph_bessel_unchecked_2(n, static_cast<value_type>(x)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
sph_bessel_impl(unsigned int n, T x)
{
	if (hamon::isnan(x))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	return sph_bessel_unchecked(n, x);
}

}	// namespace detail

/**
 *	@brief	第一種球ベッセル関数 (spherical Bessel functions of the first kind) を計算する。
 *
 *	@param	n
 *	@param	x
 *
 *	@return	引数 n, x の第一種球ベッセル関数を返す
 *
 *	x が NaN のとき、NaN を返す
 *	n >= 128 の場合、この関数の呼び出しの効果は実装定義である
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
sph_bessel(unsigned int n, FloatType x) HAMON_NOEXCEPT
{
	return detail::sph_bessel_impl(n, x);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR double
sph_bessel(unsigned int n, IntegralType x) HAMON_NOEXCEPT
{
	return detail::sph_bessel_impl(n, static_cast<double>(x));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
sph_besself(unsigned int n, float x) HAMON_NOEXCEPT
{
	return detail::sph_bessel_impl(n, x);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
sph_bessell(unsigned int n, long double x) HAMON_NOEXCEPT
{
	return detail::sph_bessel_impl(n, x);
}

}	// namespace hamon

#endif // HAMON_CMATH_SPH_BESSEL_HPP
