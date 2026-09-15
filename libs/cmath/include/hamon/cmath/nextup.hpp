/**
 *	@file	nextup.hpp
 *
 *	@brief	nextup 関数の定義
 */

#ifndef HAMON_CMATH_NEXTUP_HPP
#define HAMON_CMATH_NEXTUP_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/ieee754/binary.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
nextup_impl(T x) HAMON_NOEXCEPT
{
	if (hamon::isnan(x))
	{
		return x;
	}

	if (hamon::isinf(x) && !hamon::signbit(x))
	{
		return hamon::numeric_limits<T>::infinity();
	}

	if (x == 0)
	{
		return hamon::numeric_limits<T>::denorm_min();
	}

	if (x == hamon::numeric_limits<T>::max())
	{
		return hamon::numeric_limits<T>::infinity();
	}

	hamon::ieee754::binary<T> a(x);
	hamon::ieee754::binary<T> b(a.sign(), a.exponent(), a.sign() == 1 ? a.fraction() - 1 : a.fraction() + 1);
	return b.to_float();
}

}	// namespace detail

template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR			// nodiscard as an extension
FloatType nextup(FloatType x) HAMON_NOEXCEPT	// noexcept as an extension
{
	return detail::nextup_impl(x);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR			// nodiscard as an extension
double nextup(IntegralType x) HAMON_NOEXCEPT	// noexcept as an extension
{
	return detail::nextup_impl(static_cast<double>(x));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
float nextupf(float x) HAMON_NOEXCEPT			// noexcept as an extension
{
	return detail::nextup_impl(x);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
long double nextupl(long double x) HAMON_NOEXCEPT	// noexcept as an extension
{
	return detail::nextup_impl(x);
}

}	// namespace hamon

#endif // HAMON_CMATH_NEXTUP_HPP
