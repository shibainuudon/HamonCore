/**
 *	@file	nextup.hpp
 *
 *	@brief	nextup 関数の定義
 */

#ifndef HAMON_CMATH_NEXTUP_HPP
#define HAMON_CMATH_NEXTUP_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/ieee754/binary.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
nextup_impl(T x) HAMON_NOEXCEPT
{
	hamon::ieee754::binary<T> a(x);
	a.next_up();
	return a.to_float();
}

}	// namespace detail

template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR			// nodiscard as an extension
FloatType nextup(FloatType x) HAMON_NOEXCEPT	// noexcept as an extension
{
	return detail::nextup_impl(x);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR			// nodiscard as an extension
double nextup(IntegralType x) HAMON_NOEXCEPT	// noexcept as an extension
{
	return detail::nextup_impl(static_cast<double>(x));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
float nextupf(float x) HAMON_NOEXCEPT			// noexcept as an extension
{
	return detail::nextup_impl(x);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
long double nextupl(long double x) HAMON_NOEXCEPT	// noexcept as an extension
{
	return detail::nextup_impl(x);
}

}	// namespace hamon

#endif // HAMON_CMATH_NEXTUP_HPP
