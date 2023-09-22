/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_NUMBERS_CONFIG_HPP
#define HAMON_NUMBERS_CONFIG_HPP

#include <hamon/config.hpp>

#if HAMON_HAS_INCLUDE(<numbers>) && (HAMON_CXX_STANDARD >= 20)
#  include <numbers>
#endif

#if defined(__cpp_lib_math_constants) && (__cpp_lib_math_constants >= 201907L)
#  define	HAMON_USE_STD_NUMBERS
#endif

#endif // HAMON_NUMBERS_CONFIG_HPP
