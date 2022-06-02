/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_ALGORITHM_CONFIG_HPP
#define HAMON_ALGORITHM_CONFIG_HPP

#include <hamon/config.hpp>
#include <algorithm>

#if defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms >= 201806)
#  define HAMON_USE_STD_ALGORITHM
#endif

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 202106)
#  define HAMON_USE_STD_RANGES_ALGORITHM
#endif

#endif // HAMON_ALGORITHM_CONFIG_HPP
