/**
 *	@file	cosh.hpp
 *
 *	@brief	cosh関数の定義
 */

#ifndef HAMON_COMPLEX_COSH_HPP
#define HAMON_COMPLEX_COSH_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/exp.hpp>
#include <hamon/cmath/isfinite.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

// [complex.transcendentals], transcendentals

namespace complex_detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
cosh_unchecked(complex<T> const& x)
{
	return (hamon::exp(x) + hamon::exp(-x)) / T(2);
}

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
cosh_impl(T x, T y,
	T nan = std::numeric_limits<T>::quiet_NaN(),
	T inf = std::numeric_limits<T>::infinity())
{
	return
		// If z is (+0,+0), the result is (1,+0)
		hamon::iszero(x) && !hamon::signbit(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{+1.0, +0.0} :
		// If z is (+0,+∞), the result is (NaN,±0) (the sign of the imaginary part is unspecified) and FE_INVALID is raised
		hamon::iszero(x) && !hamon::signbit(x) && y == +inf ?
			complex<T>{nan, +0.0} :
		// If z is (+0,NaN), the result is (NaN,±0) (the sign of the imaginary part is unspecified)
		hamon::iszero(x) && !hamon::signbit(x) && hamon::isnan(y) ?
			complex<T>{nan, +0.0} :
		// If z is (x,+∞) (for any finite non-zero x), the result is (NaN,NaN) and FE_INVALID is raised
		!hamon::iszero(x) && hamon::isfinite(x) && y == +inf ?
			complex<T>{nan, nan} :
		// If z is (x,NaN) (for any finite non-zero x), the result is (NaN,NaN) and FE_INVALID may be raised
		!hamon::iszero(x) && hamon::isfinite(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		// If z is (+∞,+0), the result is (+∞,+0)
		x == +inf && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{+inf, +0.0} :
		// If z is (+∞,y) (for any finite non-zero y), the result is +∞cis(y)
		x == +inf && !hamon::iszero(y) && hamon::isfinite(y) ?
			+inf * complex<T>{hamon::cos(y), hamon::sin(y)} :
		// If z is (+∞,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
		x == +inf && y == +inf ?
			complex<T>{+inf, nan} :
		// If z is (+∞,NaN), the result is (+∞,NaN)
		x == +inf && hamon::isnan(y) ?
			complex<T>{+inf, nan} :
		// If z is (NaN,+0), the result is (NaN,±0) (the sign of the imaginary part is unspecified)
		hamon::isnan(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{nan, +0.0} :
		// If z is (NaN,+y) (for any finite non-zero y), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isnan(x) && !hamon::iszero(y) && hamon::isfinite(y) ?
			complex<T>{nan, nan} :
		// If z is (NaN,NaN), the result is (NaN,NaN)
		hamon::isnan(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		cosh_unchecked(complex<T>{x, y});
}

}	// namespace complex_detail

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
cosh(complex<T> const& x)
{
	return complex_detail::cosh_impl(x.real(), x.imag());
}

}	// namespace hamon

#endif // HAMON_COMPLEX_COSH_HPP
