/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_UNORDERED_MAP_CONFIG_HPP
#define HAMON_UNORDERED_MAP_CONFIG_HPP

#include <unordered_map>

#if defined(__cpp_lib_nonmember_container_access)          && (__cpp_lib_nonmember_container_access          >= 201411L) && \
    defined(__cpp_lib_unordered_map_try_emplace)           && (__cpp_lib_unordered_map_try_emplace           >= 201411L) && \
    defined(__cpp_lib_node_extract)                        && (__cpp_lib_node_extract                        >= 201606L) && \
    defined(__cpp_lib_generic_unordered_lookup)            && (__cpp_lib_generic_unordered_lookup            >= 201811L) && \
    defined(__cpp_lib_associative_heterogeneous_erasure)   && (__cpp_lib_associative_heterogeneous_erasure   >= 202110L) && \
    defined(__cpp_lib_containers_ranges)                   && (__cpp_lib_containers_ranges                   >= 202202L) && \
    defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L) && \
    defined(__cpp_lib_tuple_like)                          && (__cpp_lib_tuple_like                          >= 202311L) && \
    defined(__cpp_lib_constexpr_unordered_map)             && (__cpp_lib_constexpr_unordered_map             >= 202502L)

#define HAMON_USE_STD_UNORDERED_MAP
#define HAMON_USE_STD_UNORDERED_MULTIMAP

#endif

#endif // HAMON_UNORDERED_MAP_CONFIG_HPP
