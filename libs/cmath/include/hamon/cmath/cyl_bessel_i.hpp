/**
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
#include <hamon/limits.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX14_CONSTEXPR FloatType
cyl_bessel_i_unchecked(FloatType nu, FloatType x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// MSVC-STL では引数がdoubleのものしか用意されていない
		return std::cyl_bessel_i(nu, x);
HAMON_WARNING_POP()
	}
#endif

	if (x * x < FloatType(10) * (nu + FloatType(1)))
	{
		return hamon::detail::cyl_bessel_ij_series(nu, x, +FloatType(1), 200);
	}
	else
	{
		using T = hamon::float_promote_t<double, FloatType>;
		T I_nu{};
		T K_nu{};
		T Ip_nu{};
		T Kp_nu{};
		hamon::detail::bessel_ik(static_cast<T>(nu), static_cast<T>(x), I_nu, K_nu, Ip_nu, Kp_nu);
		return static_cast<FloatType>(I_nu);
	}
}

template <typename FloatType>
HAMON_CXX14_CONSTEXPR FloatType
cyl_bessel_i_impl(FloatType nu, FloatType x) HAMON_NOEXCEPT
{
	if (hamon::isnan(nu) || hamon::isnan(x))
	{
		return hamon::numeric_limits<FloatType>::quiet_NaN();
	}

	if (nu < FloatType(0) || x < FloatType(0))
	{
		return hamon::numeric_limits<FloatType>::quiet_NaN();
	}

	return hamon::detail::cyl_bessel_i_unchecked(nu, x);
}

}	// namespace detail

// 29.7.6.8 Regular modified cylindrical Bessel functions[sf.cmath.cyl.bessel.i]

/**
 *	@brief	第1種変形ベッセル関数 (modified Bessel functions of the first kind) を求める
 *
 *	@param	nu
 *	@param	x
 *
 *	@return	引数 nu, x の第1種変形ベッセル関数を返す
 *
 *	引数が NaN のとき、NaN を返す
 *	nu >= 128 のとき、振る舞いは実装定義
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
cyl_bessel_i(FloatType nu, FloatType x) HAMON_NOEXCEPT
{
	return detail::cyl_bessel_i_impl(nu, x);
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

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
cyl_bessel_i(Arithmetic1 nu, Arithmetic2 x) HAMON_NOEXCEPT
{
	using T = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::cyl_bessel_i_impl(static_cast<T>(nu), static_cast<T>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_CYL_BESSEL_I_HPP
