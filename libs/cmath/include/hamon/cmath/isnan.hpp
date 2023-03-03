/**
 *	@file	isnan.hpp
 *
 *	@brief	isnan
 */

#ifndef HAMON_CMATH_ISNAN_HPP
#define HAMON_CMATH_ISNAN_HPP

#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
inline HAMON_CONSTEXPR bool
isnan_impl(FloatType x) HAMON_NOEXCEPT
{
#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isnan(x);
#else
	return !(x == x);
#endif
}

}	// namespace detail

/**
 *	@brief	std::isnan のconstexpr版
 */
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isnan(float arg) HAMON_NOEXCEPT
{
	return detail::isnan_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isnan(double arg) HAMON_NOEXCEPT
{
	return detail::isnan_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isnan(long double arg) HAMON_NOEXCEPT
{
	return detail::isnan_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isnan(IntegralType) HAMON_NOEXCEPT
{
	return false;
}

}	// namespace hamon

#endif // HAMON_CMATH_ISNAN_HPP
