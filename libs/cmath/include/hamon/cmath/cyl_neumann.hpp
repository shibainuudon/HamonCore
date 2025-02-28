/**
 *	@file	cyl_neumann.hpp
 *
 *	@brief	cyl_neumann 関数の定義
 */

#ifndef HAMON_CMATH_CYL_NEUMANN_HPP
#define HAMON_CMATH_CYL_NEUMANN_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/detail/cyl_bessel_jn_asymp.hpp>
#include <hamon/cmath/detail/bessel_jn.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
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
cyl_neumann_unchecked_2(T nu, T x)
{
	if (x > T(1000))
	{
		T J_nu, N_nu;
		hamon::detail::cyl_bessel_jn_asymp(nu, x, J_nu, N_nu);
		return N_nu;
	}
	else
	{
		T J_nu, N_nu, Jp_nu, Np_nu;
		hamon::detail::bessel_jn(nu, x, J_nu, N_nu, Jp_nu, Np_nu);
		return N_nu;
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
cyl_neumann_unchecked(T nu, T x)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::cyl_neumann(nu, x);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(cyl_neumann_unchecked_2(
		static_cast<value_type>(nu), static_cast<value_type>(x)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
cyl_neumann_impl(T nu, T x)
{
	if (hamon::isnan(nu) || hamon::isnan(x))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	return cyl_neumann_unchecked(nu, x);
}

}	// namespace detail

/**
 *	@brief	第二種ベッセル関数 (Bessel functions of the second kind)、ノイマン関数 (Neumann functions) を計算する。
 *
 *	@param	nu
 *	@param	x
 *
 *	@return	引数 nu, x の第二種ベッセル関数を返す
 *
 *	引数がどれか1つでも NaN のとき、NaN を返す
 *	nu >= 128 のとき、振る舞いは実装定義
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
cyl_neumann(FloatType nu, FloatType x) HAMON_NOEXCEPT
{
	return detail::cyl_neumann_impl(nu, x);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
cyl_neumann(Arithmetic1 nu, Arithmetic2 x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::cyl_neumann_impl(static_cast<type>(nu), static_cast<type>(x));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
cyl_neumannf(float nu, float x) HAMON_NOEXCEPT
{
	return detail::cyl_neumann_impl(nu, x);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
cyl_neumannl(long double nu, long double x) HAMON_NOEXCEPT
{
	return detail::cyl_neumann_impl(nu, x);
}

}	// namespace hamon

#endif // HAMON_CMATH_CYL_NEUMANN_HPP
