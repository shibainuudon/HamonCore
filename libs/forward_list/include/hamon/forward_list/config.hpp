/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORWARD_LIST_CONFIG_HPP
#define HAMON_FORWARD_LIST_CONFIG_HPP

#include <forward_list>

#if defined(__cpp_lib_incomplete_container_elements) && (__cpp_lib_incomplete_container_elements >= 201505L) && \
	defined(__cpp_lib_list_remove_return_type) && (__cpp_lib_list_remove_return_type >= 201806) && \
	defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L) && \
	0	// 独自にconstexpr対応するため、std::forward_listは使わない

#define HAMON_USE_STD_FORWARD_LIST

#endif

#endif // HAMON_FORWARD_LIST_CONFIG_HPP
