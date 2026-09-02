/**
 *	@file	copysign.hpp
 *
 *	@brief	copysign
 */

#ifndef HAMON_CMATH_COPYSIGN_HPP
#define HAMON_CMATH_COPYSIGN_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/ieee754/binary.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX14_CONSTEXPR FloatType
copysign_impl_fallback(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	using Binary = hamon::ieee754::binary<FloatType>;
	Binary a(x);
	Binary b(y);
	a.set_sign(b.sign());
	return a.to_float();
}

inline HAMON_CXX11_CONSTEXPR float
copysign_impl(float x, float y) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_copysignf)
	return __builtin_copysignf(x, y);
#else
	return copysign_impl_fallback(x, y);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
copysign_impl(double x, double y) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_copysign)
	return __builtin_copysign(x, y);
#else
	return copysign_impl_fallback(x, y);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
copysign_impl(long double x, long double y) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_copysignl)
	return __builtin_copysignl(x, y);
#else
	return copysign_impl_fallback(x, y);
#endif
}

}	// namespace detail

template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
copysign(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

template <
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
copysign(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::copysign_impl(static_cast<type>(x), static_cast<type>(y));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
copysignf(float x, float y) HAMON_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
copysignl(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

}	// namespace hamon

#endif // HAMON_CMATH_COPYSIGN_HPP
