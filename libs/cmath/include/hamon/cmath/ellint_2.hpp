/**
 *	@file	ellint_2.hpp
 *
 *	@brief	ellint_2 関数の定義
 */

#ifndef HAMON_CMATH_ELLINT_2_HPP
#define HAMON_CMATH_ELLINT_2_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/floor.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/cmath/comp_ellint_2.hpp>
#include <hamon/cmath/detail/ellint_rf.hpp>
#include <hamon/cmath/detail/ellint_rd.hpp>
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
ellint_2_unchecked_2(T k, T phi_)
{
	// Reduce phi to -pi/2 < phi < +pi/2.
	int const n = static_cast<int>(hamon::floor(phi_ / hamon::numbers::pi_fn<T>() + T(0.5)));
	T const phi_red = phi_ - n * hamon::numbers::pi_fn<T>();

	T const kk = k * k;
	T const s = hamon::sin(phi_red);
	T const ss = s * s;
	T const sss = ss * s;
	T const c = hamon::cos(phi_red);
	T const cc = c * c;

	T const E = s * hamon::detail::ellint_rf(cc, T(1) - kk * ss, T(1)) -
		kk * sss * hamon::detail::ellint_rd(cc, T(1) - kk * ss, T(1)) / T(3);

	if (n == 0)
	{
		return E;
	}
	else
	{
		return E + T(2) * n * hamon::comp_ellint_2(k);
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
ellint_2_unchecked(T k, T phi_)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::ellint_2(k, phi_);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(ellint_2_unchecked_2(
		static_cast<value_type>(k), static_cast<value_type>(phi_)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
ellint_2_impl(T k, T phi_)
{
	if (hamon::isnan(k) || hamon::isnan(phi_))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	if (hamon::abs(k) > T(1))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	//if (hamon::abs(k) == T(1) && hamon::abs(phi_) >= (hamon::numbers::pi_fn<T>() / 2))
	//{
	//	return hamon::numeric_limits<T>::infinity();
	//}

	return ellint_2_unchecked(k, phi_);
}

}	// namespace detail

/**
 *	@brief	第二種不完全楕円積分 (incomplete elliptic integral of the second kind) を計算する。
 *
 *	@param	k
 *	@param	phi_
 *
 *	@return	引数 k, phi_ の第二種不完全楕円積分を返す
 *
 *	引数がどれか1つでも NaN のとき、NaN を返す
 *	|k| > 1 のとき、NaN を返す(std::ellint_2 と違い、例外を投げない)
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
ellint_2(FloatType k, FloatType phi_) HAMON_NOEXCEPT
{
	return detail::ellint_2_impl(k, phi_);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
ellint_2(Arithmetic1 k, Arithmetic2 phi_) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::ellint_2_impl(static_cast<type>(k), static_cast<type>(phi_));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
ellint_2f(float k, float phi_) HAMON_NOEXCEPT
{
	return detail::ellint_2_impl(k, phi_);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
ellint_2l(long double k, long double phi_) HAMON_NOEXCEPT
{
	return detail::ellint_2_impl(k, phi_);
}

}	// namespace hamon

#endif // HAMON_CMATH_ELLINT_2_HPP
