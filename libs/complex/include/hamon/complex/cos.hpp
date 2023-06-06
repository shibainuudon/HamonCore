/**
 *	@file	cos.hpp
 *
 *	@brief	cos関数の定義
 */

#ifndef HAMON_COMPLEX_COS_HPP
#define HAMON_COMPLEX_COS_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/cosh.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.transcendentals], transcendentals

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
cos(complex<T> const& x)
{
	return hamon::cosh(complex<T>{0, 1} * x);
}

}	// namespace hamon

#endif // HAMON_COMPLEX_COS_HPP
