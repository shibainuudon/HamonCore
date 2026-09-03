/**
 *	@file	floor.hpp
 *
 *	@brief	floor 関数の定義
 */

#ifndef HAMON_CMATH_FLOOR_HPP
#define HAMON_CMATH_FLOOR_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/almost_equal.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
floor_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T const x0 = trunc_unchecked(x);
	return
		x >= 0 || hamon::almost_equal(x, x0) ?
			x0 :
		x0 - T(1);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
floor_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::floor(x);
}

inline HAMON_CXX11_CONSTEXPR float
floor_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_floorf(x);
#elif HAMON_HAS_BUILTIN(__builtin_floorf)
	return hamon::is_constant_evaluated() ? floor_unchecked_ct(x) : __builtin_floorf(x);
#else
	return hamon::is_constant_evaluated() ? floor_unchecked_ct(x) : floor_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
floor_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_floor(x);
#elif HAMON_HAS_BUILTIN(__builtin_floor)
	return hamon::is_constant_evaluated() ? floor_unchecked_ct(x) : __builtin_floor(x);
#else
	return hamon::is_constant_evaluated() ? floor_unchecked_ct(x) : floor_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
floor_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_floorl(x);
#elif HAMON_HAS_BUILTIN(__builtin_floorl)
	return hamon::is_constant_evaluated() ? floor_unchecked_ct(x) : __builtin_floorl(x);
#else
	return hamon::is_constant_evaluated() ? floor_unchecked_ct(x) : floor_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
floor_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		(hamon::iszero(x) || hamon::isnan(x) || hamon::isinf(x)) ?
			x :
		floor_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	床関数
 *
 *	@param	arg	対象となる値
 *
 *	@return	arg以下で最大の整数
 *
 *	arg が ±∞ の場合、argをそのまま返す。
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が NaN  の場合、NaNを返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
floor(FloatType arg) HAMON_NOEXCEPT
{
	return detail::floor_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
floor(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::floor_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
floorf(float arg) HAMON_NOEXCEPT
{
	return detail::floor_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
floorl(long double arg) HAMON_NOEXCEPT
{
	return detail::floor_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_FLOOR_HPP
