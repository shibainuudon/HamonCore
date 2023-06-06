/**
 *	@file	tanh.hpp
 *
 *	@brief	tanh関数の定義
 */

#ifndef HAMON_COMPLEX_TANH_HPP
#define HAMON_COMPLEX_TANH_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/exp.hpp>
#include <hamon/cmath/isfinite.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

// [complex.transcendentals], transcendentals

namespace complex_detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
tanh_unchecked(complex<T> const& x)
{
	return (hamon::exp(x) - hamon::exp(-x)) / (hamon::exp(x) + hamon::exp(-x));
}

template <typename T>
HAMON_CXX11_CONSTEXPR complex<T>
tanh_impl(T x, T y,
	T nan = std::numeric_limits<T>::quiet_NaN(),
	T inf = std::numeric_limits<T>::infinity())
{
	return
		// If z is (+0,+0), the result is (+0,+0)
		hamon::iszero(x) && !hamon::signbit(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{+0.0, +0.0} :
		// If z is (x,+∞) (for any non-zero finite x), the result is (NaN,NaN) and FE_INVALID is raised
		hamon::isfinite(x) && !hamon::iszero(x) && y == +inf ?
			complex<T>{nan, nan} :
		// If z is (0,∞), the result should be (0,NaN)
		hamon::iszero(x) && y == +inf ?
			complex<T>{+0.0, nan} :
		// If z is (x,NaN) (for any non-zero finite x), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isfinite(x) && !hamon::iszero(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		// If z is (0,NaN), the result should be (0,NaN)
		hamon::iszero(x) && hamon::isnan(y) ?
			complex<T>{+0.0, nan} :
		// If z is (+∞,y) (for any finite positive y), the result is (1,+0)
		x == +inf && hamon::isfinite(y) && !hamon::signbit(y) ?
			complex<T>{+1.0, +0.0} :
		// If z is (+∞,+∞), the result is (1,±0) (the sign of the imaginary part is unspecified)
		x == +inf && y == +inf ?
			complex<T>{+1.0, +0.0} :
		// If z is (+∞,NaN), the result is (1,±0) (the sign of the imaginary part is unspecified)
		x == +inf && hamon::isnan(y) ?
			complex<T>{+1.0, +0.0} :
		// If z is (NaN,+0), the result is (NaN,+0)
		hamon::isnan(x) && hamon::iszero(y) && !hamon::signbit(y) ?
			complex<T>{nan, +0.0} :
		// If z is (NaN,y) (for any non-zero y), the result is (NaN,NaN) and FE_INVALID may be raised
		hamon::isnan(x) && !hamon::iszero(y) ?
			complex<T>{nan, nan} :
		// If z is (NaN,NaN), the result is (NaN,NaN)
		hamon::isnan(x) && hamon::isnan(y) ?
			complex<T>{nan, nan} :
		tanh_unchecked(complex<T>{x, y});
}

}	// namespace complex_detail

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
tanh(complex<T> const& x)
{
	return complex_detail::tanh_impl(x.real(), x.imag());
}

}	// namespace hamon

#endif // HAMON_COMPLEX_TANH_HPP
