/**
 *	@file	isinf.hpp
 *
 *	@brief	isinf
 */

#ifndef HAMON_CMATH_ISINF_HPP
#define HAMON_CMATH_ISINF_HPP

#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

namespace detail
{

template <typename FloatType>
inline HAMON_CONSTEXPR bool
isinf_impl(FloatType x) HAMON_NOEXCEPT
{
#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isinf(x);
#else
	return
		x ==  std::numeric_limits<FloatType>::infinity() ||
		x == -std::numeric_limits<FloatType>::infinity();
#endif
}

}	// namespace detail

/**
 *	@brief	std::isinf のconstexpr版
 */
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isinf(float arg) HAMON_NOEXCEPT
{
	return detail::isinf_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isinf(double arg) HAMON_NOEXCEPT
{
	return detail::isinf_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isinf(long double arg) HAMON_NOEXCEPT
{
	return detail::isinf_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isinf(IntegralType) HAMON_NOEXCEPT
{
	return false;
}

}	// namespace hamon

#endif // HAMON_CMATH_ISINF_HPP
