/**
 *	@file	sinh.hpp
 *
 *	@brief	sinh関数の定義
 */

#ifndef HAMON_COMPLEX_SINH_HPP
#define HAMON_COMPLEX_SINH_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/exp.hpp>
#include <hamon/cmath/isfinite.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

// [complex.transcendentals], transcendentals

namespace complex_detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
sinh_unchecked(complex<T> const& x)
{
	return (hamon::exp(x) - hamon::exp(-x)) / T(2);
}

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
sinh_impl(T x, T y,
	T nan = std::numeric_limits<T>::quiet_NaN(),
	T inf = std::numeric_limits<T>::infinity())
{
	return
		// If z is (+0,+0), the result is (+0,+0)
		hamon::iszero(x) && !hamon::signbit(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{+0.0, +0.0} :
		// If z is (+0,+∞), the result is (±0,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
		hamon::iszero(x) && !hamon::signbit(x) && y == +inf ?
			complex<T>{+0.0, nan} :
		// If z is (+0,NaN), the result is (±0,NaN)
		hamon::iszero(x) && !hamon::signbit(x) && hamon::isnan(y) ?
			complex<T>{+0.0, nan} :
		// If z is (x,+∞) (for any positive finite x), the result is (NaN,NaN) and FE_INVALID is raised
		hamon::isfinite(x) && !hamon::signbit(x) && y == +inf ?
			complex<T>{nan, nan} :
		// If z is (x,NaN) (for any positive finite x), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isfinite(x) && !hamon::signbit(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		// If z is (+∞,+0), the result is (+∞,+0)
		x == +inf && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{+inf, +0.0} :
		// If z is (+∞,y) (for any positive finite y), the result is +∞cis(y)
		x == +inf && hamon::isfinite(y) && !hamon::signbit(y) ?
			+inf * complex<T>{hamon::cos(y), hamon::sin(y)} :
		// If z is (+∞,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
		x == +inf && y == +inf ?
			complex<T>{+inf, nan} :
		// If z is (+∞,NaN), the result is (±∞,NaN) (the sign of the real part is unspecified)
		x == +inf && hamon::isnan(y) ?
			complex<T>{+inf, nan} :
		// If z is (NaN,+0), the result is (NaN,+0)
		hamon::isnan(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{nan, +0.0} :
		// If z is (NaN,y) (for any finite nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isnan(x) && !hamon::iszero(y) && hamon::isfinite(y) ?
			complex<T>{nan, nan} :
		// If z is (NaN,NaN), the result is (NaN,NaN)
		hamon::isnan(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		sinh_unchecked(complex<T>{x, y});
}

}	// namespace complex_detail

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
sinh(complex<T> const& x)
{
	return complex_detail::sinh_impl(x.real(), x.imag());
}

}	// namespace hamon

#endif // HAMON_COMPLEX_SINH_HPP
