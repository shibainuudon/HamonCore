/**
 *	@file	isinf.hpp
 *
 *	@brief	isinf
 */

#ifndef HAMON_CMATH_ISINF_HPP
#define HAMON_CMATH_ISINF_HPP

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

namespace detail
{

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR bool
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
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
isinf(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::isinf_impl(static_cast<type>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISINF_HPP
