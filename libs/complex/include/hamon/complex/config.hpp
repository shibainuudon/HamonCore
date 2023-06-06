/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_COMPLEX_CONFIG_HPP
#define HAMON_COMPLEX_CONFIG_HPP

#include <hamon/config.hpp>
#include <complex>

#if defined(__cpp_lib_constexpr_complex) && (__cpp_lib_constexpr_complex >= 201711L) &&	\
	defined(__cpp_lib_complex_udls) && (__cpp_lib_complex_udls >= 201309L)

// gccとclangでは std::complex の実装にC言語の _Complex を使っているため、
// constexprにできない部分がある。
#if !defined(HAMON_GCC) && !defined(HAMON_CLANG)
#  define	HAMON_USE_STD_COMPLEX
#endif

#endif

#endif // HAMON_COMPLEX_CONFIG_HPP
