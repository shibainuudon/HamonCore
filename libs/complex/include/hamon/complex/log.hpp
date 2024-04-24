/**
 *	@file	log.hpp
 *
 *	@brief	log関数の定義
 */

#ifndef HAMON_COMPLEX_LOG_HPP
#define HAMON_COMPLEX_LOG_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/abs.hpp>
#include <hamon/complex/arg.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.transcendentals], transcendentals

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
log(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.transcendentals]/16
	return hamon::complex<T>(
		hamon::log(hamon::abs(x)),
		hamon::arg(x));
}

}	// namespace hamon

#endif // HAMON_COMPLEX_LOG_HPP
