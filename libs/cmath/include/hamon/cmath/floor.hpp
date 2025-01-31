/**
 *	@file	floor.hpp
 *
 *	@brief	floor 関数の定義
 */

#ifndef HAMON_CMATH_FLOOR_HPP
#define HAMON_CMATH_FLOOR_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::floor;
using std::floorf;
using std::floorl;

}	// namespace hamon

#else

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/almost_equal.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
floor_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_floorf(x);
}

inline HAMON_CXX11_CONSTEXPR double
floor_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_floor(x);
}

inline HAMON_CXX11_CONSTEXPR long double
floor_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_floorl(x);
}

#else

template <typename T>
HAMON_CXX11_CONSTEXPR T
floor_unchecked_1(T x, T x0) HAMON_NOEXCEPT
{
	return
		x >= 0 || hamon::almost_equal(x, x0) ?
			x0 :
		x0 - T(1);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
floor_unchecked(T x) HAMON_NOEXCEPT
{
	return floor_unchecked_1(x, trunc_unchecked(x));
}

#endif

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
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
floor(FloatType arg) HAMON_NOEXCEPT
{
	return detail::floor_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
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

#endif

#endif // HAMON_CMATH_FLOOR_HPP
