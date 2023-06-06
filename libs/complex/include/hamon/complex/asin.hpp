/**
 *	@file	asin.hpp
 *
 *	@brief	asin関数の定義
 */

#ifndef HAMON_COMPLEX_ASIN_HPP
#define HAMON_COMPLEX_ASIN_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/asinh.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.transcendentals], transcendentals

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
asin(complex<T> const& x)
{
	return complex<T>{0, -1} * hamon::asinh(complex<T>{0, 1} * x);
}

}	// namespace hamon

#endif // HAMON_COMPLEX_ASIN_HPP
