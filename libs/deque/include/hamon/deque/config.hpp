/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_DEQUE_CONFIG_HPP
#define HAMON_DEQUE_CONFIG_HPP

#include <deque>

#if defined(__cpp_lib_allocator_traits_is_always_equal) && (__cpp_lib_allocator_traits_is_always_equal >= 201411L) && \
	defined(__cpp_lib_nonmember_container_access)       && (__cpp_lib_nonmember_container_access       >= 201411L) && \
	defined(__cpp_lib_algorithm_default_value_type)     && (__cpp_lib_algorithm_default_value_type     >= 202403L) && \
	defined(__cpp_lib_containers_ranges)                && (__cpp_lib_containers_ranges                >= 202202L)

// 独自実装のdequeはconstexprに対応した(C++20以上)。
// std::dequeはC++26でもconstexprになっていないので使用しない。
//#  define HAMON_USE_STD_DEQUE

#endif

#endif // HAMON_DEQUE_CONFIG_HPP
