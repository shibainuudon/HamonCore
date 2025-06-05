/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_FLAT_MAP_CONFIG_HPP
#define HAMON_FLAT_MAP_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 23)

#if HAMON_HAS_INCLUDE(<flat_map>)
#  include <flat_map>
#endif

#if defined(__cpp_lib_flat_map)           && (__cpp_lib_flat_map           >= 202207L) && \
	defined(__cpp_lib_constexpr_flat_map) && (__cpp_lib_constexpr_flat_map >= 202502L)

#  define HAMON_USE_STD_FLAT_MAP

#endif

#endif

#endif // HAMON_FLAT_MAP_CONFIG_HPP
