/**
 *	@file	proj.hpp
 *
 *	@brief	proj関数の定義
 */

#ifndef HAMON_COMPLEX_PROJ_HPP
#define HAMON_COMPLEX_PROJ_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/real.hpp>
#include <hamon/complex/imag.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/copysign.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.value.ops], values

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
proj(complex<T> const& x)
{
    return
		hamon::isinf(hamon::real(x)) || hamon::isinf(hamon::imag(x)) ?
			hamon::complex<T>(hamon::numeric_limits<T>::infinity(), hamon::copysign(T(), hamon::imag(x))) :
		x;
}

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, Float)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<Float>
proj(Float f)
{
	return hamon::proj(complex<Float>{f});
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integer)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<double>
proj(Integer i)
{
	return hamon::proj(complex<double>{static_cast<double>(i)});
}

}	// namespace hamon

#endif // HAMON_COMPLEX_PROJ_HPP
