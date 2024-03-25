/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_FUNCTIONAL_CONFIG_HPP
#define HAMON_FUNCTIONAL_CONFIG_HPP

#include <hamon/config.hpp>
#include <hamon/ranges/config.hpp>
#include <functional>

#if HAMON_CXX_STANDARD >= 17
#  if defined(__cpp_lib_transparent_operators) && (__cpp_lib_transparent_operators >= 201210)
#    define HAMON_USE_STD_FUNCTIONAL_OPERATORS
#  endif
#endif

#if defined(HAMON_USE_STD_RANGES)
#  define HAMON_USE_STD_RANGES_FUNCTIONAL
#endif

#if defined(__cpp_lib_constexpr_functional) && (__cpp_lib_constexpr_functional >= 201907) &&	\
	!(defined(HAMON_APPLE_CLANG) && (HAMON_APPLE_CLANG <= 130000))	// AppleClang 13.0.0 は __cpp_lib_constexpr_functional を定義しているのにconstexprになっていない
#  define HAMON_CPP_LIB_CONSTEXPR_FUNCTIONAL
#endif

#if defined(HAMON_CPP_LIB_CONSTEXPR_FUNCTIONAL) && \
	defined(__cpp_lib_common_reference) && (__cpp_lib_common_reference >= 202302L) && \
	defined(__cpp_lib_common_reference_wrapper) && (__cpp_lib_common_reference_wrapper >= 202302L) && \
	HAMON_CXX_STANDARD >= 23
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
