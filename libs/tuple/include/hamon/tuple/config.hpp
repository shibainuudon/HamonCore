/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_TUPLE_CONFIG_HPP
#define HAMON_TUPLE_CONFIG_HPP

#include <hamon/config.hpp>
#include <tuple>

#if defined(__cpp_lib_constexpr_tuple) && (__cpp_lib_constexpr_tuple >= 201811) && \
	defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907) && \
	defined(__cpp_lib_ranges_zip) && (__cpp_lib_ranges_zip >= 202110L) && \
	defined(__cpp_lib_tuple_like) && (__cpp_lib_tuple_like >= 202207L)
#  define HAMON_USE_STD_TUPLE
#endif

#endif // HAMON_TUPLE_CONFIG_HPP
