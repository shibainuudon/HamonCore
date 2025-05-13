/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_QUEUE_CONFIG_HPP
#define HAMON_QUEUE_CONFIG_HPP

#include <queue>

#if defined(__cpp_lib_adaptor_iterator_pair_constructor) && (__cpp_lib_adaptor_iterator_pair_constructor >= 202106L) && \
	defined(__cpp_lib_containers_ranges)                 && (__cpp_lib_containers_ranges                 >= 202202L) && \
	defined(__cpp_lib_constexpr_queue)                   && (__cpp_lib_constexpr_queue                   >= 202502L)

#  define HAMON_USE_STD_QUEUE
#  define HAMON_USE_STD_PRIORITY_QUEUE

#endif

#endif // HAMON_QUEUE_CONFIG_HPP
