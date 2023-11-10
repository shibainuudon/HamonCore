/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_PAIR_CONFIG_HPP
#define HAMON_PAIR_CONFIG_HPP

#if defined(__cpp_lib_constexpr_utility) && (__cpp_lib_constexpr_utility >= 201811) && \
	defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907) && \
	defined(__cpp_lib_ranges_zip) && (__cpp_lib_ranges_zip >= 202110L) && \
	defined(__cpp_lib_tuple_like) && (__cpp_lib_tuple_like >= 202207L)
#  define HAMON_USE_STD_PAIR
#endif

#endif // HAMON_PAIR_CONFIG_HPP
