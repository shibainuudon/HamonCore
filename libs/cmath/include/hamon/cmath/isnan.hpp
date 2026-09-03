/**
 *	@file	isnan.hpp
 *
 *	@brief	isnan
 */

#ifndef HAMON_CMATH_ISNAN_HPP
#define HAMON_CMATH_ISNAN_HPP

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
isnan_impl_ct(FloatType x) HAMON_NOEXCEPT
{
	return !(x == x);
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
isnan_impl(FloatType x) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_isnan)
	return __builtin_isnan(x);
#else
	return isnan_impl_ct(x);
#endif
}

}	// namespace detail

/**
 *	@brief	std::isnan のconstexpr版
 */
template <HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
isnan(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::isnan_impl(static_cast<type>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISNAN_HPP
