﻿/**
 *	@file	sin.hpp
 *
 *	@brief	sin関数の定義
 */

#ifndef HAMON_COMPLEX_SIN_HPP
#define HAMON_COMPLEX_SIN_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/sinh.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.transcendentals], transcendentals

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
sin(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.transcendentals]/22
	return complex<T>{0, -1} * hamon::sinh(complex<T>{0, 1} * x);
}

}	// namespace hamon

#endif // HAMON_COMPLEX_SIN_HPP
