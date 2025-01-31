/**
 *	@file	ceil.hpp
 *
 *	@brief	ceil
 */

#ifndef HAMON_CMATH_CEIL_HPP
#define HAMON_CMATH_CEIL_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::ceil;
using std::ceilf;
using std::ceill;

}	// namespace hamon

#else

#include <hamon/cmath/almost_equal.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
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
ceil_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_ceilf(x);
}

inline HAMON_CXX11_CONSTEXPR double
ceil_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_ceil(x);
}

inline HAMON_CXX11_CONSTEXPR long double
ceil_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_ceill(x);
}

#else

template <typename T>
HAMON_CXX11_CONSTEXPR T
ceil_unchecked_1(T x, T x0) HAMON_NOEXCEPT
{
	return
		x < 0 || hamon::almost_equal(x, x0) ?
			x0 :
		x0 + T(1);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
ceil_unchecked(T x) HAMON_NOEXCEPT
{
	return ceil_unchecked_1(x, trunc_unchecked(x));
}

#endif

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
ceil_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		(hamon::iszero(x) || hamon::isnan(x) || hamon::isinf(x)) ?
			x :
		ceil_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	std::ceil のconstexpr版
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
ceil(FloatType arg) HAMON_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
ceil(IntegralType arg) HAMON_NOEXCEPT
{
	return static_cast<double>(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
ceilf(float arg) HAMON_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
ceill(long double arg) HAMON_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

}	// namespace hamon

#endif

#endif // HAMON_CMATH_CEIL_HPP
