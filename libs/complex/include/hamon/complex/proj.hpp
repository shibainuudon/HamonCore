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
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
proj(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.value.ops]/7
    return
		hamon::isinf(hamon::real(x)) || hamon::isinf(hamon::imag(x)) ?
			hamon::complex<T>(hamon::numeric_limits<T>::infinity(), hamon::copysign(T(), hamon::imag(x))) :
		x;
}

// [cmplx.over]/2.1
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, Float)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<Float>	// nodiscard as an extension
proj(Float f) HAMON_NOEXCEPT	// noexcept as an extension
{
	return hamon::proj(complex<Float>{f});
}

// [cmplx.over]/2.2
template <HAMON_CONSTRAINED_PARAM(hamon::integral, Integer)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<double>	// nodiscard as an extension
proj(Integer i) HAMON_NOEXCEPT	// noexcept as an extension
{
	return hamon::proj(complex<double>{static_cast<double>(i)});
}

}	// namespace hamon

#endif // HAMON_COMPLEX_PROJ_HPP
