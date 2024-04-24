/**
 *	@file	acos.hpp
 *
 *	@brief	acos関数の定義
 */

#ifndef HAMON_COMPLEX_ACOS_HPP
#define HAMON_COMPLEX_ACOS_HPP

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
acos_unchecked(complex<T> const& x,
	complex<T> i = {0, 1},
	T pi = hamon::numbers::pi_fn<T>()) HAMON_NOEXCEPT
{
	// [complex.transcendentals]/1
	return (pi / 2) + i * hamon::log(i * x + hamon::sqrt(T(1) - (x * x)));
}

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
acos_impl(T x, T y,
	T pi = hamon::numbers::pi_fn<T>(),
	T nan = hamon::numeric_limits<T>::quiet_NaN(),
	T inf = hamon::numeric_limits<T>::infinity()) HAMON_NOEXCEPT
{
	return
		// If z is (±0,+0), the result is (π/2,-0)
		hamon::iszero(x) && hamon::iszero(y) ?
			complex<T>{pi / 2, 0} :
		// If z is (±0,NaN), the result is (π/2,NaN)
		hamon::iszero(x) && hamon::isnan(y) ?
			complex<T>{pi / 2, nan} :
		// If z is (x,+∞) (for any finite x), the result is (π/2,-∞)
		hamon::isfinite(x) && y == inf ?
			complex<T>{pi / 2, -inf} :
		// If z is (x,NaN) (for any nonzero finite x), the result is (NaN,NaN) and FE_INVALID may be raised.
		hamon::isfinite(x) && !hamon::iszero(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		// If z is (-∞,y) (for any positive finite y), the result is (π,-∞)
		x == -inf && hamon::isfinite(y) && !hamon::signbit(y) ?
			complex<T>{pi, -inf} :
		// If z is (+∞,y) (for any positive finite y), the result is (+0,-∞)
		x == +inf && hamon::isfinite(y) && !hamon::signbit(y) ?
			complex<T>{0, -inf} :
		// If z is (-∞,+∞), the result is (3π/4,-∞)
		x == -inf && y == +inf ?
			complex<T>{pi * 3 / 4, -inf} :
		// If z is (+∞,+∞), the result is (π/4,-∞)
		x == +inf && y == +inf ?
			complex<T>{pi / 4, -inf} :
		// If z is (±∞,NaN), the result is (NaN,±∞) (the sign of the imaginary part is unspecified)
		hamon::isinf(x) && hamon::isnan(y) ?
			complex<T>{nan, +inf} :
		// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isnan(x) && hamon::isfinite(y) ?
			complex<T>{nan, nan} :
		// If z is (NaN,+∞), the result is (NaN,-∞)
		hamon::isnan(x) && y == +inf ?
			complex<T>{nan, -inf} :
		// If z is (NaN,NaN), the result is (NaN,NaN)
		hamon::isnan(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		acos_unchecked(complex<T>{x, y});
}

}	// namespace complex_detail

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
acos(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	return complex_detail::acos_impl(x.real(), x.imag());
}

}	// namespace hamon

#endif // HAMON_COMPLEX_ACOS_HPP
