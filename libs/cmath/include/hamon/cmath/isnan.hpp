/**
 *	@file	isnan.hpp
 *
 *	@brief	isnan
 */

#ifndef HAMON_CMATH_ISNAN_HPP
#define HAMON_CMATH_ISNAN_HPP

#include <hamon/config.hpp>
#include <type_traits>

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
inline HAMON_CONSTEXPR bool
isnan(float arg) HAMON_NOEXCEPT
{
	return detail::isnan_impl(arg);
}

inline HAMON_CONSTEXPR bool
isnan(double arg) HAMON_NOEXCEPT
{
	return detail::isnan_impl(arg);
}

inline HAMON_CONSTEXPR bool
isnan(long double arg) HAMON_NOEXCEPT
{
	return detail::isnan_impl(arg);
}

template <
	typename IntegralType,
	typename = typename std::enable_if<
		std::is_integral<IntegralType>::value
	>::type
>
inline HAMON_CONSTEXPR bool
isnan(IntegralType) HAMON_NOEXCEPT
{
	return false;
}

}	// namespace hamon

#endif // HAMON_CMATH_ISNAN_HPP
