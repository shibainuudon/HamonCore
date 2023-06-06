/**
 *	@file	asinh.hpp
 *
 *	@brief	asinh関数の定義
 */

#ifndef HAMON_COMPLEX_ASINH_HPP
#define HAMON_COMPLEX_ASINH_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/log.hpp>
#include <hamon/complex/sqrt.hpp>
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
asinh_unchecked(complex<T> const& x)
{
	return hamon::log(x + hamon::sqrt((x * x) + T(1)));
}

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
asinh_impl(T x, T y,
	T pi = hamon::numbers::pi_fn<T>(),
	T nan = std::numeric_limits<T>::quiet_NaN(),
	T inf = std::numeric_limits<T>::infinity())
{
	return
		// If z is (+0,+0), the result is (+0,+0)
		hamon::iszero(x) && !hamon::signbit(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{+0.0, +0.0} :
		// If z is (x,+∞) (for any positive finite x), the result is (+∞,π/2)
		hamon::isfinite(x) && !hamon::signbit(x) && y == +inf ?
			complex<T>{+inf, pi / 2} :
		// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isfinite(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		// If z is (+∞,y) (for any positive finite y), the result is (+∞,+0)
		x == +inf && hamon::isfinite(y) && !hamon::signbit(y) ?
			complex<T>{+inf, +0.0} :
		// If z is (+∞,+∞), the result is (+∞,π/4)
		x == +inf && y == +inf ?
			complex<T>{+inf, pi / 4} :
		// If z is (+∞,NaN), the result is (+∞,NaN)
		x == +inf && hamon::isnan(y) ?
			complex<T>{+inf, nan} :
		// If z is (NaN,+0), the result is (NaN,+0)
		hamon::isnan(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{nan, +0.0} :
		// If z is (NaN,y) (for any finite nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isnan(x) && hamon::isfinite(y) && !hamon::iszero(y) ?
			complex<T>{nan, nan} :
		// If z is (NaN,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified)
		hamon::isnan(x) && y == +inf ?
			complex<T>{+inf, nan} :
		// If z is (NaN,NaN), the result is (NaN,NaN)
		hamon::isnan(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		asinh_unchecked(complex<T>{x, y});
}

}	// namespace complex_detail

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
asinh(complex<T> const& x)
{
	return complex_detail::asinh_impl(x.real(), x.imag());
}

}	// namespace hamon

#endif // HAMON_COMPLEX_ASINH_HPP
