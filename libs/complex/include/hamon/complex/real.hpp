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
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T
real(complex<T> const& x)
{
	return x.real();
}

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, Float)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Float
real(Float f)
{
	return f;
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integer)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
real(Integer i)
{
	return static_cast<double>(i);
}

}	// namespace hamon

#endif // HAMON_COMPLEX_REAL_HPP
