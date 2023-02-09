/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_ALGORITHM_CONFIG_HPP
#define HAMON_ALGORITHM_CONFIG_HPP

#include <hamon/config.hpp>
#include <hamon/ranges/config.hpp>
#include <algorithm>

#if defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms >= 201806)
#  define HAMON_USE_STD_ALGORITHM
#endif

#if defined(HAMON_USE_STD_ALGORITHM) && defined(HAMON_USE_STD_RANGES)
#  define HAMON_USE_STD_RANGES_ALGORITHM
#endif

#endif // HAMON_ALGORITHM_CONFIG_HPP
