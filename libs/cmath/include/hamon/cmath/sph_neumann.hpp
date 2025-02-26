/**
 *	@file	sph_neumann.hpp
 *
 *	@brief	sph_neumann 関数の定義
 */

#ifndef HAMON_CMATH_SPH_NEUMANN_HPP
#define HAMON_CMATH_SPH_NEUMANN_HPP

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
sph_neumann_unchecked_2(unsigned int n, T x)
{
	T j_n{}, n_n{}, jp_n{}, np_n{};
	hamon::detail::sph_bessel_jn(n, x, j_n, n_n, jp_n, np_n);
	return n_n;
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
sph_neumann_unchecked(unsigned int n, T x)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::sph_neumann(n, x);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(sph_neumann_unchecked_2(n, static_cast<value_type>(x)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
sph_neumann_impl(unsigned int n, T x)
{
	if (hamon::isnan(x))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	if (x == T(0))
	{
		return -hamon::numeric_limits<T>::infinity();
	}

	return sph_neumann_unchecked(n, x);
}

}	// namespace detail

/**
 *	@brief	第二種球ベッセル関数 (spherical Bessel functions of the second kind)、
 *			球ノイマン関数 (spherical Neumann functions) を求める。
 *
 *	@param	n
 *	@param	x
 *
 *	@return	引数 n, x の第二種球ベッセル関数を返す
 *
 *	x が NaN のとき、NaN を返す
 *	n >= 128 の場合、この関数の呼び出しの効果は実装定義である
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
sph_neumann(unsigned int n, FloatType x) HAMON_NOEXCEPT
{
	return detail::sph_neumann_impl(n, x);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR double
sph_neumann(unsigned int n, IntegralType x) HAMON_NOEXCEPT
{
	return detail::sph_neumann_impl(n, static_cast<double>(x));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
sph_neumannf(unsigned int n, float x) HAMON_NOEXCEPT
{
	return detail::sph_neumann_impl(n, x);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
sph_neumannl(unsigned int n, long double x) HAMON_NOEXCEPT
{
	return detail::sph_neumann_impl(n, x);
}

}	// namespace hamon

#endif // HAMON_CMATH_SPH_NEUMANN_HPP
