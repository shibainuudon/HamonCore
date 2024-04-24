/**
 *	@file	imag.hpp
 *
 *	@brief	imag関数の定義
 */

#ifndef HAMON_COMPLEX_IMAG_HPP
#define HAMON_COMPLEX_IMAG_HPP

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
imag(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.value.ops]/2
	return x.imag();
}

// [cmplx.over]/2.1
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, Float)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Float	// nodiscard as an extension
imag(Float) HAMON_NOEXCEPT	// noexcept as an extension
{
	return Float{};
}

// [cmplx.over]/2.2
template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integer)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double	// nodiscard as an extension
imag(Integer) HAMON_NOEXCEPT	// noexcept as an extension
{
	return 0.0;
}

}	// namespace hamon

#endif // HAMON_COMPLEX_IMAG_HPP
