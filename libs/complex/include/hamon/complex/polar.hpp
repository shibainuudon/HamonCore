/**
 *	@file	polar.hpp
 *
 *	@brief	polar関数の定義
 */

#ifndef HAMON_COMPLEX_POLAR_HPP
#define HAMON_COMPLEX_POLAR_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.value.ops], values

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
polar(T const& rho, T const& theta = T()) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.value.ops]/10
	return hamon::complex<T>(
		rho * hamon::cos(theta),
		rho * hamon::sin(theta));
}

}	// namespace hamon

#endif // HAMON_COMPLEX_POLAR_HPP
