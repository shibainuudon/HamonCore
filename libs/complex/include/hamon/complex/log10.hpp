/**
 *	@file	log10.hpp
 *
 *	@brief	log10関数の定義
 */

#ifndef HAMON_COMPLEX_LOG10_HPP
#define HAMON_COMPLEX_LOG10_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/log.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.transcendentals], transcendentals

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
log10(complex<T> const& x)
{
	return hamon::log(x) / hamon::log(T(10));
}

}	// namespace hamon

#endif // HAMON_COMPLEX_LOG10_HPP
