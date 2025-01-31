/**
 *	@file	fabs.hpp
 *
 *	@brief	fabs
 */

#ifndef HAMON_CMATH_FABS_HPP
#define HAMON_CMATH_FABS_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::fabs;
using std::fabsf;
using std::fabsl;

}	// namespace hamon

#else

#include <hamon/cmath/copysign.hpp>
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
fabs_impl(float x) HAMON_NOEXCEPT
{
	return __builtin_fabsf(x);
}

inline HAMON_CXX11_CONSTEXPR double
fabs_impl(double x) HAMON_NOEXCEPT
{
	return __builtin_fabs(x);
}

inline HAMON_CXX11_CONSTEXPR long double
fabs_impl(long double x) HAMON_NOEXCEPT
{
	return __builtin_fabsl(x);
}

#else

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
fabs_impl(FloatType x) HAMON_NOEXCEPT
{
	return hamon::copysign(x, FloatType(1));
}

#endif

}	// namespace detail

/**
 *	@brief	std::fabs のconstexpr版
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
fabs(FloatType arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
fabs(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
fabsf(float arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
fabsl(long double arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

}	// namespace hamon

#endif

#endif // HAMON_CMATH_FABS_HPP
