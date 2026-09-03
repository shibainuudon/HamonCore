/**
 *	@file	isinf.hpp
 *
 *	@brief	isinf
 */

#ifndef HAMON_CMATH_ISINF_HPP
#define HAMON_CMATH_ISINF_HPP

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
isinf_impl_ct(FloatType x) HAMON_NOEXCEPT
{
	return
		x ==  hamon::numeric_limits<FloatType>::infinity() ||
		x == -hamon::numeric_limits<FloatType>::infinity();
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
isinf_impl(FloatType x) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_isinf)
	return __builtin_isinf(x);
#else
	return isinf_impl_ct(x);
#endif
}

}	// namespace detail

/**
 *	@brief	std::isinf のconstexpr版
 */
template <HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
isinf(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::isinf_impl(static_cast<type>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISINF_HPP
