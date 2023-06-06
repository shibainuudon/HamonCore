/**
 *	@file	atanh.hpp
 *
 *	@brief	atanh関数の定義
 */

#ifndef HAMON_COMPLEX_ATANH_HPP
#define HAMON_COMPLEX_ATANH_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/log.hpp>
#include <hamon/cmath/isfinite.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

// [complex.transcendentals], transcendentals

namespace complex_detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
atanh_unchecked(complex<T> const& x)
{
	return (hamon::log(T(1) + x) - hamon::log(T(1) - x)) / T(2);
}

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
atanh_impl(T x, T y,
	T pi = hamon::numbers::pi_fn<T>(),
	T nan = std::numeric_limits<T>::quiet_NaN(),
	T inf = std::numeric_limits<T>::infinity())
{
	return
		// If z is (+0,+0), the result is (+0,+0)
		hamon::iszero(x) && !hamon::signbit(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{+0.0, +0.0} :
		// If z is (+0,NaN), the result is (+0,NaN)
		hamon::iszero(x) && !hamon::signbit(x) && hamon::isnan(y) ?
			complex<T>{+0.0, nan} :
		// If z is (+1,+0), the result is (+∞,+0) and FE_DIVBYZERO is raised
		x == T(+1.0) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{+inf, +0.0} :
		// If z is (x,+∞) (for any finite positive x), the result is (+0,π/2)
		hamon::isfinite(x) && !hamon::signbit(x) && y == +inf ?
			complex<T>{+0.0, pi / 2} :
		// If z is (x,NaN) (for any finite nonzero x), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isfinite(x) && !hamon::iszero(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		// If z is (+∞,y) (for any finite positive y), the result is (+0,π/2)
		x == +inf && hamon::isfinite(y) && !hamon::signbit(y) ?
			complex<T>{+0.0, pi / 2} :
		// If z is (+∞,+∞), the result is (+0,π/2)
		x == +inf && y == +inf ?
			complex<T>{+0.0, pi / 2} :
		// If z is (+∞,NaN), the result is (+0,NaN)
		x == +inf && hamon::isnan(y) ?
			complex<T>{+0.0, nan} :
		// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isnan(x) && hamon::isfinite(y) ?
			complex<T>{nan, nan} :
		// If z is (NaN,+∞), the result is (±0,π/2) (the sign of the real part is unspecified)
		hamon::isnan(x) && y == +inf ?
			complex<T>{+0.0, pi / 2} :
		// If z is (NaN,NaN), the result is (NaN,NaN)
		hamon::isnan(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		atanh_unchecked(complex<T>{x, y});
}

}	// namespace complex_detail

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
atanh(complex<T> const& x)
{
	return complex_detail::atanh_impl(x.real(), x.imag());
}

}	// namespace hamon

#endif // HAMON_COMPLEX_ATANH_HPP
