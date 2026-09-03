/**
 *	@file	cosh.hpp
 *
 *	@brief	cosh 関数の定義
 */

#ifndef HAMON_CMATH_COSH_HPP
#define HAMON_CMATH_COSH_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/exp.hpp>
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
cosh_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T const y = hamon::exp(x);
	return T(0.5) * y + T(0.5) / y;
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
cosh_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::cosh(x);
}

inline HAMON_CXX11_CONSTEXPR float
cosh_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_coshf(x);
#elif HAMON_HAS_BUILTIN(__builtin_coshf)
	return hamon::is_constant_evaluated() ? cosh_unchecked_ct(x) : __builtin_coshf(x);
#else
	return hamon::is_constant_evaluated() ? cosh_unchecked_ct(x) : cosh_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
cosh_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_cosh(x);
#elif HAMON_HAS_BUILTIN(__builtin_cosh)
	return hamon::is_constant_evaluated() ? cosh_unchecked_ct(x) : __builtin_cosh(x);
#else
	return hamon::is_constant_evaluated() ? cosh_unchecked_ct(x) : cosh_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
cosh_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_coshl(x);
#elif HAMON_HAS_BUILTIN(__builtin_coshl)
	return hamon::is_constant_evaluated() ? cosh_unchecked_ct(x) : __builtin_coshl(x);
#else
	return hamon::is_constant_evaluated() ? cosh_unchecked_ct(x) : cosh_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
cosh_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			FloatType(1) :
		hamon::isinf(x) ?
			hamon::numeric_limits<FloatType>::infinity() :
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		cosh_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	双曲線余弦（ハイパボリックコサイン）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの双曲線余弦を返す
 *
 *	arg が ±0  の場合、1を返す。
 *	arg が ±∞ の場合、+∞を返す。
 *	arg が NaN  の場合、NaNを返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
cosh(FloatType arg) HAMON_NOEXCEPT
{
	return detail::cosh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
coshf(float arg) HAMON_NOEXCEPT
{
	return detail::cosh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
coshl(long double arg) HAMON_NOEXCEPT
{
	return detail::cosh_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
cosh(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::cosh_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_COSH_HPP
