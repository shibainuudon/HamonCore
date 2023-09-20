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
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
cosh_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_coshf(x);
}

inline HAMON_CXX11_CONSTEXPR double
cosh_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_cosh(x);
}

inline HAMON_CXX11_CONSTEXPR long double
cosh_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_coshl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
cosh_unchecked_ct_1(T x) HAMON_NOEXCEPT
{
	return T(0.5) * x + T(0.5) / x;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
cosh_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return cosh_unchecked_ct_1(hamon::exp(x));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
cosh_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::cosh(x);
	}
#endif
	return cosh_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
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
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
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

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
cosh(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::cosh_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_COSH_HPP
