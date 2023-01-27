/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_NUMERIC_CONFIG_HPP
#define HAMON_NUMERIC_CONFIG_HPP

#include <hamon/config.hpp>
#include <numeric>

#if defined(__cpp_lib_constexpr_numeric) && (__cpp_lib_constexpr_numeric >= 201911)
#  define HAMON_USE_STD_NUMERIC
#endif

#if defined(HAMON_USE_STD_NUMERIC) &&	\
	defined(__cpp_lib_parallel_algorithm) && (__cpp_lib_parallel_algorithm >= 201603)
#  define HAMON_USE_STD_NUMERIC_PARALLEL
#endif

#endif // HAMON_NUMERIC_CONFIG_HPP
