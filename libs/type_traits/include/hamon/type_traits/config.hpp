/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_TYPE_TRAITS_CONFIG_HPP
#define HAMON_TYPE_TRAITS_CONFIG_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/config.hpp>
#include <type_traits>

#if defined(HAMON_USE_STD_CONCEPTS) &&	\
	defined(__cpp_lib_common_reference) && (__cpp_lib_common_reference >= 202302)
#  define HAMON_USE_STD_COMMON_REFERENCE
#endif

#endif // HAMON_TYPE_TRAITS_CONFIG_HPP
