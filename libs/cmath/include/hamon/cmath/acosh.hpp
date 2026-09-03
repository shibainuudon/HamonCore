/**
 *	@file	acosh.hpp
 *
 *	@brief	acosh 関数の定義
 */

#ifndef HAMON_CMATH_ACOSH_HPP
#define HAMON_CMATH_ACOSH_HPP

#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
acosh_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return hamon::log(x + hamon::sqrt(x * x - 1));
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
acosh_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::acosh(x);
}

inline HAMON_CXX11_CONSTEXPR float
acosh_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_acoshf(x);
#elif HAMON_HAS_BUILTIN(__builtin_acoshf)
	return hamon::is_constant_evaluated() ? acosh_unchecked_ct(x) : __builtin_acoshf(x);
#else
	return hamon::is_constant_evaluated() ? acosh_unchecked_ct(x) : acosh_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
acosh_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_acosh(x);
#elif HAMON_HAS_BUILTIN(__builtin_acosh)
	return hamon::is_constant_evaluated() ? acosh_unchecked_ct(x) : __builtin_acosh(x);
#else
	return hamon::is_constant_evaluated() ? acosh_unchecked_ct(x) : acosh_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
acosh_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_acoshl(x);
#elif HAMON_HAS_BUILTIN(__builtin_acoshl)
	return hamon::is_constant_evaluated() ? acosh_unchecked_ct(x) : __builtin_acoshl(x);
#else
	return hamon::is_constant_evaluated() ? acosh_unchecked_ct(x) : acosh_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
acosh_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			x :
		x < FloatType(1) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		x == FloatType(1) ?
			FloatType(0) :
		hamon::isinf(x) ?
			x :
		acosh_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	逆双曲線余弦（アークハイパボリックコサイン）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの逆双曲線余弦を返す
 *
 *	arg < 1  の場合、NaN を返す。
 *	arg = 1  の場合、+0  を返す。
 *	arg が +∞ の場合、+∞ を返す。
 *	arg が NaN の場合、NaN を返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
acosh(FloatType arg) HAMON_NOEXCEPT
{
	return detail::acosh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
acoshf(float arg) HAMON_NOEXCEPT
{
	return detail::acosh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
acoshl(long double arg) HAMON_NOEXCEPT
{
	return detail::acosh_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
acosh(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::acosh_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ACOSH_HPP
