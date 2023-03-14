/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_ARRAY_CONFIG_HPP
#define HAMON_ARRAY_CONFIG_HPP

#include <array>

#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201811) && \
	defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907)
#  define HAMON_USE_STD_ARRAY
#endif

#endif // HAMON_ARRAY_CONFIG_HPP
