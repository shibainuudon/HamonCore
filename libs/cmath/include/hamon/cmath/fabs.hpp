/**
 *	@file	fabs.hpp
 *
 *	@brief	fabs
 */

#ifndef HAMON_CMATH_FABS_HPP
#define HAMON_CMATH_FABS_HPP

#include <hamon/cmath/copysign.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CONSTEXPR float
fabs_impl(float x) HAMON_NOEXCEPT
{
	return __builtin_fabsf(x);
}

inline HAMON_CONSTEXPR double
fabs_impl(double x) HAMON_NOEXCEPT
{
	return __builtin_fabs(x);
}

inline HAMON_CONSTEXPR long double
fabs_impl(long double x) HAMON_NOEXCEPT
{
	return __builtin_fabsl(x);
}

#else

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
fabs_impl(FloatType x) HAMON_NOEXCEPT
{
	return hamon::copysign(x, FloatType(1));
}

#endif

}	// namespace detail

/**
 *	@brief	std::fabs のconstexpr版
 */
HAMON_NODISCARD inline HAMON_CONSTEXPR float
fabs(float arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR float
fabsf(float arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR double
fabs(double arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
fabs(long double arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
fabsl(long double arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR double
fabs(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::fabs_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_FABS_HPP
