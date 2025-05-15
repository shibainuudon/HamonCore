/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_STACK_CONFIG_HPP
#define HAMON_STACK_CONFIG_HPP

#include <stack>

#if defined(__cpp_lib_adaptor_iterator_pair_constructor	)  && (__cpp_lib_adaptor_iterator_pair_constructor	 >= 202106L) && \
    defined(__cpp_lib_containers_ranges)                   && (__cpp_lib_containers_ranges                   >= 202202L) && \
    defined(__cpp_lib_constexpr_stack)                     && (__cpp_lib_constexpr_stack                     >= 202502L)

#define HAMON_USE_STD_STACK

#endif

#endif // HAMON_STACK_CONFIG_HPP
