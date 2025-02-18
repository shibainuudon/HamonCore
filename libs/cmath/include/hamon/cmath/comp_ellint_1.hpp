/**
 *	@file	comp_ellint_1.hpp
 *
 *	@brief	comp_ellint_1 関数の定義
 */

#ifndef HAMON_CMATH_COMP_ELLINT_1_HPP
#define HAMON_CMATH_COMP_ELLINT_1_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/detail/ellint_rf.hpp>
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
comp_ellint_1_unchecked_2(T k)
{
	return hamon::detail::ellint_rf(T(0), T(1) - k * k, T(1));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
comp_ellint_1_unchecked(T k)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::comp_ellint_1(k);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(comp_ellint_1_unchecked_2(static_cast<value_type>(k)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
comp_ellint_1_impl(T k)
{
	if (hamon::isnan(k))
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

	return comp_ellint_1_unchecked(k);
}

}	// namespace detail

/**
 *	@brief	第一種完全楕円積分 (complete elliptic integral of the first kind) を計算する。
 *
 *	@param	k
 *
 *	@return	引数 k の第一種完全楕円積分を返す
 *
 *	引数 k が NaN のとき、NaN を返す
 *	|k| > 1 のとき、NaN を返す(std::comp_ellint_1 と違い、例外を投げない)
 *	|k| = 1 のとき、inf を返す
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
comp_ellint_1(FloatType k) HAMON_NOEXCEPT
{
	return detail::comp_ellint_1_impl(k);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR double
comp_ellint_1(IntegralType k) HAMON_NOEXCEPT
{
	return detail::comp_ellint_1_impl(static_cast<double>(k));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
comp_ellint_1f(float k) HAMON_NOEXCEPT
{
	return detail::comp_ellint_1_impl(k);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
comp_ellint_1l(long double k) HAMON_NOEXCEPT
{
	return detail::comp_ellint_1_impl(k);
}

}	// namespace hamon

#endif // HAMON_CMATH_COMP_ELLINT_1_HPP
