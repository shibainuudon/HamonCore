/**
 *	@file	ellint_1.hpp
 *
 *	@brief	ellint_1 関数の定義
 */

#ifndef HAMON_CMATH_ELLINT_1_HPP
#define HAMON_CMATH_ELLINT_1_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/floor.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/cmath/comp_ellint_1.hpp>
#include <hamon/cmath/detail/ellint_rf.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/numbers.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
ellint_1_unchecked_2(T k, T phi_)
{
	// Reduce phi_ to -pi/2 < phi_ < +pi/2.
	const int n = static_cast<int>(hamon::floor(phi_ / hamon::numbers::pi_fn<T>() + T(0.5)));
	const T phi_red = phi_ - n * hamon::numbers::pi_fn<T>();

	const T s = hamon::sin(phi_red);
	const T c = hamon::cos(phi_red);

	const T F = s * hamon::detail::ellint_rf(c * c, T(1) - k * k * s * s, T(1));

	if (n == 0)
	{
		return F;
	}
	else
	{
		return F + T(2) * n * hamon::comp_ellint_1(k);
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
ellint_1_unchecked(T k, T phi_)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::ellint_1(k, phi_);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(ellint_1_unchecked_2(
		static_cast<value_type>(k), static_cast<value_type>(phi_)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
ellint_1_impl(T k, T phi_)
{
	return
		(hamon::isnan(k) || hamon::isnan(phi_)) ?
			hamon::numeric_limits<T>::quiet_NaN() :
		(hamon::abs(k) > T(1)) ?
			hamon::numeric_limits<T>::quiet_NaN() :
		(hamon::abs(k) == T(1) && hamon::abs(phi_) >= (hamon::numbers::pi_fn<T>() / 2)) ?
			hamon::numeric_limits<T>::infinity() :
		ellint_1_unchecked(k, phi_);
}

}	// namespace detail

/**
 *	@brief	第一種不完全楕円積分 (incomplete elliptic integral of the first kind) を計算する。
 *
 *	@param	k
 *	@param	phi_
 *
 *	@return	引数 k, phi_ の第一種不完全楕円積分を返す
 *
 *	引数がどれか1つでも NaN のとき、NaN を返す
 *	|k| > 1 のとき、NaN を返す(std::ellint_1 と違い、例外を投げない)
 *	|k| = 1 かつ |phi_| >= π / 2 のとき、inf を返す
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
ellint_1(FloatType k, FloatType phi_) HAMON_NOEXCEPT
{
	return detail::ellint_1_impl(k, phi_);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
ellint_1(Arithmetic1 k, Arithmetic2 phi_) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::ellint_1_impl(static_cast<type>(k), static_cast<type>(phi_));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
ellint_1f(float k, float phi_) HAMON_NOEXCEPT
{
	return detail::ellint_1_impl(k, phi_);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
ellint_1l(long double k, long double phi_) HAMON_NOEXCEPT
{
	return detail::ellint_1_impl(k, phi_);
}

}	// namespace hamon

#endif // HAMON_CMATH_ELLINT_1_HPP
