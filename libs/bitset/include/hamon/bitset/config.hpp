/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_BITSET_CONFIG_HPP
#define HAMON_BITSET_CONFIG_HPP

#include <bitset>

#if defined(__cpp_lib_bitset) && (__cpp_lib_bitset >= 202306L) &&	\
	defined(__cpp_lib_constexpr_bitset) && (__cpp_lib_constexpr_bitset >= 202207L) &&	\
	defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907L)

#define	HAMON_USE_STD_BITSET

#endif

#endif // HAMON_BITSET_CONFIG_HPP
