/**
 *	@file	conj.hpp
 *
 *	@brief	conj関数の定義
 */

#ifndef HAMON_COMPLEX_CONJ_HPP
#define HAMON_COMPLEX_CONJ_HPP

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
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
conj(complex<T> const& x)
{
	return hamon::complex<T>(hamon::real(x), -hamon::imag(x));
}

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, Float)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<Float>
conj(Float f)
{
	return hamon::conj(complex<Float>{f});
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integer)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<double>
conj(Integer i)
{
	return hamon::conj(complex<double>{static_cast<double>(i)});
}

}	// namespace hamon

#endif // HAMON_COMPLEX_CONJ_HPP
