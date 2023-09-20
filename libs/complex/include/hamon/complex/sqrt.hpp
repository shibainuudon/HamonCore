/**
 *	@file	sqrt.hpp
 *
 *	@brief	sqrt関数の定義
 */

#ifndef HAMON_COMPLEX_SQRT_HPP
#define HAMON_COMPLEX_SQRT_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/polar.hpp>
#include <hamon/complex/abs.hpp>
#include <hamon/complex/arg.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/isfinite.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.transcendentals], transcendentals

namespace complex_detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
sqrt_unchecked(complex<T> const& x)
{
	return hamon::polar(hamon::sqrt(hamon::abs(x)), hamon::arg(x) / T(2));
}

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
sqrt_impl(T x, T y,
	T nan = hamon::numeric_limits<T>::quiet_NaN(),
	T inf = hamon::numeric_limits<T>::infinity())
{
	return
		// If z is (±0,+0), the result is (+0,+0)
		hamon::iszero(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>(+0.0, +0.0) :
		// If z is (x,+∞), the result is (+∞,+∞) even if x is NaN
		y == +inf ?
			complex<T>(+inf, +inf) :
		// If z is (x,NaN), the result is (NaN,NaN) (unless x is ±∞) and FE_INVALID may be raised
		!hamon::isinf(x) && hamon::isnan(y) ?
			complex<T>(nan, nan) :
		// If z is (-∞,y), the result is (+0,+∞) for finite positive y
		x == -inf && hamon::isfinite(y) && !hamon::signbit(y) ?
			complex<T>(+0.0, +inf) :
		// If z is (+∞,y), the result is (+∞,+0) for finite positive y
		x == +inf && hamon::isfinite(y) && !hamon::signbit(y) ?
			complex<T>(+inf, +0.0) :
		// If z is (-∞,NaN), the result is (NaN,∞) (sign of imaginary part unspecified)
		x == -inf && hamon::isnan(y) ?
			complex<T>(nan, +inf) :
		// If z is (+∞,NaN), the result is (+∞,NaN)
		x == +inf && hamon::isnan(y) ?
			complex<T>(+inf, nan) :
		// If z is (NaN,y), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isnan(x) && !hamon::isnan(y) ?
			complex<T>(nan, nan) :
		// If z is (NaN,NaN), the result is (NaN,NaN)
		hamon::isnan(x) && hamon::isnan(y) ?
			complex<T>(nan, nan) :
		sqrt_unchecked(complex<T>{x, y});
}

}	// namespace complex_detail

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
sqrt(complex<T> const& x)
{
	return complex_detail::sqrt_impl(x.real(), x.imag());
}

}	// namespace hamon

#endif // HAMON_COMPLEX_SQRT_HPP
