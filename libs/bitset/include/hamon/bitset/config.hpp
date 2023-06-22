/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_BITSET_CONFIG_HPP
#define HAMON_BITSET_CONFIG_HPP

#include <bitset>

#if defined(__cpp_lib_constexpr_bitset) && (__cpp_lib_constexpr_bitset >= 202207L)

#define	HAMON_USE_STD_BITSET

#endif

#endif // HAMON_BITSET_CONFIG_HPP
