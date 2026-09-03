/**
 *	@file	nextafter.hpp
 *
 *	@brief	nextafter 関数の定義
 */

#ifndef HAMON_CMATH_NEXTAFTER_HPP
#define HAMON_CMATH_NEXTAFTER_HPP

#include <hamon/cmath/copysign.hpp>
#include <hamon/cmath/ilogb.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/issubnormal.hpp>
#include <hamon/cmath/ldexp.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
nextafter_unchecked_ct_impl_next(T x) HAMON_NOEXCEPT
{
	if (hamon::isinf(x))
	{
		return hamon::numeric_limits<T>::lowest();
	}

	if (x == 0)
	{
		return hamon::numeric_limits<T>::denorm_min();
	}

	if (x == hamon::numeric_limits<T>::max())
	{
		return hamon::numeric_limits<T>::infinity();
	}

	if (hamon::issubnormal(x))
	{
		return hamon::copysign(x + hamon::numeric_limits<T>::denorm_min(), x);
	}

	int exp = hamon::ilogb(x);
	if (hamon::ldexp(T(-1), exp) != x)
	{
		++exp;
	}
	exp -= hamon::numeric_limits<T>::digits;

	if (exp <= hamon::numeric_limits<T>::min_exponent)
	{
		return x + hamon::numeric_limits<T>::denorm_min();
	}

	return x + hamon::ldexp(T(1), exp);
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
nextafter_unchecked_ct_impl_prior(T x) HAMON_NOEXCEPT
{
	if (hamon::isinf(x))
	{
		return hamon::numeric_limits<T>::max();
	}

	if (x == 0)
	{
		return -hamon::numeric_limits<T>::denorm_min();
	}

	if (x == hamon::numeric_limits<T>::lowest())
	{
		return -hamon::numeric_limits<T>::infinity();
	}

	if (hamon::issubnormal(x))
	{
		return hamon::copysign(x - hamon::numeric_limits<T>::denorm_min(), x);
	}

	int exp = hamon::ilogb(x);
	if (hamon::ldexp(T(1), exp) != x)
	{
		++exp;
	}
	exp -= hamon::numeric_limits<T>::digits;

	if (exp <= hamon::numeric_limits<T>::min_exponent)
	{
		return x - hamon::numeric_limits<T>::denorm_min();
	}

	return x - hamon::ldexp(T(1), exp);
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
nextafter_unchecked_ct_impl(T x, T y) HAMON_NOEXCEPT
{
	if (x < y)
	{
		return nextafter_unchecked_ct_impl_next(x);
	}
	else if (x == y)
	{
		return y;
	}
	else
	{
		return nextafter_unchecked_ct_impl_prior(x);
	}
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
nextafter_unchecked_ct(T x, T y) HAMON_NOEXCEPT
{
	return nextafter_unchecked_ct_impl(x, y);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
nextafter_unchecked_rt(T x, T y) HAMON_NOEXCEPT
{
	// TODO
	return std::nextafter(x, y);
}

inline HAMON_CXX11_CONSTEXPR float
nextafter_unchecked(float x, float y) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_nextafterf)
	return hamon::is_constant_evaluated() ? nextafter_unchecked_ct(x, y) : __builtin_nextafterf(x, y);
#else
	return hamon::is_constant_evaluated() ? nextafter_unchecked_ct(x, y) : nextafter_unchecked_rt(x, y);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
nextafter_unchecked(double x, double y) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_nextafter)
	return hamon::is_constant_evaluated() ? nextafter_unchecked_ct(x, y) : __builtin_nextafter(x, y);
#else
	return hamon::is_constant_evaluated() ? nextafter_unchecked_ct(x, y) : nextafter_unchecked_rt(x, y);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
nextafter_unchecked(long double x, long double y) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_nextafterl)
	return hamon::is_constant_evaluated() ? nextafter_unchecked_ct(x, y) : __builtin_nextafterl(x, y);
#else
	return hamon::is_constant_evaluated() ? nextafter_unchecked_ct(x, y) : nextafter_unchecked_rt(x, y);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
nextafter_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) || hamon::isnan(y) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		nextafter_unchecked(x, y);
}

}	// namespace detail

template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
nextafter(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::nextafter_impl(x, y);
}

template <
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
nextafter(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::nextafter_impl(static_cast<type>(x), static_cast<type>(y));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
nextafterf(float x, float y) HAMON_NOEXCEPT
{
	return detail::nextafter_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
nextafterl(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::nextafter_impl(x, y);
}

}	// namespace hamon

#endif // HAMON_CMATH_NEXTAFTER_HPP
