/**
 *	@file	fabs.hpp
 *
 *	@brief	fabs
 */

#ifndef HAMON_CMATH_FABS_HPP
#define HAMON_CMATH_FABS_HPP

#include <hamon/cmath/copysign.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
fabs_impl_ct(FloatType x) HAMON_NOEXCEPT
{
	return hamon::copysign(x, FloatType(1));
}

inline HAMON_CXX11_CONSTEXPR float
fabs_impl(float x) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_fabsf)
	return __builtin_fabsf(x);
#else
	return fabs_impl_ct(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
fabs_impl(double x) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_fabs)
	return __builtin_fabs(x);
#else
	return fabs_impl_ct(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
fabs_impl(long double x) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_fabsl)
	return __builtin_fabsl(x);
#else
	return fabs_impl_ct(x);
#endif
}

}	// namespace detail

/**
 *	@brief	std::fabs のconstexpr版
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
fabs(FloatType arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
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

#endif // HAMON_CMATH_FABS_HPP
