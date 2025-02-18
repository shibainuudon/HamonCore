/**
 *	@file	comp_ellint_3.hpp
 *
 *	@brief	comp_ellint_3 関数の定義
 */

#ifndef HAMON_CMATH_COMP_ELLINT_3_HPP
#define HAMON_CMATH_COMP_ELLINT_3_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/detail/ellint_rf.hpp>
#include <hamon/cmath/detail/ellint_rj.hpp>
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
comp_ellint_3_unchecked_2(T k, T nu)
{
	T const x = T(0);
	T const y = T(1) - k * k;
	T const z = T(1);
	return hamon::detail::ellint_rf(x, y, z) +
		nu * hamon::detail::ellint_rj(x, y, z, T(1) - nu) / T(3);
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
comp_ellint_3_unchecked(T k, T nu)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::comp_ellint_3(k, nu);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(comp_ellint_3_unchecked_2(
		static_cast<value_type>(k), static_cast<value_type>(nu)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
comp_ellint_3_impl(T k, T nu)
{
	if (hamon::isnan(k) || hamon::isnan(nu))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	if (hamon::abs(k) > T(1))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	if (hamon::abs(k) == T(1))
	{
		return hamon::numeric_limits<T>::infinity();
	}

	return comp_ellint_3_unchecked(k, nu);
}

}	// namespace detail

/**
 *	@brief	第三種完全楕円積分 (complete elliptic integral of the third kind) を計算する。
 *
 *	@param	k
 *	@param	nu
 *
 *	@return	引数 k, nu の第三種完全楕円積分を返す
 *
 *	引数がどれか1つでも NaN のとき、NaN を返す
 *	|k| > 1 のとき、NaN を返す(std::comp_ellint_3 と違い、例外を投げない)
 *	|k| = 1 のとき、inf を返す
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
comp_ellint_3(FloatType k, FloatType nu) HAMON_NOEXCEPT
{
	return detail::comp_ellint_3_impl(k, nu);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
comp_ellint_3(Arithmetic1 k, Arithmetic2 nu) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::comp_ellint_3_impl(static_cast<type>(k), static_cast<type>(nu));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
comp_ellint_3f(float k, float nu) HAMON_NOEXCEPT
{
	return detail::comp_ellint_3_impl(k, nu);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
comp_ellint_3l(long double k, long double nu) HAMON_NOEXCEPT
{
	return detail::comp_ellint_3_impl(k, nu);
}

}	// namespace hamon

#endif // HAMON_CMATH_COMP_ELLINT_3_HPP
