/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_LIST_CONFIG_HPP
#define HAMON_LIST_CONFIG_HPP

#include <list>

#if defined(__cpp_lib_incomplete_container_elements) && (__cpp_lib_incomplete_container_elements >= 201505L) && \
	defined(__cpp_lib_list_remove_return_type) && (__cpp_lib_list_remove_return_type >= 201806) && \
	defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L) && \
	0	// 独自にconstexpr対応するため、std::listは使わない

#define HAMON_USE_STD_LIST

#endif

#endif // HAMON_LIST_CONFIG_HPP
