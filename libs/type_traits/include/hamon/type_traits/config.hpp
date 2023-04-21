/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_TYPE_TRAITS_CONFIG_HPP
#define HAMON_TYPE_TRAITS_CONFIG_HPP

#include <hamon/config.hpp>
#include <type_traits>
#if defined(HAMON_HAS_CXX20_CONCEPTS) && HAMON_HAS_INCLUDE(<concepts>)
#include <concepts>
#endif

#if defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002) &&	\
	defined(__cpp_lib_common_reference) && (__cpp_lib_common_reference >= 202302)
#  define HAMON_USE_STD_COMMON_REFERENCE
#endif

#endif // HAMON_TYPE_TRAITS_CONFIG_HPP
