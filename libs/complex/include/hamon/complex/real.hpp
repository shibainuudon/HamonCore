/**
 *	@file	real.hpp
 *
 *	@brief	real関数の定義
 */

#ifndef HAMON_COMPLEX_REAL_HPP
#define HAMON_COMPLEX_REAL_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.value.ops], values
template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T	// nodiscard as an extension
real(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.value.ops]/1
	return x.real();
}

// [cmplx.over]/2.1
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, Float)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Float	// nodiscard as an extension
real(Float f) HAMON_NOEXCEPT	// noexcept as an extension
{
	return f;
}

// [cmplx.over]/2.2
template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integer)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double	// nodiscard as an extension
real(Integer i) HAMON_NOEXCEPT	// noexcept as an extension
{
	return static_cast<double>(i);
}

}	// namespace hamon

#endif // HAMON_COMPLEX_REAL_HPP
