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
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
log(complex<T> const& x)
{
	return hamon::complex<T>(
		hamon::log(hamon::abs(x)),
		hamon::arg(x));
}

}	// namespace hamon

#endif // HAMON_COMPLEX_LOG_HPP
