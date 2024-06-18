/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_CHRONO_CONFIG_HPP
#define HAMON_CHRONO_CONFIG_HPP

#include <chrono>

#if	defined(__cpp_lib_chrono) && (__cpp_lib_chrono >= 202306L) && \
	defined(__cpp_lib_chrono_udls) && (__cpp_lib_chrono_udls >= 201304L) && \
	defined(__cpp_lib_type_trait_variable_templates) && (__cpp_lib_type_trait_variable_templates >= 201510L) && \
	defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907L) && \
	defined(__cpp_lib_format) && (__cpp_lib_format >= 202207L)

#  define HAMON_USE_STD_CHRONO

#endif

#endif // HAMON_CHRONO_CONFIG_HPP
