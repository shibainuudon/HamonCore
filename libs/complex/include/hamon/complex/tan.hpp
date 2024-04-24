/**
 *	@file	tan.hpp
 *
 *	@brief	tan関数の定義
 */

#ifndef HAMON_COMPLEX_TAN_HPP
#define HAMON_COMPLEX_TAN_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/tanh.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.transcendentals], transcendentals

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
tan(complex<T> const& x) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.transcendentals]/26
	return complex<T>{0, -1} * hamon::tanh(complex<T>{0, 1} * x);
}

}	// namespace hamon

#endif // HAMON_COMPLEX_TAN_HPP
