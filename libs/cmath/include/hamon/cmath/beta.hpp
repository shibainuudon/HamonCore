/**
 *	@file	beta.hpp
 *
 *	@brief	beta 関数の定義
 */

#ifndef HAMON_CMATH_BETA_HPP
#define HAMON_CMATH_BETA_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/tgamma.hpp>
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
beta_unchecked_2(T x, T y)
{
	if (x > y)
	{
		return (hamon::tgamma(x) / hamon::tgamma(x + y)) * hamon::tgamma(y);
	}
	else
	{
		return (hamon::tgamma(y) / hamon::tgamma(x + y)) * hamon::tgamma(x);
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
beta_unchecked(T x, T y)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::beta(x, y);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(beta_unchecked_2(
		static_cast<value_type>(x), static_cast<value_type>(y)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
beta_impl(T x, T y)
{
	if (hamon::isnan(x) || hamon::isnan(y))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	if (x <= T(0) || y <= T(0))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	return beta_unchecked(x, y);
}

}	// namespace detail

/**
 *	@brief	ベータ関数 (beta function) を計算する。
 *
 *	@param	x
 *	@param	y
 *
 *	@return	引数 x, y のベータ関数を返す
 *
 *	引数がどれか1つでも NaN のとき、NaN を返す
 *	x <= 0 または y <= 0 のとき、NaN を返す
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
betaf(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::beta_impl(x, y);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
beta(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::beta_impl(static_cast<type>(x), static_cast<type>(y));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
betaf(float x, float y) HAMON_NOEXCEPT
{
	return detail::beta_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
betal(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::beta_impl(x, y);
}

}	// namespace hamon

#endif // HAMON_CMATH_BETA_HPP
