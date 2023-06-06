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
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T
imag(complex<T> const& x)
{
	return x.imag();
}

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, Float)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Float
imag(Float)
{
	return Float{};
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integer)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
imag(Integer)
{
	return 0.0;
}

}	// namespace hamon

#endif // HAMON_COMPLEX_IMAG_HPP
