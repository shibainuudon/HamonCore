﻿/**
 *	@file	atan.hpp
 *
 *	@brief	atan関数の定義
 */

#ifndef HAMON_COMPLEX_ATAN_HPP
#define HAMON_COMPLEX_ATAN_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/atanh.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.transcendentals], transcendentals

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>
atan(complex<T> const& x)
{
	return complex<T>{0, -1} * hamon::atanh(complex<T>{0, 1} * x);
}

}	// namespace hamon

#endif // HAMON_COMPLEX_ATAN_HPP
