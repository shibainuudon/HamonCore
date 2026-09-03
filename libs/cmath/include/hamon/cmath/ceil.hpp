/**
 *	@file	ceil.hpp
 *
 *	@brief	ceil
 */

#ifndef HAMON_CMATH_CEIL_HPP
#define HAMON_CMATH_CEIL_HPP

#include <hamon/cmath/almost_equal.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
ceil_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T const x0 = trunc_unchecked(x);
	return
		x < 0 || hamon::almost_equal(x, x0) ?
			x0 :
		x0 + T(1);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
ceil_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::ceil(x);
}

inline HAMON_CXX11_CONSTEXPR float
ceil_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_ceilf(x);
#elif HAMON_HAS_BUILTIN(__builtin_ceilf)
	return hamon::is_constant_evaluated() ? ceil_unchecked_ct(x) : __builtin_ceilf(x);
#else
	return hamon::is_constant_evaluated() ? ceil_unchecked_ct(x) : ceil_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
ceil_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_ceil(x);
#elif HAMON_HAS_BUILTIN(__builtin_ceil)
	return hamon::is_constant_evaluated() ? ceil_unchecked_ct(x) : __builtin_ceil(x);
#else
	return hamon::is_constant_evaluated() ? ceil_unchecked_ct(x) : ceil_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
ceil_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_ceill(x);
#elif HAMON_HAS_BUILTIN(__builtin_ceill)
	return hamon::is_constant_evaluated() ? ceil_unchecked_ct(x) : __builtin_ceill(x);
#else
	return hamon::is_constant_evaluated() ? ceil_unchecked_ct(x) : ceil_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
ceil_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		(hamon::iszero(x) || hamon::isnan(x) || hamon::isinf(x)) ?
			x :
		ceil_unchecked(x);
}

}	// namespace detail

template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
ceil(FloatType arg) HAMON_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
ceil(IntegralType arg) HAMON_NOEXCEPT
{
	return static_cast<double>(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
ceilf(float arg) HAMON_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
ceill(long double arg) HAMON_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_CEIL_HPP
