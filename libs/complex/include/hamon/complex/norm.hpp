/**
 *	@file	norm.hpp
 *
 *	@brief	norm関数の定義
 */

#ifndef HAMON_COMPLEX_NORM_HPP
#define HAMON_COMPLEX_NORM_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/real.hpp>
#include <hamon/complex/imag.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.value.ops], values

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T	// nodiscard as an extension
norm(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.value.ops]/5
	return hamon::real(x) * hamon::real(x) + hamon::imag(x) * hamon::imag(x);
}

// [cmplx.over]/2.1
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, Float)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Float	// nodiscard as an extension
norm(Float f) HAMON_NOEXCEPT	// noexcept as an extension
{
	return hamon::norm(complex<Float>{f});
}

// [cmplx.over]/2.2
template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integer)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double	// nodiscard as an extension
norm(Integer i) HAMON_NOEXCEPT	// noexcept as an extension
{
	return hamon::norm(complex<double>{static_cast<double>(i)});
}

}	// namespace hamon

#endif // HAMON_COMPLEX_NORM_HPP
