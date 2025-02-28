﻿/**
 *	@file	cyl_bessel_i.hpp
 *
 *	@brief	cyl_bessel_i 関数の定義
 */

#ifndef HAMON_CMATH_CYL_BESSEL_I_HPP
#define HAMON_CMATH_CYL_BESSEL_I_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/detail/cyl_bessel_ij_series.hpp>
#include <hamon/cmath/detail/bessel_ik.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
cyl_bessel_i_unchecked_2(T nu, T x)
{
	if (x * x < T(10) * (nu + T(1)))
	{
		return hamon::detail::cyl_bessel_ij_series(nu, x, +T(1), 200);
	}
	else
	{
		T i_nu, k_nu, ip_nu, kp_nu;
		hamon::detail::bessel_ik(nu, x, i_nu, k_nu, ip_nu, kp_nu);
		return i_nu;
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
cyl_bessel_i_unchecked(T nu, T x)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::cyl_bessel_i(nu, x);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(cyl_bessel_i_unchecked_2(
		static_cast<value_type>(nu), static_cast<value_type>(x)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
cyl_bessel_i_impl(T nu, T x)
{
	if (hamon::isnan(nu) || hamon::isnan(x))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	return cyl_bessel_i_unchecked(nu, x);
}

}	// namespace detail

/**
 *	@brief	第一種変形ベッセル関数 (modified Bessel functions of the first kind) を計算する。
 *
 *	@param	nu
 *	@param	x
 *
 *	@return	引数 nu, x の第一種変形ベッセル関数を返す
 *
 *	引数がどれか1つでも NaN のとき、NaN を返す
 *	nu >= 128 のとき、振る舞いは実装定義
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
cyl_bessel_i(FloatType nu, FloatType x) HAMON_NOEXCEPT
{
	return detail::cyl_bessel_i_impl(nu, x);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
cyl_bessel_i(Arithmetic1 nu, Arithmetic2 x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::cyl_bessel_i_impl(static_cast<type>(nu), static_cast<type>(x));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
cyl_bessel_if(float nu, float x) HAMON_NOEXCEPT
{
	return detail::cyl_bessel_i_impl(nu, x);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
cyl_bessel_il(long double nu, long double x) HAMON_NOEXCEPT
{
	return detail::cyl_bessel_i_impl(nu, x);
}

}	// namespace hamon

#endif // HAMON_CMATH_CYL_BESSEL_I_HPP
