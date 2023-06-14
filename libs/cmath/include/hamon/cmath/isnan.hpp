/**
 *	@file	isnan.hpp
 *
 *	@brief	isnan
 */

#ifndef HAMON_CMATH_ISNAN_HPP
#define HAMON_CMATH_ISNAN_HPP

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR bool
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
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
isnan(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::isnan_impl(static_cast<type>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISNAN_HPP
