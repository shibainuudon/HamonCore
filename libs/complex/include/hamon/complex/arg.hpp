/**
 *	@file	arg.hpp
 *
 *	@brief	arg関数の定義
 */

#ifndef HAMON_COMPLEX_ARG_HPP
#define HAMON_COMPLEX_ARG_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/imag.hpp>
#include <hamon/complex/real.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cmath/atan2.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.value.ops], values

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T
arg(complex<T> const& x)
{
	return hamon::atan2(hamon::imag(x), hamon::real(x));
}

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, Float)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Float
arg(Float f)
{
	return hamon::arg(complex<Float>{f});
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integer)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
arg(Integer i)
{
	return hamon::arg(complex<double>{static_cast<double>(i)});
}

}	// namespace hamon

#endif // HAMON_COMPLEX_ARG_HPP
