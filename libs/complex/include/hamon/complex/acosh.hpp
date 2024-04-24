/**
 *	@file	acosh.hpp
 *
 *	@brief	acosh関数の定義
 */

#ifndef HAMON_COMPLEX_ACOSH_HPP
#define HAMON_COMPLEX_ACOSH_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/log.hpp>
#include <hamon/complex/sqrt.hpp>
#include <hamon/cmath/isfinite.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.transcendentals], transcendentals

namespace complex_detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
acosh_unchecked(complex<T> const& x) HAMON_NOEXCEPT
{
	// [complex.transcendentals]/7
	return hamon::log(x + hamon::sqrt(x + T(1)) * hamon::sqrt(x - T(1)));
}

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
acosh_impl(T x, T y,
	T pi = hamon::numbers::pi_fn<T>(),
	T nan = hamon::numeric_limits<T>::quiet_NaN(),
	T inf = hamon::numeric_limits<T>::infinity()) HAMON_NOEXCEPT
{
	return
		// If z is (±0,+0), the result is (+0,π/2)
		hamon::iszero(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{+0.0, pi / 2} :
		// If z is (x,+∞) (for any finite x), the result is (+∞,π/2)
		hamon::isfinite(x) && y == +inf ?
			complex<T>{+inf, pi / 2} :
		// If z is (x,NaN) (for any non-zero finite x), the result is (NaN,NaN) and FE_INVALID may be raised.
		hamon::isfinite(x) && !hamon::iszero(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		// If z is (0,NaN), the result should be (NaN,π/2)
		hamon::iszero(x) && hamon::isnan(y) ?
			complex<T>{nan, pi / 2} :
		// If z is (-∞,y) (for any positive finite y), the result is (+∞,π)
		x == -inf && hamon::isfinite(y) && !hamon::signbit(y) ?
			complex<T>{+inf, pi} :
		// If z is (+∞,y) (for any positive finite y), the result is (+∞,+0)
		x == +inf && hamon::isfinite(y) && !hamon::signbit(y) ?
			complex<T>{+inf, +0.0} :
		// If z is (-∞,+∞), the result is (+∞,3π/4)
		x == -inf && y == +inf ?
			complex<T>{+inf, pi * 3 / 4} :
		// If z is (±∞,NaN), the result is (+∞,NaN)
		hamon::isinf(x) && hamon::isnan(y) ?
			complex<T>{+inf, nan} :
		// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised.
		hamon::isnan(x) && hamon::isfinite(y) ?
			complex<T>{nan, nan} :
		// If z is (NaN,+∞), the result is (+∞,NaN)
		hamon::isnan(x) && y == +inf ?
			complex<T>{+inf, nan} :
		// If z is (NaN,NaN), the result is (NaN,NaN)
		hamon::isnan(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		acosh_unchecked(complex<T>{x, y});
}

}	// namespace complex_detail

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
acosh(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	return complex_detail::acosh_impl(x.real(), x.imag());
}

}	// namespace hamon

#endif // HAMON_COMPLEX_ACOSH_HPP
