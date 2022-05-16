/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_BIT_CONFIG_HPP
#define HAMON_BIT_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 20) && HAMON_HAS_INCLUDE(<bit>)
#include <bit>

#  if defined(__cpp_lib_endian) && (__cpp_lib_endian >= 201907)
#    define HAMON_HAS_CXX_LIB_ENDIAN
#  endif
#  if defined(__cpp_lib_bit_cast) && (__cpp_lib_bit_cast >= 201806)
#    define HAMON_HAS_CXX_LIB_BIT_CAST
#  endif
#  if defined(__cpp_lib_bitops) && (__cpp_lib_bitops >= 201907)
#    define HAMON_HAS_CXX_LIB_BITOPS
#  endif
#  if defined(__cpp_lib_int_pow2) && (__cpp_lib_int_pow2 >= 202002)
#    define HAMON_HAS_CXX_LIB_INT_POW2
#  endif

#endif

#endif // HAMON_BIT_CONFIG_HPP
