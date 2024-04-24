﻿/**
 *	@file	exp.hpp
 *
 *	@brief	exp関数の定義
 */

#ifndef HAMON_COMPLEX_EXP_HPP
#define HAMON_COMPLEX_EXP_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/isfinite.hpp>
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
exp_unchecked(complex<T> const& x) HAMON_NOEXCEPT
{
	// [complex.transcendentals]/15
    return hamon::exp(x.real()) * hamon::complex<T>(hamon::cos(x.imag()), hamon::sin(x.imag()));
}

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
exp_impl(T x, T y,
	T nan = hamon::numeric_limits<T>::quiet_NaN(),
	T inf = hamon::numeric_limits<T>::infinity()) HAMON_NOEXCEPT
{
	return
		// If z is (±0,+0), the result is (1,+0)
		hamon::iszero(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{1.0, +0.0} :
		// If z is (x,+∞) (for any finite x), the result is (NaN,NaN) and FE_INVALID is raised.
		hamon::isfinite(x) && y == +inf ?
			complex<T>{nan, nan} :
		// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised.
		hamon::isfinite(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		// If z is (+∞,+0), the result is (+∞,+0)
		x == +inf && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{+inf, +0.0} :
		// If z is (-∞,y) (for any finite y), the result is +0cis(y)
		x == -inf && hamon::isfinite(y) ?
			T(+0) * complex<T>{hamon::cos(y), hamon::sin(y)} :
		// If z is (+∞,y) (for any finite nonzero y), the result is +∞cis(y)
		x == +inf && hamon::isfinite(y) && !hamon::iszero(y) ?
			+inf * complex<T>{hamon::cos(y), hamon::sin(y)} :
		// If z is (-∞,+∞), the result is (±0,±0) (signs are unspecified)
		x == -inf && y == +inf ?
			complex<T>{+0.0, +0.0} :
		// If z is (+∞,+∞), the result is (±∞,NaN) and FE_INVALID is raised (the sign of the real part is unspecified)
		x == +inf && y == +inf ?
			complex<T>{+inf, nan} :
		// If z is (-∞,NaN), the result is (±0,±0) (signs are unspecified)
		x == -inf && hamon::isnan(y) ?
			complex<T>{+0.0, +0.0} :
		// If z is (+∞,NaN), the result is (±∞,NaN) (the sign of the real part is unspecified)
		x == +inf && hamon::isnan(y) ?
			complex<T>{+inf, nan} :
		// If z is (NaN,+0), the result is (NaN,+0)
		hamon::isnan(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{nan, +0.0} :
		// If z is (NaN,y) (for any nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isnan(x) && !hamon::iszero(y) ?
			complex<T>{nan, nan} :
		// If z is (NaN,NaN), the result is (NaN,NaN)
		hamon::isnan(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		exp_unchecked(complex<T>{x, y});
}

}	// namespace complex_detail

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
exp(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	return complex_detail::exp_impl(x.real(), x.imag());
}

}	// namespace hamon

#endif // HAMON_COMPLEX_EXP_HPP
