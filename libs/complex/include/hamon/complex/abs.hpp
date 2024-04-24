/**
 *	@file	abs.hpp
 *
 *	@brief	abs関数の定義
 */

#ifndef HAMON_COMPLEX_ABS_HPP
#define HAMON_COMPLEX_ABS_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/real.hpp>
#include <hamon/complex/imag.hpp>
#include <hamon/cmath/hypot.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.value.ops], values

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T	// nodiscard as an extension
abs(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.value.ops]/3
	return hamon::hypot(hamon::real(x), hamon::imag(x));
}

}	// namespace hamon

#endif // HAMON_COMPLEX_ABS_HPP
