/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_FUNCTIONAL_CONFIG_HPP
#define HAMON_FUNCTIONAL_CONFIG_HPP

#include <hamon/config.hpp>
#include <functional>

#if defined(__cpp_lib_constexpr_functional) && (__cpp_lib_constexpr_functional >= 201907) &&	\
	!(defined(HAMON_APPLE_CLANG) && (HAMON_APPLE_CLANG <= 130000))	// AppleClang 13.0.0 は __cpp_lib_constexpr_functional を定義しているのにconstexprになっていない
#  define HAMON_CPP_LIB_CONSTEXPR_FUNCTIONAL
#endif

#if defined(HAMON_CPP_LIB_CONSTEXPR_FUNCTIONAL)
#  define HAMON_USE_STD_REFERENCE_WRAPPER
#endif

#if defined(HAMON_USE_STD_REFERENCE_WRAPPER) && \
	defined(__cpp_lib_invoke) && (__cpp_lib_invoke >= 201411)
#  define HAMON_USE_STD_INVOKE
#endif

#if defined(HAMON_USE_STD_REFERENCE_WRAPPER) && \
	defined(__cpp_lib_invoke_r) && (__cpp_lib_invoke_r >= 202106)
#  define HAMON_USE_STD_INVOKE_R
#endif

#endif // HAMON_FUNCTIONAL_CONFIG_HPP
