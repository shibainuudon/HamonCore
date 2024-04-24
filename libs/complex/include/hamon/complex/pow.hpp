/**
 *	@file	pow.hpp
 *
 *	@brief	pow関数の定義
 */

#ifndef HAMON_COMPLEX_POW_HPP
#define HAMON_COMPLEX_POW_HPP

#include <hamon/complex/complex.hpp>
#include <hamon/complex/exp.hpp>
#include <hamon/complex/log.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [complex.transcendentals], transcendentals

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
pow(complex<T> const& x, complex<T> const& y) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.transcendentals]/20
	return hamon::exp(y * hamon::log(x));
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
pow(complex<T> const& x, T const& y) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.transcendentals]/20
	return hamon::pow(x, complex<T>{y});
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR complex<T>	// nodiscard as an extension
pow(T const& x, complex<T> const& y) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [complex.transcendentals]/20
	return hamon::pow(complex<T>{x}, y);
}

// [cmplx.over]/3
template <typename T1, typename T2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::complex<hamon::common_type_t<T1, T2>>	// nodiscard as an extension
pow(complex<T1> const& x, complex<T2> const& y) HAMON_NOEXCEPT	// noexcept as an extension
{
	return hamon::pow(
		hamon::complex<hamon::common_type_t<T1, T2>>(x),
		hamon::complex<hamon::common_type_t<T1, T2>>(y));
}

// [cmplx.over]/3
template <typename T1, typename T2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::complex<hamon::common_type_t<T1, T2>>	// nodiscard as an extension
pow(complex<T1> const& x, T2 const& y) HAMON_NOEXCEPT	// noexcept as an extension
{
	return hamon::pow(
		hamon::complex<hamon::common_type_t<T1, T2>>(x),
		static_cast<hamon::common_type_t<T1, T2>>(y));
}

// [cmplx.over]/3
template <typename T1, typename T2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::complex<hamon::common_type_t<T1, T2>>	// nodiscard as an extension
pow(T1 const& x, complex<T2> const& y) HAMON_NOEXCEPT	// noexcept as an extension
{
	return hamon::pow(
		static_cast<hamon::common_type_t<T1, T2>>(x),
		hamon::complex<hamon::common_type_t<T1, T2>>(y));
}

}	// namespace hamon

#endif // HAMON_COMPLEX_POW_HPP
