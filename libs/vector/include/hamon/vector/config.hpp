/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_VECTOR_CONFIG_HPP
#define HAMON_VECTOR_CONFIG_HPP

#include <hamon/config.hpp>
#include <vector>

#if defined(__cpp_lib_allocator_traits_is_always_equal) && (__cpp_lib_allocator_traits_is_always_equal >= 201411L) && \
	defined(__cpp_lib_incomplete_container_elements)    && (__cpp_lib_incomplete_container_elements    >= 201505L) && \
	defined(__cpp_lib_constexpr_vector)                 && (__cpp_lib_constexpr_vector                 >= 201907L) && \
	defined(__cpp_lib_three_way_comparison)             && (__cpp_lib_three_way_comparison             >= 201907L) && \
	defined(__cpp_lib_containers_ranges)                && (__cpp_lib_containers_ranges                >= 202202L) && \
	!defined(HAMON_APPLE_CLANG)	/* Apple Clangのstd::vectorは使わない(insert関数においてvalue_typeがcopy assignableであることを要求するので) */

#  define HAMON_USE_STD_VECTOR

#endif

#endif // HAMON_VECTOR_CONFIG_HPP
